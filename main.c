#include <msp430x14x.h>
#include "display.h"
#include "global.h"
#include "gui.h"
#include "ILI9325.h"
#include "interface.h"

void Init_Clk(void)
{
    uint delay;
    BCSCTL1 &= ~XT2OFF;                    // XT2OFF:����XT2�����Ŀ���(XT2OFF=0)
    BCSCTL2 |= SELM_2 + SELS;               //SELS:ѡ��SMCLK��ʱ��Դ,0:DCOCLK;1:XT2CLK.   
    for(delay=5000;delay>0;delay--);	   //SELM0~1:ѡ��MCLK��ʱ��Դ,0,1:DCOCLK,2:XT2CLK,3:LFXT1CLK
            IFG1 &=~OFIFG;      			   //��������жϱ�־λ  
    TACCR0=0XFFFF; 
  
}

void main(void) 																  
{	
    WDTCTL = WDTPW + WDTHOLD;    // �رտ��Ź� 

    Init_Clk();		//ʱ�ӳ�ʼ��
    DelayMs(50);   
    InitPort();     //�����˿ڳ�ʼ��
    
    ILI9325_initial();    //Һ����ʼ������
    DelayMs(50);
    GUI_clearscreen(WHITE);
    MAIN_WINDOW();
    LPM4;
    // _BIS_SR(LPM3 + GIE);//����͹���ģʽ
    while(1)
    {
        
    }
    
}