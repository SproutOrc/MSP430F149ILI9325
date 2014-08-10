#ifndef __IR_H__
#define __IR_H__

#include"global.h"
#include<msp430x14x.h>
#define Ir_Pin  (P2IN & BIT0) //定义红外接收头端口



void Scan_Ir(void);
void InitIR(void);
void IR(void);
void CLK_Reset();
void Init_Clk(void);
uchar IR_Value();
void KeyPro();

#endif