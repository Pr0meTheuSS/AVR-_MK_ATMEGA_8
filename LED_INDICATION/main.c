/*
 * Created: 16.11.2020 22:25:20
 * Author : olimp
 */ 
# define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRC =  0b0000001;
    while (1) 
    {
		PORTC = 0b0000001;
		_delay_ms(500);		
		PORTC = 0b0000000;
		_delay_ms(500);
    }
}
