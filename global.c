/***********************************************************
*模块名称：global
*功能说明：写公用模块函数
***********************************************************/
#include"global.h"

void DelayMs(uint a)
{
  	uchar i;
  	for(i = a;i>0;i--)
  		__delay_cycles(1000);
}

void DelayUs(uint z)
{
  	uchar i;
  	for(i=z;i>0;i--)
	  	__delay_cycles(1);
}
