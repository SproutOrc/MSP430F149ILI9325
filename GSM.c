#include<msp430x14x.h>
#include "GSM.h"
#include "isd4004.h"
void GsmSend(void);
void UART0_Init (void);
void DelayNS (unsigned int dly);
void Delay(unsigned long t);
//��ʾ��pud�ķ�ʽ���Ͷ���
unsigned char ATCMGF[]="AT+CMGF=0\r\n";  
//���ö���Ϣ֪ͨ��Ƭ�������
unsigned char ATCN[]="AT+CNMI=2,1\r\n";
//����PUD��ʽ����:���˴���
uchar ATCMGS[]="0891683108701905F011000B818177004940F50008A71253EF75914EBA5458722C7A9751655C4BFF01";
//uart��ʼ��
void InitGSM()
{
  //BoardConfig(0xb8);
  P1DIR &=~BIT7;//����Ϊ����
  P1SEL &=~BIT7;//ѡ��Ϊ����ģ��
  P1IES |= BIT7;//ѡ�񴥷���ʽ1Ϊ�½��ش�����0������
  P1IE  |= BIT7;//ʹ���ж�
  P1IFG &=~BIT7;//�����־λ
  
  //P1DIR &=~BIT6;//����Ϊ����
  //P1SEL &=~BIT6;//ѡ��Ϊ����ģ��
  //P1IES &=~BIT6;//ѡ�񴥷���ʽ1Ϊ�½��ش�����0������
  //P1IE  |= BIT6;//ʹ���ж�
  //P1IFG &=~BIT6;//�����־λ
   
  UART0_Init();
}
//uart��ʼ��
void UART0_Init(void)
{
  /*ME1 |= UTXE0 +URXE0;         //ʹ��UART0��TXD��RXD
  UCTL0 = CHAR;                //ѡ���λ�ַ�
  UTCTL0 = SSEL0;              //UCLK=ACLK
  UBR00 = 0X03;                //����������Ϊ9600
  UBR10 = 0X00;
  UMCTL0 =0X4A;               //USART0ģʽ����
  UCTL0 &= ~SWRST;            //��ʼ��UART���ƻ�
  IE1 |= URXIE0;              //ʹ��UART0��RX�����ж�
  P3SEL = 0X30;               //����P3.4/P3.5ΪUART0��txd��rxd
  P3DIR = 0x10;               //����P3.4Ϊ����ܽ�
  */
  BCSCTL1 &= ~XT2OFF;          // XT2on
  BCSCTL2 |= SELM_2 + SELS;    // MCLK = SMCLK = XT2 (safe)
  ME1 |= UTXE0 +URXE0;         //ʹ��UART0��TXD��RXD
  UCTL0 |= CHAR;                //ѡ���λ�ַ�
  UTCTL0 |= SSEL1;              //UCLK=ACLK
  UBR00 = 0XA0;                //����������Ϊ19200
  UBR10 = 0X01;
  UMCTL0 =0X00;               //USART0ģʽ����
  UCTL0 &= ~SWRST;            //��ʼ��UART���ƻ�
  IE1 |= URXIE0;              //ʹ��UART0��RX�����ж�
  P3SEL = 0X30;               //����P3.4/P3.5ΪUART0��txd��rxd
  P3DIR = 0x10;               //����P3.4Ϊ����ܽ�
}
//ʱ���ӳ�
void DelayNS(unsigned int dly)  
{
  unsigned int i;
  for(;dly>0;dly--)
    for(i=0;i<2000;i++);
}
//��Ϣ����
void GsmSend1(void)
{
  unsigned char ATNUM[]="AT+CMGS=32\r\n";
  unsigned char i;
  if((P1IFG&BIT7)==BIT7) //��if�����Ҫ�����ж�ǰ��������
 {
      P1IFG &=~BIT7;//����жϱ�־λ
      P1IE  &=~BIT7;//�ر��ж�
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
    TXBUF0 = ATNUM[i];       //���ų���
    while((IFG1 & UTXIFG0)==0);
  }
  DelayNS(150);
  for(i=0;i<82;i++)
  {
    TXBUF0 = ATCMGS[i];       //���ű���
    while((IFG1 & UTXIFG0)==0);
  }
  TXBUF0 = 0x1a;              //������
  while(!(IFG1 & UTXIFG0));
  P1IFG &=~BIT7;	//�����־λ
  P1IE |= BIT7;	//���ж�
}