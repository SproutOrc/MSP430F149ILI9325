#include <msp430x14x.h>
#include "display.h"
#include "global.h"
#include "gui.h"
#include "ILI9325.h"
#include "interface.h"

void Init_Clk(void)
{
    uint delay;
    BCSCTL1 &= ~XT2OFF;                    // XT2OFF:控制XT2振荡器的开启(XT2OFF=0)
    BCSCTL2 |= SELM_2 + SELS;               //SELS:选择SMCLK的时钟源,0:DCOCLK;1:XT2CLK.   
    for(delay=5000;delay>0;delay--);	   //SELM0~1:选择MCLK的时钟源,0,1:DCOCLK,2:XT2CLK,3:LFXT1CLK
            IFG1 &=~OFIFG;      			   //晶振故障中断标志位  
    TACCR0=0XFFFF; 
  
}

void main(void) 																  
{	
    WDTCTL = WDTPW + WDTHOLD;    // 关闭看门狗 

    Init_Clk();		//时钟初始化
    DelayMs(50);   
    InitPort();     //彩屏端口初始化
    
    ILI9325_initial();    //液晶初始化程序
    DelayMs(50);
    GUI_clearscreen(WHITE);
    MAIN_WINDOW();
    LPM4;
    // _BIS_SR(LPM3 + GIE);//进入低功耗模式
    while(1)
    {
        
    }
    
}