#include "ILI9325.h"
#include "global.h"

/*��ɫ��ֵ:��ɫ����ɫ����ɫ����ɫ����ɫ����ɫ������ɫ����ɫ*/
unsigned int color[]={0xf800,0x07e0,0x001f,0xffe0,0x0000,0xffff,0x07ff,0xf81f};

//�˿ڳ�ʼ������
void InitPort(void)
{
  P2SEL = 0x00;
  P2DIR=0XF8;
  P4SEL = 0x00;
  P4DIR=0XFF;
  
}
//=============================================================
//TFT��ʼ��
//���ܣ��ú������ڳ�ʼ��TFT����ģ�顣
//��ڲ���: ��
//���ڲ���: ��
void ILI9325_initial(void)
{ 
    InitPort();
	TFT_CS_1;
	DelayMs(5);
	TFT_RST_0;
	DelayMs(5);
	TFT_RST_1;
	DelayMs(20);//�����ʵ�������ʱ�������ȶ���ʾ
	write_cmd_data(0x0001,0x0100); //Դɨ������SS=0, ������ƶ������Ǵ�S1��S720
	//��Դɨ������SS=1, ������ƶ������Ǵ�S720��S1��
	//SM=0������ɨ�裨SM=1������ɨ�裩

	write_cmd_data(0x0002,0x0700); //B/C=1��EOR=1���е��ã�B/C=0��֡/�����ã�
	write_cmd_data(0x0003,0x1030); //AM=0����ַ��ˮƽ�����Զ���1
	//I/D[1:0] = 11��ˮƽ��ֱ���������
	//BGR=1:����BGR��ʽ
	//TRI=0��DFM=*��8λ�����������ݴ���
	write_cmd_data(0x0004,0x0000); //�����������ã�������
	
	//��ʾ����
	write_cmd_data(0x0008,0x0207); //���ú���غ�ǰ�� 
	write_cmd_data(0x0009,0x0000);//���÷���ʾ��ʱ����ISC[3:0]
	write_cmd_data(0x000A,0x0000); //֡��ǹ���

	write_cmd_data(0x000C,0x0000);//RGB��ʾ�ӿڿ���1
	write_cmd_data(0x000D,0x0000);//֡���λ��
	write_cmd_data(0x000F,0x0000);//RGB��ʾ�ӿڿ���2
	
	//��Դ����
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
	
	//٤��У��
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
	
	//��������
	write_cmd_data(0x0050,0x0000);//ˮƽ��ʼλ��
	write_cmd_data(0x0051,0x00EF);//ˮƽ��ֹλ��
	write_cmd_data(0x0052,0x0000);//��ֱ��ʼλ��
	write_cmd_data(0x0053,0x013F);//��ֱ��ֹλ��

	write_cmd_data(0x0060,0xA700);//��ɨ�����ã�GS=1����G320ɨ�赽G1��320��
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
//д����
//���ܣ�дһ�����TFT��������
//��ڲ���: CH,CL�ֱ�Ϊ�����ֵĸ�8λ�͵�8λ��ָ��Ҫִ�е����
//���ڲ���: ��
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
//д����
//���ܣ�дһ�����ݵ�TFT��������
//��ڲ���: DH,DL�ֱ�Ϊ�����ֵĸ�8λ�͵�8λ��ָ��Ҫд������ݡ�
//���ڲ���: ��
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
//д16λ����
//���ܣ� дһ�����ݵ�TFT��������
//��ڲ���: datΪҪд���16λ���ݡ�
//���ڲ���: ��
void write_data_u16(unsigned int dat)
{
	unsigned char m,n;
	m=dat>>8;
	n=dat;
	write_data(m,n);
}


//===============================================================
//д��������
//���ܣ� д�������ݵ�TFT��������
//��ڲ���: cmdΪҪд��������ֽڣ�datΪҪд���16λ���ݡ�
//���ڲ���: ��
void write_cmd_data (unsigned char cmd,unsigned int dat)
{
	unsigned char m,n;
	m=dat>>8;
	n=dat;
	write_cmd(0x00,cmd);
	write_data(m,n);
}


//===============================================================
//���ô���
//��ڲ���: x0 y0,Ϊ��ʾ�������Ͻ����ꣻx1,y1Ϊ��ʾ�������½����ꡣ
//���ڲ���: ��
//˵�����ú�������TFTģ�����ʾ���ڡ�
void LCD_setwindow(unsigned char x0,unsigned int y0,unsigned char x1,unsigned int y1)
{
	write_cmd_data(WINDOW_XADDR_START,x0);//ˮƽ��ʼλ��
	write_cmd_data(WINDOW_XADDR_END,x1);//ˮƽ��ֹλ��
	write_cmd_data(WINDOW_YADDR_START,y0);//��ֱ��ʼλ��
	write_cmd_data(WINDOW_YADDR_END,y1);//��ֱ��ֹλ��
	write_cmd_data(GRAM_XADDR,x0);//����X����λ��
	write_cmd_data(GRAM_YADDR,y0);//����Y����λ��
	write_cmd(0x00,0x22);//LCD_WriteCMD(GRAMWR);
}


//===============================================================
//�趨��ǰ��ʾ����
//��ڲ���: x,yΪ��ǰ��ʾ���ꡣ
//���ڲ���: ��
//˵����������ʵ������LCD_setwindow������һ����������ʾ����Ϊ��С������һ�����ص㡣
void LCD_setxy(unsigned char x,unsigned int y)
{
	LCD_setwindow(x,y,x,y);	
}

//===============================================================
//��������ɫ�Բ����
//��ڲ���: �ޡ�
//���ڲ���: ��
//˵������TFT����������ʾ�����͸�����ɫ�ĵ�ɫ��Ļ��
void LCD_test()
{
	unsigned int temp,num;
	unsigned char n,c;

	//��ʾ����	
	LCD_setwindow(0,0,239,319);
	for(n=0;n<8;n++)
	{
	   temp=color[n];										
		for(num=40*240;num>0;num--)
	   	write_data_u16(temp);
	}
	DelayMs(1);

	//��ʾ��ɫ��ɫ
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



