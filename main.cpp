#include "startthings.h"
#include <graphics.h>
#include<stdlib.h>

int main()
{
    game used;
    setinitmode(0,480,270);
    initgraph(960,540,INIT_RENDERMANUAL);
    setcaption("贪吃蛇");
    ege_enable_aa(true);
    setbkcolor(EGERGB(0xFF, 0xFF, 0xFF));//完成窗口配置之一（窗口的打开和设置窗口标题）
    used.startmenu();
    used.gamemodeselect();
    closegraph();
    return 0;
}