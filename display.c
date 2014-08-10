#include "display.h"
#include "global.h"
#include "gui.h"
#include "ILI9325.h"
#include <msp430x14x.h>


void Display()
{
  //�˻��������  
  GUI_clearscreen(WHITE);
  GUI_DisPicture(0,30,66,261);
  GUI_box(0,0,239,30,BLUE);
  GUI_box(0,0,7,319,GREEN);
  GUI_box(0,310,239,319,YELLOW);
  //GUI_sprintf_HZ2(0,0,RED,BLACK);
  //GUI_sprintf_HZ3(0,60,RED,BLACK);
  
}
void TempInterFace()
{
    uint x,y ;  
    GUI_clearscreen(0);//����
    GUI_box(0,0,239,15,0x001f);			 //	���ϽǶ������꣬���½Ƕ������꣬��ɫ
    GUI_sprintf_HZ1(56, 0, 0x07ff,0x001f);//��ʾԤ���庺���ַ���	��ʾ�������Ͻ����꣬��ɫ��������ɫ

    /*�ñȽϰ�����ɫ�������з���ʮ��̶���*/
    for(y=25;y<=275;y=y+10)
    {
            if ((y-25)%50!=0)/*�ж��Ƿ���ʮ�̶���λ��*/
                    GUI_HLine(28, y, 201,0x000f); /*�񣬻��Ƚϰ��ĺ�̶��� ������������꣬���߳��ȣ���ɫ*/
    }
    
    /*�ñȽϰ�����ɫ�������з���ʮ�ݿ̶���*/
    for(x=28;x<=228;x=x+10)
    {
            if ((x-28)%50!=0)/*�ж��Ƿ���ʮ�̶���λ��*/
                    GUI_RLine(x, 25, 251,0x000f); /*�񣬻��Ƚϰ����ݿ̶���*/
    }

    /*�ñȽ�������ɫ����������ʮ��̶���*/
    for(y=25;y<=275;y=y+50)
    {
            GUI_HLine(28, y, 201,0x001f); /*���Ƚ����ĺ�̶���*/
    }

    /*�ñȽ�������ɫ����������ʮ�ݿ̶���*/
    for(x=28;x<=228;x=x+50)
    {
            GUI_RLine(x, 25, 251,0x001f); /*���Ƚ������ݿ̶���*/
    }

    /*����������̶�ֵ*/
    GUI_sprintf_string(0, 17,"40C", 0xf81f,0);		  //�������Ͻ����꣬�ַ�������ɫ��������ɫ
    GUI_sprintf_string(0, 67,"30C", 0xf81f,0);
    GUI_sprintf_string(0, 117,"20C", 0xf81f,0);
    GUI_sprintf_string(0, 167,"10C", 0xf81f,0);
    GUI_sprintf_string(0, 217," 0C", 0xf81f,0);
    GUI_sprintf_string(0, 267,"10C", 0xf81f,0);

    GUI_Point(16, 19, 0xf81f);		   //�����꣬��ɫ
    GUI_Point(16, 69, 0xf81f);
    GUI_Point(16, 119, 0xf81f);
    GUI_Point(16, 169, 0xf81f);
    GUI_Point(16, 219, 0xf81f);
    GUI_Point(16, 269, 0xf81f);

    
    /*����������̶�ֵ*/
    GUI_sprintf_string(24, 279,"0S", 0x07e0,0);			//�������Ͻ����꣬�ַ�������ɫ��������ɫ
    GUI_sprintf_string(66, 279,"50S", 0x07e0,0);
    GUI_sprintf_string(112, 279,"100S", 0x07e0,0);
    GUI_sprintf_string(162, 279,"150S", 0x07e0,0);
    GUI_sprintf_string(208, 279,"200S", 0x07e0,0);

    GUI_box(0,300,239,319,0x7bef);					   //	���ϽǶ������꣬���½Ƕ������꣬��ɫ

    GUI_sprintf_string(20, 302,"TEMP:", 0xffe0,0x7bef);	
    GUI_sprintf_string(110, 302,"C", 0xffe0,0x7bef);
    GUI_Point(110, 304, 0xffe0);

    GUI_sprintf_string(150, 302,"TIME:", 0xffe0,0x7bef);	
    GUI_sprintf_string(216, 302,"S", 0xffe0,0x7bef);
}
void TempReflash()
{
    uint x,y;
    GUI_box(0,16,239,299,BLACK);
      /*�ñȽϰ�����ɫ�������з���ʮ��̶���*/
    for(y=25;y<=275;y=y+10)
    {
            if ((y-25)%50!=0)/*�ж��Ƿ���ʮ�̶���λ��*/
                    GUI_HLine(28, y, 201,0x000f); /*�񣬻��Ƚϰ��ĺ�̶��� ������������꣬���߳��ȣ���ɫ*/
    }
    
    /*�ñȽϰ�����ɫ�������з���ʮ�ݿ̶���*/
    for(x=28;x<=228;x=x+10)
    {
            if ((x-28)%50!=0)/*�ж��Ƿ���ʮ�̶���λ��*/
                    GUI_RLine(x, 25, 251,0x000f); /*�񣬻��Ƚϰ����ݿ̶���*/
    }

    /*�ñȽ�������ɫ����������ʮ��̶���*/
    for(y=25;y<=275;y=y+50)
    {
            GUI_HLine(28, y, 201,0x001f); /*���Ƚ����ĺ�̶���*/
    }

    /*�ñȽ�������ɫ����������ʮ�ݿ̶���*/
    for(x=28;x<=228;x=x+50)
    {
            GUI_RLine(x, 25, 251,0x001f); /*���Ƚ������ݿ̶���*/
    }

    /*����������̶�ֵ*/
    GUI_sprintf_string(0, 17,"40C", 0xf81f,0);		  //�������Ͻ����꣬�ַ�������ɫ��������ɫ
    GUI_sprintf_string(0, 67,"30C", 0xf81f,0);
    GUI_sprintf_string(0, 117,"20C", 0xf81f,0);
    GUI_sprintf_string(0, 167,"10C", 0xf81f,0);
    GUI_sprintf_string(0, 217," 0C", 0xf81f,0);
    GUI_sprintf_string(0, 267,"10C", 0xf81f,0);

    GUI_Point(16, 19, 0xf81f);		   //�����꣬��ɫ
    GUI_Point(16, 69, 0xf81f);
    GUI_Point(16, 119, 0xf81f);
    GUI_Point(16, 169, 0xf81f);
    GUI_Point(16, 219, 0xf81f);
    GUI_Point(16, 269, 0xf81f);

    
    /*����������̶�ֵ*/
    GUI_sprintf_string(24, 279,"0S", 0x07e0,0);			//�������Ͻ����꣬�ַ�������ɫ��������ɫ
    GUI_sprintf_string(66, 279,"50S", 0x07e0,0);
    GUI_sprintf_string(112, 279,"100S", 0x07e0,0);
    GUI_sprintf_string(162, 279,"150S", 0x07e0,0);
    GUI_sprintf_string(208, 279,"200S", 0x07e0,0);
}
