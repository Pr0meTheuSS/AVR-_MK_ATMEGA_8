#include “I2C.h”


void I2C_init(void){
	TWSR=(0<<TWPS1)|(0<<TWPS0);// настройка делителя
	TWBR=0x20; // настройка рабочей частоты шины
}

void I2C_Start(void){
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!(TWCR&(1<<TWINT))){;}
}

void I2C_Stop(void){
	TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

void I2C_SendByte(unsigned char c){
	TWDR=c;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while (!(TWCR&(1<<TWINT))){;}
}

void I2C_SendByteAdres(unsigned char c, unsigned char addr )
{
	I2C_Start();
	I2C_SendByte(addr);
	I2C_SendByte(c);
	I2C_Stop();
}

unsigned char I2C_ReadByte(void){
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while (!(TWCR&(1<<TWINT))){;}
	return TWDR;
}

unsigned char I2C_ReadLastByte(void){
	TWCR=(1<<TWINT)|(1<<TWEN);
	while (!(TWCR&(1<<TWINT))){;}
	return TWDR;
}
