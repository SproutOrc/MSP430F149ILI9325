#ifndef __ISD4004_H__
#define __ISD4004_H__

//������ͷ�ļ�
#include<msp430x14x.h>
#include"global.h"  
//isd4004����λ�궨��
#define ISD_MISO BIT0   //���������
#define ISD_MOSI BIT1   //���������
#define ISD_SS  BIT2    //Ƭѡ��
#define ISD_SCLK BIT3   //ʱ�Ӷ�
#define BUTTON BIT4     //��������
#define ISD_RINT BIT6   //�ж϶�
//isd4004���ƼĴ����궨��
#define ISD_OUT P1OUT
#define ISD_IN  P1IN
#define ISD_DIR P1DIR

//ISD4004��������˺궨��
#define ISD_MISO_OUT  ISD_DIR |= ISD_MISO         //
#define ISD_MISO_IN  ISD_DIR &= ~ISD_MISO
#define ISD_MISO_H  ISD_OUT |= ISD_MISO           //
#define ISD_MISO_L  ISD_OUT &= ~ISD_MISO          //


//ISD4004��������˺궨��
#define ISD_MOSI_OUT  ISD_DIR |= ISD_MOSI         //
#define ISD_MOSI_IN  ISD_DIR &= ~ISD_MOSI
#define ISD_MOSI_H  ISD_OUT |= ISD_MOSI           //
#define ISD_MOSI_L  ISD_OUT &= ~ISD_MOSI          //


//ISD4004Ƭѡ�˺궨��
#define ISD_SS_OUT  ISD_DIR |= ISD_SS             //
#define ISD_SS_IN  ISD_DIR &= ~ISD_SS
#define ISD_SS_H  ISD_OUT |= ISD_SS               //
#define ISD_SS_L  ISD_OUT &= ~ISD_SS              //


//ISD4004ʱ�Ӷ˺궨��
#define ISD_SCLK_OUT  ISD_DIR |= ISD_SCLK         //
#define ISD_SCLK_IN  ISD_DIR &= ~ISD_SCLK
#define ISD_SCLK_H  ISD_OUT |= ISD_SCLK           //
#define ISD_SCLK_L  ISD_OUT &= ~ISD_SCLK          //


//��������
 void ISD4004_Reset(void);
 void ISD4004_WriteChar(uchar z);
 void ISD4004_PowerUp_Rec(void);
 void ISD4004_PowerUp_Play(void);
 void ISD4004_Stop(void);
 void ISD4004_StopDown(void);
 void ISD4004_SetPlay(uint z);
 void ISD4004_Play(void);
 void ISD4004_SetRec(uint z);
 void ISD4004_Rec(void);
 void  ISD4004_Init();
#endif