#include "ILI9325.h"
#include "global.h"

/*颜色数值:红色，绿色，蓝色，黄色，黑色，白色，天蓝色，紫色*/
unsigned int color[]={0xf800,0x07e0,0x001f,0xffe0,0x0000,0xffff,0x07ff,0xf81f};

//端口初始化函数
void InitPort(void)
{
  P2SEL = 0x00;
  P2DIR=0XF8;
  P4SEL = 0x00;
  P4DIR=0XFF;
  
}
//=============================================================
//TFT初始化
//功能：该函数用于初始化TFT彩屏模块。
//入口参数: 无
//出口参数: 无
void ILI9325_initial(void)
{ 
    InitPort();
	TFT_CS_1;
	DelayMs(5);
	TFT_RST_0;
	DelayMs(5);
	TFT_RST_1;
	DelayMs(20);//可以适当调整延时，保障稳定显示
	write_cmd_data(0x0001,0x0100); //源扫描设置SS=0, 输出的移动方向是从S1到S720
	//（源扫描设置SS=1, 输出的移动方向是从S720到S1）
	//SM=0，逐行扫描（SM=1，隔行扫描）

	write_cmd_data(0x0002,0x0700); //B/C=1、EOR=1：行倒置（B/C=0：帧/场倒置）
	write_cmd_data(0x0003,0x1030); //AM=0，地址在水平方向自动加1
	//I/D[1:0] = 11：水平垂直方向均增加
	//BGR=1:采用BGR格式
	//TRI=0、DFM=*：8位机、两次数据传送
	write_cmd_data(0x0004,0x0000); //比例缩放设置：不缩放
	
	//显示控制
	write_cmd_data(0x0008,0x0207); //设置后边沿和前沿 
	write_cmd_data(0x0009,0x0000);//设置非显示区时间间隔ISC[3:0]
	write_cmd_data(0x000A,0x0000); //帧标记功能

	write_cmd_data(0x000C,0x0000);//RGB显示接口控制1
	write_cmd_data(0x000D,0x0000);//帧标记位置
	write_cmd_data(0x000F,0x0000);//RGB显示接口控制2
	
	//电源配置
	write_cmd_data(0x0010,0x0000);   
	write_cmd_data(0x0011,0x0007);  
	write_cmd_data(0x0012,0x0000);  
	write_cmd_data(0x0013,0x0000); 
	//vgh 
	write_cmd_data(0x0010,0x1290);   
	write_cmd_data(0x0011,0x0227);
	//delayms(100);
	//vregiout 
	write_cmd_data(0x0012,0x001d); //0x001b
	//delayms(100); 
	//vom amplitude
	write_cmd_data(0x0013,0x1500);
	//delayms(100); 
	//vom H
	write_cmd_data(0x0029,0x0018); 
	write_cmd_data(0x002B,0x000D); 
	
	//伽马校正
	write_cmd_data(0x0030,0x0004);
	write_cmd_data(0x0031,0x0307);
	write_cmd_data(0x0032,0x0002);//0006
	write_cmd_data(0x0035,0x0206);
	write_cmd_data(0x0036,0x0408);
	write_cmd_data(0x0037,0x0507); 
	write_cmd_data(0x0038,0x0204);//0200
	write_cmd_data(0x0039,0x0707); 
	write_cmd_data(0x003C,0x0405);//0504
	write_cmd_data(0x003D,0x0F02); 
	
	//窗口设置
	write_cmd_data(0x0050,0x0000);//水平起始位置
	write_cmd_data(0x0051,0x00EF);//水平终止位置
	write_cmd_data(0x0052,0x0000);//垂直起始位置
	write_cmd_data(0x0053,0x013F);//垂直终止位置

	write_cmd_data(0x0060,0xA700);//门扫描设置，GS=1：从G320扫描到G1，320线
	write_cmd_data(0x0061,0x0001); 
	write_cmd_data(0x006A,0x0000);
	//
	write_cmd_data(0x0080,0x0000); 
	write_cmd_data(0x0081,0x0000); 
	write_cmd_data(0x0082,0x0000); 
	write_cmd_data(0x0083,0x0000); 
	write_cmd_data(0x0084,0x0000); 
	write_cmd_data(0x0085,0x0000); 
	//
	write_cmd_data(0x0090,0x0010); 
	write_cmd_data(0x0092,0x0600); 
	write_cmd_data(0x0093,0x0003); 
	write_cmd_data(0x0095,0x0110); 
	write_cmd_data(0x0097,0x0000); 
	write_cmd_data(0x0098,0x0000);
	write_cmd_data(0x0007,0x0133);
	//write_cmd_data(0x0022);		
}


