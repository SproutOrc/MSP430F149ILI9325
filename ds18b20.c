#include "ds18b20.h"
#include <stdio.h>
#include <math.h>
#include "gui.h"
#include "global.h"
#include "ILI9325.h"
#define DQ_1    P2OUT |=BIT2
#define DQ_0    P2OUT &=~BIT2
#define DQ_OUT  P2DIR|=BIT2
#define DQ_IN   P2DIR&=~BIT2
#define DQ_DATA P2IN&BIT2
uchar num;
float temp;
float temperature;
char DisplayArray[16];
void Delayus(uint us)
{
  while(us--)
  {
    for(uint i=0;i<8;i++);
  }
}
void DS18B20_Init() 
{
  DQ_OUT;//设置为输出方向
  DQ_0;//拉低总线
  Delayus(50);
  DQ_1;//释放总线
  Delayus(6);
  DQ_IN;//设置为输入方向
  while(DQ_DATA);//等待应答信号
  while(~DQ_DATA);//等待释放总线
}
//读一个字节
uchar ReadByte(void)
{
  uchar i;
  uchar ReadData=0;
  for(i=0;i<8;i++)
  {
    DQ_OUT;
    DQ_0;
    ReadData>>=1;
    DQ_1;
    Delayus(1);
    DQ_IN;
    if(DQ_DATA) ReadData|=0x80;
    Delayus(6);
  }
  return ReadData;
}
//写一个字节
void WriteByte(uchar WriteData)
{
  uint i;
  uchar tempData;
  for(i=0;i<8;i++){
    tempData=WriteData&0x01;
    WriteData>>=1;
    DQ_OUT;
    DQ_0;
    if(tempData){
      DQ_1;
    }else{
      DQ_0;
    }
    Delayus(5);
    DQ_1;
  }
}

uint ReadTemperature()
{
    uchar a=0,b=0;
    int temp;
    DS18B20_Init();
    WriteByte(0xCC);
    WriteByte(0x44);
    DelayUs(10);
    DS18B20_Init();
    WriteByte(0xCC);
    WriteByte(0xBE);
    a=ReadByte();
    b=ReadByte();
    temp=b;
    temp<<=8;
    temp=a|temp;
    if(temp>0x07ff)
    {
      temp=~temp;
      temp++;
      temp=temp*6.25+0.55;
    
    }	
    else
      temp=temp*6.25+0.55;
    
    return temp;
}

uint DisplayTemp()
{
    temp=ReadTemperature();
    DelayMs(50);
    return temp;
}
/****************************************************
*             定时器初始化
****************************************************/
void init_TimerA ( void )
{
  CCTL0 = CCIE;                     // 开启比较器0中断
  CCR0 = 32768;                    // 1S秒的定时  
  TACTL = TASSEL_1 + MC_1;          // 开启定时器   
}


