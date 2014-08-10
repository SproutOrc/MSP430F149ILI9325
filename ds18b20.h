#ifndef __DS18B20_H__
#define __DS18B20_H__
//#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char
void Delayus(uint us);
void DS18B20_Init();
uchar ReadByte(void);
void WriteByte(uchar WriteData);
void init_TimerA ( void );
uint DisplayTemp();
#endif