#include "key.h"
#include "global.h"
#include "gui.h"
#include "ILI9325.h"
#include "IR.h"
#include "display.h"
#include <msp430x14x.h>

//��������
uchar password[6]={0,3,1,0,1,6};
#define ROW P1OUT       //������̵��к궨��
#define COL P1IN        //������̵��к궨��

extern unsigned char Ir_Buf[4];                              // ���ڱ��������
unsigned char keyval;   //��ֵ
uchar num,KeyFlag=1;
/*******************************************************
*�������ƣ�keyscan()
*��    �ܣ�ɨ��4*3������̣������ؼ�ֵ
*���ڲ��������а����򷵻ؼ�ֵ�����ް�������15
*4*3������̣� 0  1  2  3
*              4  5  6  7
*              8  9  A  b
*******************************************************/
unsigned char KeyScan()
{
  unsigned char key=0;
  ROW = 0x0f;        //������������͵�ƽ
  if((COL & 0x0f)!= 0x0f) //�Ƿ��а���
  {
    DelayMs(300);        
    
  
    ROW = 0xbf;           //ɨ���һ��
    if((COL & 0x0f)== 0x0f)
    { ROW = 0xdf;         //ɨ��ڶ���
      if((COL & 0x0f)== 0x0f)
      { ROW = 0xef;       //ɨ�������
        if((COL & 0x0f)== 0x0f)
          key = 16;
        else key = ~((ROW & 0XF0)|(COL & 0X0F));
      }
      else key = ~((ROW & 0XF0)|(COL & 0X0F));
    }
    else key = ~((ROW & 0XF0)|(COL & 0X0F));

    if(key != 16)
     switch(key)      //��ȡ��Ч�ؼ�ֵ
     {

       case 0x48: key=0; break;
       case 0x44: key=1; break;
       case 0x42: key=2; break;
       case 0x41: key=3; break;
       case 0x28: key=4; break;
       case 0x24: key=5; break;
       case 0x22: key=6; break;
       case 0x21: key=7; break;
       case 0x18: key=8; break;
       case 0x14: key=9; break;
       case 0x12: key=10;break;
       case 0x11: key=11;break;
       default: key=16;
     }
  }
  else key = 16;
  keyval=key;
  return key;
}
void InitKeyPad()
{
  
  P1DIR |= BIT4+BIT5+BIT6; //�����þ�����̵��У������
}
void KeyPro()
{
  uchar j,Flag;
  uchar static WrongTime,k;
  uchar temp[6];
  num=KeyScan();
  
  if(num!=16)   //���ɨ���ǰ�����Чֵ����д���
  { 
    
    if(k==0)
      GUI_box(100,16,239,31,GRAY);  
    if(k<6)     //������6λ������6λʱ�������밴��ֵ
    {
      temp[k]=num;
      GUI_sprintf_char(100+k*9,16,num+'0',YELLOW,GRAY);   
    }
    k++;   //������ֵ�ۼ�
    
    if(k==7)//6λ��İ�����������ֵ���൱��ȷ�ϰ��������ⰴ�����ɣ�
    {
      k=0;  //��������λ
      
      Flag=1;//�ȰѱȽ�λ��1
      for(j=0;j<6;j++)//ѭ���Ƚ�8����ֵ�������һ������ ������FlagֵΪ0
         Flag=Flag&&(temp[j]==password[j]);//�Ƚ�����ֵ����������
      KeyFlag=0;
      if(Flag)//����Ƚ�ȫ����ͬ����־λ��1
      { 
        GUI_box(100,16,239,31,GRAY);
        GUI_sprintf_string(100,16,"Right,Come in!",RED,GRAY);//������ȷ��ʾ����Ϣ
        WrongTime=0;
        Flag=0;
      }
      else 
      { 
        ++WrongTime;
        if(WrongTime==3)
        {
          GUI_box(100,16,239,31,GRAY);
          GUI_sprintf_string(100,16,"Wrong,Three Times!",RED,GRAY);//�����������
          KeyFlag=0;
         // while(1);
        }
        GUI_box(100,16,239,31,GRAY);
        GUI_sprintf_string(100,16,"Wrong,Try again!",RED,GRAY);//���������ʾ��������
                 
      }

    }    
  }
  
  
}
