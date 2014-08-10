#include "gui.h"
#include "interface.h"

void MAIN_WINDOW()
{
    // GUI_sprintf_string(0, 50, "xiao mi mi !", RED, WHITE);
    int i;
    for (i = 0; i < 64; i++) {
        GUI_box(0, i * 5, 3 * i + 4, i * 5 + 3, 0x001f);//»­ÊµÐÄ¾ØÐÎ
    }
}