#include "motor.h"
#include "global.h"
#define  A1  P5OUT |= BIT0;
#define  A_  P5OUT &= ~BIT0;
#define  B1  P5OUT |= BIT1;
#define  B_  P5OUT &= ~BIT1;
#define  C1  P5OUT |= BIT2;
#define  C_  P5OUT &= ~BIT2;
#define  D1  P5OUT |= BIT3;
#define  D_  P5OUT &= ~BIT3;
#define Coil_A   {A1;B_;C_;D_;} //A��ͨ�磬������ϵ�
#define Coil_B   {A_;B1;C_;D_;} //ͬ��
#define Coil_C   {A_;B_;C1;D_;}
#define Coil_D   {A_;B_;C_;D1;}
#define Coil_AB1 {A1;B1;C_;D_;}//AB��ͨ�磬������ϵ�
#define Coil_BC1 {A_;B1;C1;D_;}//BC��ͨ�磬������ϵ�
#define Coil_CD1 {A_;B_;C1;D1;}//CD��ͨ�磬������ϵ�
#define Coil_DA1 {A1;B_;C_;D1;}//D��ͨ�磬������ϵ�
#define Coil_OFF {A_;B_;C_;D_;}//ȫ���ϵ�

void InitMotor()
{
  P5DIR=0xff;
}
void Speaker()
{
  P5OUT &= ~BIT5;
  DelayMs(20);
  P5OUT |= BIT5;
  DelayMs(20);
}
void RelayOpen()
{
  P5OUT |=BIT4;
  P1IE |= BIT7;	//���ж�
}
void RelayClose()
{
  P5OUT &=~BIT4;
  P1IE &= ~BIT7;	//�ر��ж�
}
void MotorRight()
{
  Coil_AB1
  DelayMs(25);
  for(uchar i=0;i<64;i++)
  {    
    Coil_BC1
    DelayMs(25);
    Coil_CD1
    DelayMs(25);
    Coil_DA1
    DelayMs(25);
    Coil_AB1
    DelayMs(25);
  }
  P1IE &= ~BIT7;	//�ر��ж�
}
void MotorLeft()
{
  Coil_DA1
  DelayMs(25);
  for(uchar i=0;i<64;i++)
  {    
    Coil_CD1
    DelayMs(25);
    Coil_BC1
    DelayMs(25);
    Coil_AB1
    DelayMs(25);
    Coil_DA1
    DelayMs(25);
  } 
  P1IE |= BIT7;	//���ж�
}