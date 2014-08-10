#include "IR.h"
#include "gui.h"
#include "global.h"
#include "display.h"
#include "motor.h"
#include "ds18b20.h"
#include "GSM.h"
#include "isd4004.h"

uchar password[6]={1,2,3,4,5,6}; 
unsigned char Ir_Buf[4];                              // 用于保存解码结果
uchar IR_KeyValue,FlagIR,FlagTemp,FlagRed;

void Init_Clk(void)
{
    uint delay;
    BCSCTL1 &= ~XT2OFF;                    // XT2OFF:控制XT2振荡器的开启(XT2OFF=0)
    BCSCTL2 |= SELM_2 + SELS;               //SELS:选择SMCLK的时钟源,0:DCOCLK;1:XT2CLK.   
    for(delay=5000;delay>0;delay--);	   //SELM0~1:选择MCLK的时钟源,0,1:DCOCLK,2:XT2CLK,3:LFXT1CLK
            IFG1 &=~OFIFG;      			   //晶振故障中断标志位  
    TACCR0=0XFFFF; 
  
}
void CLK_Reset()						  //时钟系统复位
{
    uint delay;
    BCSCTL1 |= XT2OFF;                    // 开启XT2振荡器(高频振荡器8M)
    BCSCTL2 &= ~(SELM1 + SELS);               //SELS = 1:选择XT2CLK 作为SMCLK的时钟源  
    for(delay=5000;delay>0;delay--);	   //SELM1 = 1:选择DCOCLK作为MCLK的时钟源
            IFG1 |= OFIFG;      			   //晶振故障中断标志位 
    TACCR0=0;	
}
void InitIR(void)
{
    P2DIR &=~BIT0;//配置为输入
    P2SEL &=~BIT0;//选择为功能模块
    P2IES |= BIT0;//选择触发方式1为下降沿触发，0上升沿
    P2IE  |= BIT0;//使能中断
    P2IFG &=~BIT0;//清除标志位
    //P1DIR |= BIT4+BIT5+BIT6;
}
void IR(void)
{
    uchar i,j;
    uint temp=0;
    if((P2IFG&BIT0)==BIT0) //此if语句主要用于中断前的清理工作
    {
      P2IFG &=~BIT0;//清除中断标志位
      P2IE  &=~BIT0;//关闭中断
    }
loop:	//检测引导码，检测到引导码通过后，进行客户码和数据码的读取				 
    for(i=0;i<4;i++)
    {
	    if(Ir_Pin==0) break;	//如果P1.7检测到低电平，则退出循环
	 	if(i==3)
	 	{
			P2IE |= BIT0;      //使能P1.7中断
			return;
	  	}
    }
	DelayUs(270);  //延时270us
    if(Ir_Pin)     //如果P1.7检测到的还是高电平，再次进入检测 
      goto loop;   
    while(!Ir_Pin);//等待红外信号到来
	
    for(i=0;i<4;i++)                        //4个字节      
      for(j=0;j<8;j++)                        //每个字节8位 
      {  
         while(Ir_Pin)  	
         DelayUs(130);	//等待低电平
         while(!Ir_Pin)		
         DelayUs(130);	//等待高电平
         while(Ir_Pin)		//计算高电平时间
         {
            DelayUs(130);
            temp++;
            if(temp>=30)
            {
              P2IE |= BIT0;	//使能中断
              return;
            }
         } 
         Ir_Buf[i]>>=1;		//数据右移一位  
         if(temp>11) 
         	Ir_Buf[i]|=0x80;//如果高电平时间大于1.69ms则高位补1，红外解码从高位读起
         temp = 0;
      }
      IR_KeyValue=Ir_Buf[2];
      Scan_Ir();		//红外扫描
      if(FlagIR)
        KeyPro();
      P2IFG &=~BIT0;	//清除标志位
      P2IE |= BIT0;	//打开中断
      
}
void Scan_Ir(void)
{
  
  if(IR_KeyValue==0x46)
  {
    FlagIR=1;
    FlagTemp=0;
    FlagRed=0;
    GUI_clearscreen(0);//清屏
    GUI_box(0,0,239,15,0x001f);			 //左上角顶点坐标，右下角顶点坐标，颜色
    GUI_sprintf_HZ1(1, 0, 0x07ff,0x001f);//显示预定义汉字字符串	显示内容左上角坐标，颜色，背景颜色
    GUI_box(0,16,99,31,GRAY);
    GUI_box(100,16,239,31,GRAY);
    GUI_sprintf_HZ2(0, 16, BLACK,GRAY);
    ISD4004_SetPlay(0x0030);//请输入密码
    //DelayMs(20);      	
  }
  if(IR_KeyValue==0X47)
  {
    FlagIR=0;
    FlagRed=0;
    FlagTemp=1;
    DelayMs(5);
    //P3DIR |=BIT2; //P3.2为输出方式
    TempInterFace();
    if(FlagTemp)
      init_TimerA();
  }
  if(IR_KeyValue==0X45)
  {
    FlagIR=0;
    FlagTemp=0;
    FlagRed=0;
    Display();
  }
  if(IR_KeyValue==0X43)//关门
  {
    FlagIR=0;
    FlagTemp=0;
    MotorLeft();
    DelayMs(2000);
    //ISD4004_SetPlay(0x0000);//设防
    //RelayClose();
    FlagRed=1;
    
  }
  if(IR_KeyValue==0X40)//设防开
  {
    FlagIR=0;
    FlagTemp=0;
    RelayOpen();
    FlagRed=1;
    
  }
  if(IR_KeyValue==0X44)//设防关
  {
    FlagIR=0; 
    FlagTemp=0;
    FlagRed=0;
    
    RelayClose();
  }
 
  
}
uchar IR_Value()
{
  uchar num;
  switch(IR_KeyValue)
  {
    case 0x16:num=0;break;
    case 0x0c:num=1;break;
    case 0x18:num=2;break;
    case 0x5e:num=3;break;
    case 0x08:num=4;break;
    case 0x1c:num=5;break;
    case 0x5a:num=6;break;
    case 0x42:num=7;break;
    case 0x52:num=8;break;
    case 0x4a:num=9;break;
    case 0x09:num=10;break;//确定
    case 0x07:num=11;break;//删除
    default  :break;
  }
  return num;
}

