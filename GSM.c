#include<msp430x14x.h>
#include "GSM.h"
#include "isd4004.h"
void GsmSend(void);
void UART0_Init (void);
void DelayNS (unsigned int dly);
void Delay(unsigned long t);
//表示以pud的方式发送短信
unsigned char ATCMGF[]="AT+CMGF=0\r\n";  
//设置短消息通知单片机服务端
unsigned char ATCN[]="AT+CNMI=2,1\r\n";
//设置PUD格式内容:有人闯入
uchar ATCMGS[]="0891683108701905F011000B818177004940F50008A71253EF75914EBA5458722C7A9751655C4BFF01";
//uart初始化
void InitGSM()
{
  //BoardConfig(0xb8);
  P1DIR &=~BIT7;//配置为输入
  P1SEL &=~BIT7;//选择为功能模块
  P1IES |= BIT7;//选择触发方式1为下降沿触发，0上升沿
  P1IE  |= BIT7;//使能中断
  P1IFG &=~BIT7;//清除标志位
  
  //P1DIR &=~BIT6;//配置为输入
  //P1SEL &=~BIT6;//选择为功能模块
  //P1IES &=~BIT6;//选择触发方式1为下降沿触发，0上升沿
  //P1IE  |= BIT6;//使能中断
  //P1IFG &=~BIT6;//清除标志位
   
  UART0_Init();
}
//uart初始化
void UART0_Init(void)
{
  /*ME1 |= UTXE0 +URXE0;         //使能UART0的TXD和RXD
  UCTL0 = CHAR;                //选择八位字符
  UTCTL0 = SSEL0;              //UCLK=ACLK
  UBR00 = 0X03;                //波特率设置为9600
  UBR10 = 0X00;
  UMCTL0 =0X4A;               //USART0模式控制
  UCTL0 &= ~SWRST;            //初始化UART控制机
  IE1 |= URXIE0;              //使能UART0的RX接收中断
  P3SEL = 0X30;               //设置P3.4/P3.5为UART0的txd和rxd
  P3DIR = 0x10;               //设置P3.4为输出管脚
  */
  BCSCTL1 &= ~XT2OFF;          // XT2on
  BCSCTL2 |= SELM_2 + SELS;    // MCLK = SMCLK = XT2 (safe)
  ME1 |= UTXE0 +URXE0;         //使能UART0的TXD和RXD
  UCTL0 |= CHAR;                //选择八位字符
  UTCTL0 |= SSEL1;              //UCLK=ACLK
  UBR00 = 0XA0;                //波特率设置为19200
  UBR10 = 0X01;
  UMCTL0 =0X00;               //USART0模式控制
  UCTL0 &= ~SWRST;            //初始化UART控制机
  IE1 |= URXIE0;              //使能UART0的RX接收中断
  P3SEL = 0X30;               //设置P3.4/P3.5为UART0的txd和rxd
  P3DIR = 0x10;               //设置P3.4为输出管脚
}
//时间延迟
void DelayNS(unsigned int dly)  
{
  unsigned int i;
  for(;dly>0;dly--)
    for(i=0;i<2000;i++);
}
//消息发送
void GsmSend1(void)
{
  unsigned char ATNUM[]="AT+CMGS=32\r\n";
  unsigned char i;
  if((P1IFG&BIT7)==BIT7) //此if语句主要用于中断前的清理工作
 {
      P1IFG &=~BIT7;//清除中断标志位
      P1IE  &=~BIT7;//关闭中断
  }
  DelayNS(150);
  for(i=0;i<11;i++)
  {
    TXBUF0 = ATCMGF[i];           
    while((IFG1 & UTXIFG0)==0);
  }
  DelayNS(150);
  for(i=0;i<13;i++)
  {
    TXBUF0 = ATCN[i];           
    while((IFG1 & UTXIFG0)==0);
  }
  DelayNS(150);
  for(i=0;i<12;i++)
  {
    TXBUF0 = ATNUM[i];       //短信长度
    while((IFG1 & UTXIFG0)==0);
  }
  DelayNS(150);
  for(i=0;i<82;i++)
  {
    TXBUF0 = ATCMGS[i];       //短信编码
    while((IFG1 & UTXIFG0)==0);
  }
  TXBUF0 = 0x1a;              //结束符
  while(!(IFG1 & UTXIFG0));
  P1IFG &=~BIT7;	//清除标志位
  P1IE |= BIT7;	//打开中断
}