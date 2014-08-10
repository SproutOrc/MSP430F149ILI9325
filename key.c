#include "key.h"
#include "global.h"
#include "gui.h"
#include "ILI9325.h"
#include "IR.h"
#include "display.h"
#include <msp430x14x.h>

//设置密码
uchar password[6]={0,3,1,0,1,6};
#define ROW P1OUT       //矩阵键盘的行宏定义
#define COL P1IN        //矩阵键盘的列宏定义

extern unsigned char Ir_Buf[4];                              // 用于保存解码结果
unsigned char keyval;   //键值
uchar num,KeyFlag=1;
/*******************************************************
*函数名称：keyscan()
*功    能：扫描4*3矩阵键盘，并返回键值
*出口参数：若有按键则返回键值，若无按键返回15
*4*3矩阵键盘： 0  1  2  3
*              4  5  6  7
*              8  9  A  b
*******************************************************/
unsigned char KeyScan()
{
  unsigned char key=0;
  ROW = 0x0f;        //先置三行输出低电平
  if((COL & 0x0f)!= 0x0f) //是否有按键
  {
    DelayMs(300);        
    
  
    ROW = 0xbf;           //扫描第一行
    if((COL & 0x0f)== 0x0f)
    { ROW = 0xdf;         //扫描第二行
      if((COL & 0x0f)== 0x0f)
      { ROW = 0xef;       //扫描第三行
        if((COL & 0x0f)== 0x0f)
          key = 16;
        else key = ~((ROW & 0XF0)|(COL & 0X0F));
      }
      else key = ~((ROW & 0XF0)|(COL & 0X0F));
    }
    else key = ~((ROW & 0XF0)|(COL & 0X0F));

    if(key != 16)
     switch(key)      //获取有效地键值
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
  
  P1DIR |= BIT4+BIT5+BIT6; //先配置矩阵键盘的行（输出）
}
void KeyPro()
{
  uchar j,Flag;
  uchar static WrongTime,k;
  uchar temp[6];
  num=KeyScan();
  
  if(num!=16)   //如果扫描是按键有效值则进行处理
  { 
    
    if(k==0)
      GUI_box(100,16,239,31,GRAY);  
    if(k<6)     //密码是6位，大于6位时不再输入按键值
    {
      temp[k]=num;
      GUI_sprintf_char(100+k*9,16,num+'0',YELLOW,GRAY);   
    }
    k++;   //输入数值累加
    
    if(k==7)//6位后的按键不输入数值，相当于确认按键（任意按键即可）
    {
      k=0;  //计数器复位
      
      Flag=1;//先把比较位置1
      for(j=0;j<6;j++)//循环比较8个数值，如果有一个不等 则最终Flag值为0
         Flag=Flag&&(temp[j]==password[j]);//比较输入值和已有密码
      KeyFlag=0;
      if(Flag)//如果比较全部相同，标志位置1
      { 
        GUI_box(100,16,239,31,GRAY);
        GUI_sprintf_string(100,16,"Right,Come in!",RED,GRAY);//密码正确显示的信息
        WrongTime=0;
        Flag=0;
      }
      else 
      { 
        ++WrongTime;
        if(WrongTime==3)
        {
          GUI_box(100,16,239,31,GRAY);
          GUI_sprintf_string(100,16,"Wrong,Three Times!",RED,GRAY);//密码错误三次
          KeyFlag=0;
         // while(1);
        }
        GUI_box(100,16,239,31,GRAY);
        GUI_sprintf_string(100,16,"Wrong,Try again!",RED,GRAY);//密码错误，提示重新输入
                 
      }

    }    
  }
  
  
}