void KeyPro()
{
  uchar j,Flag,num;
  uchar static WrongTime,k;
  uchar temp[6];
  num=IR_Value();
  
  if(num!=16)   //如果扫描是按键有效值则进行处理
  { 
    
    if(k==0)
      GUI_box(100,16,239,31,GRAY);  
    if(k<6)     //密码是6位，大于6位时不再输入按键值
    {      
      if(num==11)
      {
        GUI_sprintf_char(100+(--k)*9,16,' ',GRAY,GRAY);
        temp[k--]=num;        
      }
      else
      {
        temp[k]=num;
        GUI_sprintf_char(100+k*9,16,'*',YELLOW,GRAY);
      }
    }
    k++;   //输入数值累加
    
    if(num==10)//6位后的按键不输入数值，相当于确认按键（任意按键即可）
    {
      k=0;  //计数器复位
      num=16;
      Flag=1;//先把比较位置1
      for(j=0;j<6;j++)//循环比较8个数值，如果有一个不等 则最终Flag值为0
        Flag=Flag&&(temp[j]==password[j]);//比较输入值和已有密码
      
      if(Flag)//如果比较全部相同，标志位置1
      { 
        
        GUI_box(100,16,239,31,GRAY);
        GUI_sprintf_string(100,16,"Right,Come in!",RED,GRAY);//密码正确显示的信息
        ISD4004_SetPlay(0X90);//密码输入正确
        MotorRight();
        //RelayClose();        
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
      
          Speaker();
        }
        GUI_box(100,16,239,31,GRAY);
        GUI_sprintf_string(100,16,"Wrong,Try again!",RED,GRAY);//密码错误，提示重新输入
        ISD4004_SetPlay(0X0065);//密码输入错误         
      }

    }    
  }
  
  
}
