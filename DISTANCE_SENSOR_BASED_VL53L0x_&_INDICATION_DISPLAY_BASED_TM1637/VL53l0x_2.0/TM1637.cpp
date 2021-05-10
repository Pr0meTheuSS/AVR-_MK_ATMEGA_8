#include "main.h"
#include "TM1637.h"


uint8_t digits[] =
{
	0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f
};


void indication(int n)
{
	int n1, n2, n3, n4;
	n1 = (int) n % 10;
	n2 = (int) ((n % 100)-n1)/10;
	n3 = (int) ((n % 1000) - n2 - n1) / 100;
	n4 = (int) ((n % 10000) - n3 - n2 - n1) / 1000;
	write(digits[n4], digits[n3], digits[n2], digits[n1]);
}


void write(uint8_t first, uint8_t second, uint8_t third, uint8_t fourth)
{
	start();
	writeValue(SetBright); // яркость, настраивается в main.h
	start();
	writeValue(0x40); // писать в регистры дисплея
	stop();
	start();
	writeValue(0xc0); // вывод с 1-го разряда.
	writeValue(first);
	writeValue(second);
	writeValue(third);
	writeValue(fourth);
	stop();
}

void start(void)
{
	DDRB|=(1<<_CLK);
	DDRB|=(1<<_DIO);
	PORTB |= (1<<_CLK);
	PORTB |= (1<<_DIO);
	_delay_us(5);
	PORTB &=~ (1<<_DIO);
	PORTB &=~ (1<<_CLK);
	_delay_us(5);
}

void stop(void)
{
	DDRB|=(1<<_CLK);
	DDRB|=(1<<_DIO);
	PORTB &=~ (1<<_CLK);
	PORTB &=~ (1<<_DIO);
	_delay_us(5);
	PORTB |= (1<<_CLK);
	PORTB |= (1<<_DIO);
	_delay_us(5);
}


void writeValue(uint8_t value)
{
	for(uint8_t i = 0; i < 8; i++)
	{
		PORTB &=~ (1<<_CLK);
		_delay_us(5);
		bool not_null = ((value & (1 << i)) >> i);
		if(not_null)
		PORTB |= (1<<_DIO);
		else
		PORTB &=~ (1<<_DIO);
		_delay_us(5);
		PORTB |= (1<<_CLK);
		_delay_us(5);
	}
	PORTB &=~ (1<<_CLK);
	_delay_us(5);
	PORTB |= (1<<_CLK);
	_delay_us(5);
}