/***********************************************************
*ģ�����ƣ�global
*����˵����д����ģ�麯��
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
