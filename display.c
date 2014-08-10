#include "display.h"
#include "global.h"
#include "gui.h"
#include "ILI9325.h"
#include <msp430x14x.h>


void Display()
{
  //人机界面绘制  
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
    GUI_clearscreen(0);//清屏
    GUI_box(0,0,239,15,0x001f);			 //	左上角顶点坐标，右下角顶点坐标，颜色
    GUI_sprintf_HZ1(56, 0, 0x07ff,0x001f);//显示预定义汉字字符串	显示内容左上角坐标，颜色，背景颜色

    /*用比较暗的颜色画出所有非整十横刻度线*/
    for(y=25;y<=275;y=y+10)
    {
            if ((y-25)%50!=0)/*判断是否整十刻度线位置*/
                    GUI_HLine(28, y, 201,0x000f); /*否，画比较暗的横刻度线 ，横线起点坐标，横线长度，颜色*/
    }
    
    /*用比较暗的颜色画出所有非整十纵刻度线*/
    for(x=28;x<=228;x=x+10)
    {
            if ((x-28)%50!=0)/*判断是否整十刻度线位置*/
                    GUI_RLine(x, 25, 251,0x000f); /*否，画比较暗的纵刻度线*/
    }

    /*用比较亮的颜色画出所有整十横刻度线*/
    for(y=25;y<=275;y=y+50)
    {
            GUI_HLine(28, y, 201,0x001f); /*画比较亮的横刻度线*/
    }

    /*用比较亮的颜色画出所有整十纵刻度线*/
    for(x=28;x<=228;x=x+50)
    {
            GUI_RLine(x, 25, 251,0x001f); /*画比较亮的纵刻度线*/
    }

    /*画出纵坐标刻度值*/
    GUI_sprintf_string(0, 17,"40C", 0xf81f,0);		  //内容左上角坐标，字符串，颜色，背景颜色
    GUI_sprintf_string(0, 67,"30C", 0xf81f,0);
    GUI_sprintf_string(0, 117,"20C", 0xf81f,0);
    GUI_sprintf_string(0, 167,"10C", 0xf81f,0);
    GUI_sprintf_string(0, 217," 0C", 0xf81f,0);
    GUI_sprintf_string(0, 267,"10C", 0xf81f,0);

    GUI_Point(16, 19, 0xf81f);		   //点坐标，颜色
    GUI_Point(16, 69, 0xf81f);
    GUI_Point(16, 119, 0xf81f);
    GUI_Point(16, 169, 0xf81f);
    GUI_Point(16, 219, 0xf81f);
    GUI_Point(16, 269, 0xf81f);

    
    /*画出横坐标刻度值*/
    GUI_sprintf_string(24, 279,"0S", 0x07e0,0);			//内容左上角坐标，字符串，颜色，背景颜色
    GUI_sprintf_string(66, 279,"50S", 0x07e0,0);
    GUI_sprintf_string(112, 279,"100S", 0x07e0,0);
    GUI_sprintf_string(162, 279,"150S", 0x07e0,0);
    GUI_sprintf_string(208, 279,"200S", 0x07e0,0);

    GUI_box(0,300,239,319,0x7bef);					   //	左上角顶点坐标，右下角顶点坐标，颜色

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
      /*用比较暗的颜色画出所有非整十横刻度线*/
    for(y=25;y<=275;y=y+10)
    {
            if ((y-25)%50!=0)/*判断是否整十刻度线位置*/
                    GUI_HLine(28, y, 201,0x000f); /*否，画比较暗的横刻度线 ，横线起点坐标，横线长度，颜色*/
    }
    
    /*用比较暗的颜色画出所有非整十纵刻度线*/
    for(x=28;x<=228;x=x+10)
    {
            if ((x-28)%50!=0)/*判断是否整十刻度线位置*/
                    GUI_RLine(x, 25, 251,0x000f); /*否，画比较暗的纵刻度线*/
    }

    /*用比较亮的颜色画出所有整十横刻度线*/
    for(y=25;y<=275;y=y+50)
    {
            GUI_HLine(28, y, 201,0x001f); /*画比较亮的横刻度线*/
    }

    /*用比较亮的颜色画出所有整十纵刻度线*/
    for(x=28;x<=228;x=x+50)
    {
            GUI_RLine(x, 25, 251,0x001f); /*画比较亮的纵刻度线*/
    }

    /*画出纵坐标刻度值*/
    GUI_sprintf_string(0, 17,"40C", 0xf81f,0);		  //内容左上角坐标，字符串，颜色，背景颜色
    GUI_sprintf_string(0, 67,"30C", 0xf81f,0);
    GUI_sprintf_string(0, 117,"20C", 0xf81f,0);
    GUI_sprintf_string(0, 167,"10C", 0xf81f,0);
    GUI_sprintf_string(0, 217," 0C", 0xf81f,0);
    GUI_sprintf_string(0, 267,"10C", 0xf81f,0);

    GUI_Point(16, 19, 0xf81f);		   //点坐标，颜色
    GUI_Point(16, 69, 0xf81f);
    GUI_Point(16, 119, 0xf81f);
    GUI_Point(16, 169, 0xf81f);
    GUI_Point(16, 219, 0xf81f);
    GUI_Point(16, 269, 0xf81f);

    
    /*画出横坐标刻度值*/
    GUI_sprintf_string(24, 279,"0S", 0x07e0,0);			//内容左上角坐标，字符串，颜色，背景颜色
    GUI_sprintf_string(66, 279,"50S", 0x07e0,0);
    GUI_sprintf_string(112, 279,"100S", 0x07e0,0);
    GUI_sprintf_string(162, 279,"150S", 0x07e0,0);
    GUI_sprintf_string(208, 279,"200S", 0x07e0,0);
}