//=============================================================
//写命令
//功能：写一个命令到TFT控制器。
//入口参数: CH,CL分别为命令字的高8位和低8位，指定要执行的命令。
//出口参数: 无
void write_cmd(unsigned char CH,unsigned char CL)
{
    TFT_RD_1;
	TFT_CS_0;
	TFT_RS_0;
	P4OUT=CH;
	TFT_WR_0;
	TFT_WR_1;
	P4OUT=CL;
	TFT_WR_0;
	TFT_WR_1;
	TFT_CS_1;
}


//===================================================================
//写数据
//功能：写一个数据到TFT控制器。
//入口参数: DH,DL分别为数据字的高8位和低8位，指定要写入的数据。
//出口参数: 无
void write_data(unsigned char DH,unsigned char DL)
{
	TFT_RD_1;
    TFT_CS_0;
	TFT_RS_1;
	P4OUT=DH;
	TFT_WR_0;
	TFT_WR_1;
	P4OUT=DL;	
	TFT_WR_0;
	TFT_WR_1;
	TFT_CS_1;
}


//==============================================================
//写16位数据
//功能： 写一个数据到TFT控制器。
//入口参数: dat为要写入的16位数据。
//出口参数: 无
void write_data_u16(unsigned int dat)
{
	unsigned char m,n;
	m=dat>>8;
	n=dat;
	write_data(m,n);
}


//===============================================================
//写命令数据
//功能： 写命令数据到TFT控制器。
//入口参数: cmd为要写入的命令字节；dat为要写入的16位数据。
//出口参数: 无
void write_cmd_data (unsigned char cmd,unsigned int dat)
{
	unsigned char m,n;
	m=dat>>8;
	n=dat;
	write_cmd(0x00,cmd);
	write_data(m,n);
}


//===============================================================
//设置窗口
//入口参数: x0 y0,为显示窗口左上角坐标；x1,y1为显示窗口右下角坐标。
//出口参数: 无
//说明：该函数设置TFT模块的显示窗口。
void LCD_setwindow(unsigned char x0,unsigned int y0,unsigned char x1,unsigned int y1)
{
	write_cmd_data(WINDOW_XADDR_START,x0);//水平起始位置
	write_cmd_data(WINDOW_XADDR_END,x1);//水平终止位置
	write_cmd_data(WINDOW_YADDR_START,y0);//垂直起始位置
	write_cmd_data(WINDOW_YADDR_END,y1);//垂直终止位置
	write_cmd_data(GRAM_XADDR,x0);//设置X坐标位置
	write_cmd_data(GRAM_YADDR,y0);//设置Y坐标位置
	write_cmd(0x00,0x22);//LCD_WriteCMD(GRAMWR);
}


//===============================================================
//设定当前显示坐标
//入口参数: x,y为当前显示坐标。
//出口参数: 无
//说明：本函数实际上是LCD_setwindow函数的一个特例，显示窗口为最小，仅是一个像素点。
void LCD_setxy(unsigned char x,unsigned int y)
{
	LCD_setwindow(x,y,x,y);	
}

//===============================================================
//彩条、单色自测程序
//入口参数: 无。
//出口参数: 无
//说明：在TFT屏上轮流显示彩条和各种颜色的单色屏幕。
void LCD_test()
{
	unsigned int temp,num;
	unsigned char n,c;

	//显示彩条	
	LCD_setwindow(0,0,239,319);
	for(n=0;n<8;n++)
	{
	   temp=color[n];										
		for(num=40*240;num>0;num--)
	   	write_data_u16(temp);
	}
	DelayMs(1);

	//显示单色彩色
	for(c=0;c<8;c++)
	{
		temp = color[c];
		LCD_setwindow(0,0,239,319);
		for(n=0;n<240;n++)
		{
			for(num=0;num<320;num++)
			  write_data_u16(temp);
	 	}
   	DelayMs(1);
	}
}



