#ifndef __GSM_H__
#define __GSM_H__
#define uint unsigned int
#define uchar unsigned char

//控制位的宏定义
#define Ctrl_Out  P6DIR |= BIT3 + BIT6 + BIT7;
#define Ctrl_0    P6OUT &= ~(BIT3 + BIT6 + BIT7)
#define SRCLK_1   P6OUT |= BIT7
#define SRCLK_0   P6OUT &= ~BIT7
#define SER_1     P6OUT |= BIT6
#define SER_0     P6OUT &= ~BIT6
#define RCLK_1    P6OUT |= BIT3
#define RCLK_0    P6OUT &= ~BIT3
void UART0_Init(void);
//板上资源配置函数
void BoardConfig(uchar cmd);
void DelayNS(unsigned int dly);
void GsmSend1(void);

void InitGSM();

#endif
