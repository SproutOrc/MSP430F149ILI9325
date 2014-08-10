#include "IR.h"
#include "gui.h"
#include "global.h"
#include "display.h"
#include "motor.h"
#include "ds18b20.h"
#include "GSM.h"
#include "isd4004.h"

uchar password[6]={1,2,3,4,5,6}; 
unsigned char Ir_Buf[4];                              // ���ڱ��������
uchar IR_KeyValue,FlagIR,FlagTemp,FlagRed;

void Init_Clk(void)
{
    uint delay;
    BCSCTL1 &= ~XT2OFF;                    // XT2OFF:����XT2�����Ŀ���(XT2OFF=0)
    BCSCTL2 |= SELM_2 + SELS;               //SELS:ѡ��SMCLK��ʱ��Դ,0:DCOCLK;1:XT2CLK.   
    for(delay=5000;delay>0;delay--);	   //SELM0~1:ѡ��MCLK��ʱ��Դ,0,1:DCOCLK,2:XT2CLK,3:LFXT1CLK
            IFG1 &=~OFIFG;      			   //��������жϱ�־λ  
    TACCR0=0XFFFF; 
  
}
void CLK_Reset()						  //ʱ��ϵͳ��λ
{
    uint delay;
    BCSCTL1 |= XT2OFF;                    // ����XT2����(��Ƶ����8M)
    BCSCTL2 &= ~(SELM1 + SELS);               //SELS = 1:ѡ��XT2CLK ��ΪSMCLK��ʱ��Դ  
    for(delay=5000;delay>0;delay--);	   //SELM1 = 1:ѡ��DCOCLK��ΪMCLK��ʱ��Դ
            IFG1 |= OFIFG;      			   //��������жϱ�־λ 
    TACCR0=0;	
}
void InitIR(void)
{
    P2DIR &=~BIT0;//����Ϊ����
    P2SEL &=~BIT0;//ѡ��Ϊ����ģ��
    P2IES |= BIT0;//ѡ�񴥷���ʽ1Ϊ�½��ش�����0������
    P2IE  |= BIT0;//ʹ���ж�
    P2IFG &=~BIT0;//�����־λ
    //P1DIR |= BIT4+BIT5+BIT6;
}
void IR(void)
{
    uchar i,j;
    uint temp=0;
    if((P2IFG&BIT0)==BIT0) //��if�����Ҫ�����ж�ǰ��������
    {
      P2IFG &=~BIT0;//����жϱ�־λ
      P2IE  &=~BIT0;//�ر��ж�
    }
loop:	//��������룬��⵽������ͨ���󣬽��пͻ����������Ķ�ȡ				 
    for(i=0;i<4;i++)
    {
	    if(Ir_Pin==0) break;	//���P1.7��⵽�͵�ƽ�����˳�ѭ��
	 	if(i==3)
	 	{
			P2IE |= BIT0;      //ʹ��P1.7�ж�
			return;
	  	}
    }
	DelayUs(270);  //��ʱ270us
    if(Ir_Pin)     //���P1.7��⵽�Ļ��Ǹߵ�ƽ���ٴν����� 
      goto loop;   
    while(!Ir_Pin);//�ȴ������źŵ���
	
    for(i=0;i<4;i++)                        //4���ֽ�      
      for(j=0;j<8;j++)                        //ÿ���ֽ�8λ 
      {  
         while(Ir_Pin)  	
         DelayUs(130);	//�ȴ��͵�ƽ
         while(!Ir_Pin)		
         DelayUs(130);	//�ȴ��ߵ�ƽ
         while(Ir_Pin)		//����ߵ�ƽʱ��
         {
            DelayUs(130);
            temp++;
            if(temp>=30)
            {
              P2IE |= BIT0;	//ʹ���ж�
              return;
            }
         } 
         Ir_Buf[i]>>=1;		//��������һλ  
         if(temp>11) 
         	Ir_Buf[i]|=0x80;//����ߵ�ƽʱ�����1.69ms���λ��1���������Ӹ�λ����
         temp = 0;
      }
      IR_KeyValue=Ir_Buf[2];
      Scan_Ir();		//����ɨ��
      if(FlagIR)
        KeyPro();
      P2IFG &=~BIT0;	//�����־λ
      P2IE |= BIT0;	//���ж�
      
}
void Scan_Ir(void)
{
  
  if(IR_KeyValue==0x46)
  {
    FlagIR=1;
    FlagTemp=0;
    FlagRed=0;
    GUI_clearscreen(0);//����
    GUI_box(0,0,239,15,0x001f);			 //���ϽǶ������꣬���½Ƕ������꣬��ɫ
    GUI_sprintf_HZ1(1, 0, 0x07ff,0x001f);//��ʾԤ���庺���ַ���	��ʾ�������Ͻ����꣬��ɫ��������ɫ
    GUI_box(0,16,99,31,GRAY);
    GUI_box(100,16,239,31,GRAY);
    GUI_sprintf_HZ2(0, 16, BLACK,GRAY);
    ISD4004_SetPlay(0x0030);//����������
    //DelayMs(20);      	
  }
  if(IR_KeyValue==0X47)
  {
    FlagIR=0;
    FlagRed=0;
    FlagTemp=1;
    DelayMs(5);
    //P3DIR |=BIT2; //P3.2Ϊ�����ʽ
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
  if(IR_KeyValue==0X43)//����
  {
    FlagIR=0;
    FlagTemp=0;
    MotorLeft();
    DelayMs(2000);
    //ISD4004_SetPlay(0x0000);//���
    //RelayClose();
    FlagRed=1;
    
  }
  if(IR_KeyValue==0X40)//�����
  {
    FlagIR=0;
    FlagTemp=0;
    RelayOpen();
    FlagRed=1;
    
  }
  if(IR_KeyValue==0X44)//�����
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
    case 0x09:num=10;break;//ȷ��
    case 0x07:num=11;break;//ɾ��
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
  
  if(num!=16)   //���ɨ���ǰ�����Чֵ����д���
  { 
    
    if(k==0)
      GUI_box(100,16,239,31,GRAY);  
    if(k<6)     //������6λ������6λʱ�������밴��ֵ
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
    k++;   //������ֵ�ۼ�
    
    if(num==10)//6λ��İ�����������ֵ���൱��ȷ�ϰ��������ⰴ�����ɣ�
    {
      k=0;  //��������λ
      num=16;
      Flag=1;//�ȰѱȽ�λ��1
      for(j=0;j<6;j++)//ѭ���Ƚ�8����ֵ�������һ������ ������FlagֵΪ0
        Flag=Flag&&(temp[j]==password[j]);//�Ƚ�����ֵ����������
      
      if(Flag)//����Ƚ�ȫ����ͬ����־λ��1
      { 
        
        GUI_box(100,16,239,31,GRAY);
        GUI_sprintf_string(100,16,"Right,Come in!",RED,GRAY);//������ȷ��ʾ����Ϣ
        ISD4004_SetPlay(0X90);//����������ȷ
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
          GUI_sprintf_string(100,16,"Wrong,Three Times!",RED,GRAY);//�����������
      
          Speaker();
        }
        GUI_box(100,16,239,31,GRAY);
        GUI_sprintf_string(100,16,"Wrong,Try again!",RED,GRAY);//���������ʾ��������
        ISD4004_SetPlay(0X0065);//�����������         
      }

    }    
  }
  
  
}
