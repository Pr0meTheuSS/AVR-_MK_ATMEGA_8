#ifndef I2C_H_
#define I2C_H_
#include <avr/io.h>

void I2C_init(void);// инициализация
void I2C_Start(void);//Старт
void I2C_Stop(void);//Стоп
void I2C_SendByte(unsigned char c);//отправка данных
void I2C_SendByteAdres(unsigned char c, unsigned char addr );// отправка данных по адресу
unsigned char I2C_ReadByte(void);// чтение байта
unsigned char I2C_ReadLastByte(void);// чтение последнего байта

#endif /* I2C_H_ */
