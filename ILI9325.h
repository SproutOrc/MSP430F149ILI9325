#ifndef ILI9325_H
#define ILI9325_H

#include <msp430X14X.h>
//============================================================
//����оƬ���϶���
#define WINDOW_XADDR_START	0x0050 // Horizontal Start Address Set
#define WINDOW_XADDR_END	0x0051 // Horizontal End Address Set
#define WINDOW_YADDR_START	0x0052 // Vertical Start Address Set
#define WINDOW_YADDR_END	0x0053 // Vertical End Address Set
#define GRAM_XADDR		0x0020 // GRAM Horizontal Address Set
#define GRAM_YADDR		0x0021 // GRAM Vertical Address Set
#define GRAMWR 			0x0022 // memory write
#define GUI_LCM_YMAX 319
#define GUI_LCM_XMAX 239

//=============================================================
//����TFT����ģ��ӿ�
#define TFT_RS_1  P2OUT |= BIT3;	//����/����ѡ��
#define TFT_RS_0  P2OUT &= ~BIT3;

#define TFT_WR_1  P2OUT |= BIT4;	//д
#define TFT_WR_0  P2OUT &= ~BIT4;

#define TFT_RD_1  P2OUT |= BIT5;	//��
#define TFT_RD_0  P2OUT &= ~BIT5;

#define TFT_CS_1  P2OUT |= BIT6;	//Ƭѡ
#define TFT_CS_0  P2OUT &= ~BIT6;

#define TFT_RST_1 P2OUT |= BIT7;	//��λ
#define TFT_RST_0 P2OUT &= ~BIT7;

//#define TFT_DATA P4OUT	//���ݿ�



//=============================================================
//��������
void InitPort(void);
void ILI9325_initial(void);//TFT��ʼ��
void write_cmd(unsigned char CH,unsigned char CL);//д����
void write_data(unsigned char DH,unsigned char DL);//д����
void write_data_u16(unsigned int dat);//д16λ����
void write_cmd_data (unsigned char cmd,unsigned int dat);//д��������
void LCD_setwindow(unsigned char x0,unsigned int y0,unsigned char x1,unsigned int y1);//���ô���
void LCD_setxy(unsigned char x,unsigned int y);//�趨��ǰ��ʾ����
void LCD_test();//��������ɫ�Բ����


#endif











