#ifndef TM1637_H_
#define TM1637_H_

//------------- настройка подключени€ индикатора, ножки  PB0 и PB1 (дл€ изменени€ порта мен€ть в коде функций)----------
#define _CLK 1
#define _DIO 0
//------------------------------------------------------------------


//------------- €ркость свечени€ индикатора ----------
#define Bright0 0x88
#define Bright1 0x89
#define Bright2 0x8A
#define Bright3 0x8B
#define Bright4 0x8C
#define Bright5 0x8D
#define Bright6 0x8E
#define Bright7 0x8F
#define SetBright Bright1 //сюда прописать €ркость от 0 до 7
//------------------------------------------------------------------


void delay_us(uint16_t us);
void delay_ms(uint16_t ms);
void indication(int n);
void write(uint8_t first, uint8_t second, uint8_t third, uint8_t fourth);
void start(void);
void stop(void);
void writeValue(uint8_t value);


#endif /* TM1637_H_ */