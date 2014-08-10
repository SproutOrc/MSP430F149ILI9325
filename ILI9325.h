#ifndef ILI9325_H
#define ILI9325_H

#include <msp430X14X.h>
//============================================================
//根据芯片资料定义
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
//定义TFT彩屏模块接口
#define TFT_RS_1  P2OUT |= BIT3;	//数据/命令选择
#define TFT_RS_0  P2OUT &= ~BIT3;

#define TFT_WR_1  P2OUT |= BIT4;	//写
#define TFT_WR_0  P2OUT &= ~BIT4;

#define TFT_RD_1  P2OUT |= BIT5;	//读
#define TFT_RD_0  P2OUT &= ~BIT5;

#define TFT_CS_1  P2OUT |= BIT6;	//片选
#define TFT_CS_0  P2OUT &= ~BIT6;

#define TFT_RST_1 P2OUT |= BIT7;	//复位
#define TFT_RST_0 P2OUT &= ~BIT7;

//#define TFT_DATA P4OUT	//数据口



//=============================================================
//函数声明
void InitPort(void);
void ILI9325_initial(void);//TFT初始化
void write_cmd(unsigned char CH,unsigned char CL);//写命令
void write_data(unsigned char DH,unsigned char DL);//写数据
void write_data_u16(unsigned int dat);//写16位数据
void write_cmd_data (unsigned char cmd,unsigned int dat);//写命令数据
void LCD_setwindow(unsigned char x0,unsigned int y0,unsigned char x1,unsigned int y1);//设置窗口
void LCD_setxy(unsigned char x,unsigned int y);//设定当前显示坐标
void LCD_test();//彩条、单色自测程序


#endif











