#ifndef I2C_H_
#define I2C_H_
#include <avr/io.h>

void I2C_init(void);// �������������
void I2C_Start(void);//�����
void I2C_Stop(void);//����
void I2C_SendByte(unsigned char c);//�������� ������
void I2C_SendByteAdres(unsigned char c, unsigned char addr );// �������� ������ �� ������
unsigned char I2C_ReadByte(void);// ������ �����
unsigned char I2C_ReadLastByte(void);// ������ ���������� �����

#endif /* I2C_H_ */
