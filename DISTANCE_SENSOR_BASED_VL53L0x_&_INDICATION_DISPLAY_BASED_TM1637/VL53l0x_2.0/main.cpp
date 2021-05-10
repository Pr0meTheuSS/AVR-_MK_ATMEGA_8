/*
 * VL53l0x_2.0.cpp
 *
 * Created: 20.03.2021 23:46:09
 * Author : olimp
 */ 

#define F_CPU 1200000UL
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>
#include "TM1637.cpp"


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


void print(unsigned int value){
	indication(value);
	_delay_ms(2000);
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//25.03.2021_ сделал версию, способную выводить информацию о дистанции до объекта 
//в миллиметрах с точностью до сантиметра
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
unsigned int VL53L0x_result_mm(uint8_t data[]){
	unsigned int result = 0;
	if (data[0] == 0){
		if (data[1] == 20){
			result = 10;
		}
		if(data[1] >= 50){
			result = data[1] - 30; 
		}
	}
	else{
		result += 200 * data[0];// register #30
		result += data[1];// register #31	
	}
	return result;
}

uint8_t Abs(uint8_t val_1, uint8_t val_2){
	return val_1 >= val_2?val_1 - val_2:val_2 - val_1;
	};

int main(void)
{
	uint8_t data[2];
	uint8_t new_data = 0;
	I2C_init();
    while (1) 
    {
		I2C_Start();
		// VL53l0x i2c to write
		I2C_SendByte(0x52);
		// VL53l0x register 0x0 in condition 01 ~ START Measurement

		I2C_SendByte(0x0);
		I2C_SendByte(0x1);
		I2C_Stop();
		//repeat Start i2c
		I2C_Start();
		// VL53l0x i2c to write adress of register containing result	
		I2C_SendByte(0x52);
		I2C_SendByte(30);
		
		I2C_Start();
		I2C_SendByte(0x53);
		
		data[0] = I2C_ReadByte();
		new_data = I2C_ReadLastByte();
		if (Abs(data[1], new_data) > 5){
			data[1] = new_data;
		}
		indication(VL53L0x_result_mm(data));
		I2C_Stop();
	}
}

