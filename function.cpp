#include"startthings.h"
#include<graphics.h>
#include<stdlib.h>
#define SNACK_MAX 1260

enum KeyState
{
    KEY_UP,
    KEY_DOWN,
};

int rec_x;
int rec_y;
int recfood=0;
int speed=200;
bool surefood=false;
bool rec_draw=false;
bool draw_first=false;
bool chuanqiang=false;
bool siwang=true;
bool show_food=false;
int snack_x=580;
int snack_y=435;
int snack_body_lx;
int snack_body_ly;
int dx=0,dy=0;
int snack_size=1;
bool reckbkey=false;
int key;
int key1;
int xNext=0;int yNext=0;
int LOC_x[SNACK_MAX];int LOC_y[SNACK_MAX];



struct returnmove
{
    int dx=0;
    int dy=0;
};


void game::startmenu()
{
    for(int y=0;is_run()&&!(y==255);delay_fps(255))//实现了文字淡化，较为粗糙的实现
    {
        cleardevice();
        color_t color=EGEGRAY(y);
        setcolor(color);
        setbkmode(TRANSPARENT);
        setfont(50,0,"宋体");
        settextjustify(CENTER_TEXT, CENTER_TEXT);
        outtextxy(480,220,"贪吃蛇游戏");
        if(y==0)
        delay_ms(2000);
        y+=1;
    }
    delay_ms(1000); 
    for(int x=255;is_run();delay_fps(255))//实现了文字闪烁，亮。初略的实现较为粗糙
        {
            x-=1;
            cleardevice();
            color_t color=EGEGRAY(x);
            setcolor(color);
            setbkmode(TRANSPARENT);
            setfont(30,0,"宋体");
            settextjustify(CENTER_TEXT, CENTER_TEXT);
            outtextxy(480,220,"正在进入游戏");
            if(x==0)
            break;
        }
    for(int x=0;is_run();delay_fps(255))//实现了文字闪烁，暗。初略的实现较为粗糙
        {
            x+=1;
            cleardevice();
            color_t color=EGEGRAY(x);
            setcolor(color);
            setbkmode(TRANSPARENT);
            setfont(30,0,"宋体");
            settextjustify(CENTER_TEXT, CENTER_TEXT);
            outtextxy(480,220,"正在进入游戏");
            if(x==255)
            break;
        }
    for(int x=255;is_run();delay_fps(255))
        {
            x-=1;
            cleardevice();
            setbkcolor(EGERGB(255,255,255));
            color_t color = EGEGRAY(x);
            setcolor(color);
            setbkmode(TRANSPARENT);
            setfont(20, 0, "宋体");
            settextjustify(CENTER_LINE, CENTER_TEXT);
            outtextxy(480, 135, "模式一：普通模式"); //宽度为160
            outtextxy(480, 270, "模式二：穿墙模式");
            outtextxy(480, 405, "模式三：无敌模式");
            setfont(20,0,"宋体");
            outtextxy(762,60,"退出");
            if(x==0)
            break;
        }
}

void game::gamemodeselect()
{
    MouseState set;
    mouse_msg selection;
    int mousekey;
    for(;is_run();delay_fps(60))
    {
        set.resetState();
        while(mousemsg())
        {
            int x,y;
            mousepos(&x,&y);
            if((x>=405&&x<=565)&&(y>=120&&y<=150))
            {
                selection=getmouse();
                set.handleMouseMsg(selection);
                if(set.hasLeftClick())
                {
                    cleardevice();
                    dhshow();
                    show_map();
                    food();
                    text_show();
                    snack_body(580,435);
                    draw_first=true;
                    showrec();
                    levleshow();
                    goto end;
                }
            }
            else if((x>=405&&x<=565)&&(y>=255&&y<=285))
            {
                selection=getmouse();
                set.handleMouseMsg(selection);
                if(set.hasLeftClick())
                {
                    cleardevice();
                    dhshow();
                    show_map();
                    food();
                    text_show();
                    snack_body(580,435);
                    draw_first=true;
                    chuanqiang=true;
                    showrec();
                    levleshow();
                    goto end;
                }
            }
            else if((x>=405&&x<=565)&&(y>=390&&y<=420))
            {   
                selection=getmouse();
                set.handleMouseMsg(selection);
                if(set.hasLeftClick())
                {
                    cleardevice();
                    dhshow();
                    show_map();
                    food();
                    text_show();
                    snack_body(580,435);
                    draw_first=true;
                    chuanqiang=true;
                    siwang=false;
                    showrec();
                    levleshow();
                    goto end;
                }
            }
            else if(x>=742&&x<=782&&y>=50&&y<=70)
            {
                selection=getmouse();
                set.handleMouseMsg(selection);
                if(set.hasLeftClick()) 
                {
                    goto quit;
                }
            }
        }
    }
    end:
    snack_control();
    flushmouse();
    quit:;
}


void game::show_map()
{
    setcolor(EGEARGB(125,0,0,0));
    setlinewidth(3);
    ege_line(240,0,240,540);
    setcolor(EGEARGB(255,0,0,0));
    setlinewidth(5);
    ege_line(0,0,0,540);
    ege_line(0,540,240,540);
    ege_line(0,0,240,0);
    setlinewidth(3);
    ege_line(240,0,960,0);
    setlinewidth(3);
    ege_line(240,540,960,540);
    setlinewidth(3);
    ege_line(960,540,960,0);
}

void game::map_clean()
{
    setcolor(EGEARGB(125,255,255,255));
    setlinewidth(3);
    ege_line(240,0,240,540);
    setcolor(EGEARGB(255,255,255,255));
    setlinewidth(5);
    ege_line(0,0,0,540);
    ege_line(0,540,240,540);
    ege_line(0,0,240,0);
    setlinewidth(3);
    ege_line(240,0,960,0);
    setlinewidth(3);
    ege_line(240,540,960,540);
    setlinewidth(3);
    ege_line(960,540,960,0);
}

void game::text_show()
{
    setcolor(BLACK);
    setbkmode(TRANSPARENT);
    setfont(30,0,"华文琥珀");
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    outtextxy(120,135,"得分");
    outtextxy(120,375,"速度");
    setfont(20,0,"华文琥珀");
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    outtextxy(120,160,"(一个食物1分)");
    outtextxy(120,400,"(每1分快10ms,最低50)");
}

void game::food()
{
    int loc_x;
    int loc_y;
    srand(GetTickCount());
    loc_x=rand()%(48-12+1)+12;
    loc_y=rand()%(34-0+1)+0;
    if(show_food)
    {
        for(int i=SNACK_MAX-1;i>SNACK_MAX-1-snack_size;i--)
        {
            if(loc_x==LOC_x[i]&&loc_y==LOC_y[i])
            {
                loc_x=rand()%(48-12+1)+12;
                loc_y=rand()%(34-0+1)+0;
            }
            else
            {
                break;
            }
        }
    }
    rec_x=loc_x*20;
    rec_y=loc_y*15;
    setfillcolor(EGEARGB(255,103, 128, 159));
    ege_fillellipse(rec_x,rec_y,20,15);
    show_food=true;
}

void game::snack_body(int loc_x=580,int loc_y=435)
{
    setcolor(EGEARGB(255,0,0,0));
    setlinewidth(2);
    setfillcolor(EGEARGB(255,1, 152, 117));
    ege_fillrect(loc_x,loc_y,20,15);
    ege_rectangle(loc_x,loc_y,20,15);
    if(draw_first)
    {
        if(!rec_draw)
        {
            setcolor(EGEARGB(255,255,255,255));
            setlinewidth(2);
            setfillcolor(EGEARGB(255,255, 255, 255));
            ege_fillrect(loc_x-dx,loc_y-dy,20,15);
            ege_rectangle(loc_x-dx,loc_y-dy,20,15); 
        }
        if(rec_draw)
        {
            setcolor(EGEARGB(255,255,255,255));
            setlinewidth(2);
            setfillcolor(EGEARGB(255,255, 255, 255));
            ege_fillrect(LOC_x[SNACK_MAX-1],LOC_y[SNACK_MAX-1],20,15);
            ege_rectangle(LOC_x[SNACK_MAX-1],LOC_y[SNACK_MAX-1],20,15);
        }
    }
}

void game::snack_control()
{
    LOC_x[SNACK_MAX-1]=snack_x;
    LOC_y[SNACK_MAX-1]=snack_y;
    for(;is_run();delay_fps(60))
    {
        while(kbmsg())
        {
            key_msg kMsg=getkey();
            if(kMsg.msg==key_msg_down)
            {
                reckbkey=true;
                key=kMsg.key;
                flushkey();              
            }
        }
        if(key==key_up&&key1==key_down
            ||key==key_down&&key1==key_up
            ||key==key_right&&key1==key_left
            ||key==key_left&&key1==key_right)
            {
                goto dd; 
            }
        else if(key=='W'&&key1=='S'
        ||key=='S'&&key1=='W'
        ||key=='D'&&key1=='A'
        ||key=='A'&&key1=='D')
        {
            goto dd; 
        }
        key1=key;
        kbcheck(&key,dx,dy);
        if (reckbkey)
        {
            dd:
            LOC_x[SNACK_MAX-1-snack_size]=snack_x;
            LOC_y[SNACK_MAX-1-snack_size]=snack_y;
            for(int i=SNACK_MAX-1;i>SNACK_MAX-1-snack_size;i--)
            {
                LOC_x[i]=LOC_x[i-1];
                LOC_y[i]=LOC_y[i-1];
            }
            xNext=snack_x+dx;yNext=snack_y+dy;
            snack_x=xNext;snack_y=yNext;
            snack_body(xNext,yNext);
            map_clean();
            show_map();
            if((snack_x==rec_x)&&(snack_y==rec_y))
            {
                delay_ms(100);
                recfood+=1;
                speed-=10;
                snack_size+=1;
                rec_draw=true;
                cleanrec();
                showrec();
                if(speed>50)
                {
                    cleanlev();
                    levleshow();
                }
                else if(speed==50)
                {
                    cleanlev();
                    setcolor(BLACK);
                    setbkmode(TRANSPARENT);
                    settextjustify(CENTER_LINE, CENTER_TEXT);
                    setfont(30,0,"华文琥珀");
                    xyprintf(120,435,"%d",speed);
                }
                food();
            }
                if(siwang)
                {
                    for(int i=SNACK_MAX-1;i>SNACK_MAX-1-snack_size;i--)
                    {
                        if(xNext==LOC_x[i]&&yNext==LOC_y[i])
                        {
                            goto end1;
                        }
                    }
                }
                if(!chuanqiang)
                {
                    if(xNext>=240&&xNext<960&&yNext>=0&&yNext<540)
                    {
                        if(speed>50)
                        {
                            delay_ms(speed);//极限数值50
                        }
                        else
                        {
                            delay_ms(50);
                        }
                        continue;
                    }
                    else
                    {
                        snack_x=580;snack_y=435;
                        break;
                    }
                }
                if(chuanqiang)
                {
                    if(snack_x<240)
                    {
                        snack_x=960;
                        setcolor(EGEARGB(255,255,255,255));
                        setlinewidth(2);
                        setfillcolor(EGEARGB(255,255, 255, 255));
                        ege_fillrect(220,snack_y,20,15);
                        ege_rectangle(220,snack_y,20,15); 
                    }
                    if(snack_x>960)
                    {
                        snack_x=220;
                    }
                    if(snack_y<0)
                    {
                        snack_y=540;
                    }
                    if(snack_y>540)
                    {
                        snack_y=-15;
                    }
                    if(speed>50)
                    {
                        delay_ms(speed);//极限数值50
                    }
                        else
                        {
                            delay_ms(50);
                        }
                    continue;
                }
        }
    }
    flushkey();
    end1:
    gameover();
}


void game::kbcheck(int* key,int& dx,int& dy)
{
    switch (*key)
    {
    case 'W':
    case key_up:
        dx=0;dy=-15;
        break;
    case 'A':
    case key_left:
        dx=-20;dy=0;
        break;
    case 'S':
    case key_down:
        dx=0;dy=15;
        break;
    case 'D':
    case key_right:
        dx=20;dy=0;
        break;
    default:
        dx=0;dy=0;
        break;
    };
}

void game::snack_body_lastclean(int x,int y)
{
    setcolor(EGEARGB(255,255,255,255));
    setlinewidth(2);
    setfillcolor(EGEARGB(255,255, 255, 255));
    ege_fillrect(x,y,20,15);
    ege_rectangle(x,y,20,15);
}

void game::gameover()
{
    flushkey();
    recfood=0;
    speed=200;
    snack_size=1;
    rec_draw=false;
    snack_x=580;
    snack_y=435;
    dx=0;dy=0;
    draw_first=false;
    setfillcolor(EGEARGB(255,228, 241, 254));
    ege_fillrect(360,202.5,240,135);
    setlinewidth(2);
    setcolor(EGEARGB(0xFF,0,0,0));
    ege_rectangle(360,202.5,240,135);
    setbkmode(TRANSPARENT);
    setfont(20,0,"宋文");
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    outtextxy(480,270,"WASTED");
    outtextxy(480,240,"按任意键回到选择菜单");
    getch();
    for(int x=255;is_run();delay_fps(255))
    {
        x-=1;
        cleardevice();
        setbkcolor(EGERGB(255,255,255));
        color_t color = EGEGRAY(x);
        setcolor(color);
        setbkmode(TRANSPARENT);
        setfont(20, 0, "宋体");
        settextjustify(CENTER_LINE, CENTER_TEXT);
        outtextxy(480, 135, "模式一：普通模式"); //宽度为160
        outtextxy(480, 270, "模式二：穿墙模式");
        outtextxy(480, 405, "模式三：无敌模式");
        outtextxy(762,60,"退出");
        if(x==0)
        break;
    }
    flushmouse();
    gamemodeselect();
}

void game::showrec()
{
    setcolor(BLACK);
    setbkmode(TRANSPARENT);
    settextjustify(CENTER_LINE, CENTER_TEXT);
    setfont(30,0,"华文琥珀");
    xyprintf(120,195,"%d",recfood);
}

void game::cleanrec()
{
    setcolor(EGEARGB(255,255,255,255));
    ege_fillrect(5,180,232,30);
}

void game::levleshow()
{
    setcolor(BLACK);
    setbkmode(TRANSPARENT);
    settextjustify(CENTER_LINE, CENTER_TEXT);
    setfont(30,0,"华文琥珀");
    xyprintf(120,435,"%d",speed);
}

void game::cleanlev()
{
    setcolor(EGEARGB(255,255,255,255));
    ege_fillrect(5,420,232,30);
}

void game::dhshow()
{
    for(int x=255;is_run();delay_fps(255))//实现了文字闪烁，亮。初略的实现较为粗糙
        {
            x-=1;
            cleardevice();
            color_t color=EGEGRAY(x);
            setcolor(color);
            setbkmode(TRANSPARENT);
            setfont(30,0,"宋体");
            settextjustify(CENTER_TEXT, CENTER_TEXT);
            outtextxy(480,220,"WASD或上下左右移动");
            if(x==0)
            break;
        }
    for(int x=0;is_run();delay_fps(255))//实现了文字闪烁，暗。初略的实现较为粗糙
        {
            x+=1;
            cleardevice();
            color_t color=EGEGRAY(x);
            setcolor(color);
            setbkmode(TRANSPARENT);
            setfont(30,0,"宋体");
            settextjustify(CENTER_TEXT, CENTER_TEXT);
            outtextxy(480,220,"WASD或上下左右移动");
            if(x==255)
            break;
        }
}

//鼠标信息组
//int xMouse, yMouse;
//mousepos(&xMouse, &yMouse);获取鼠标实时位置
// 在帧循环外创建一个 MouseState 类对象， 一个mouse_msg 类对象
// 在鼠标消息处理前，调用 MouseState 对象的 resetState();
// 进行鼠标消息处理循环，对每一条鼠标消息，调用 handleMouseMsg( ) 进行处理
// 如果需要检测每一条鼠标消息类型的，在鼠标消息处理循环中进行。
// 鼠标单击双击事件，在鼠标消息处理循环外判断 hasXXXClick()
// 在用hasXXXClick() 判断由鼠标点击后，可以用 getXXXClickPos() 获取鼠标点击时的位置
//flushmouse();当你觉得缓存区中的鼠标消息已经无用时，可以把缓存区中的鼠标消息清空。

MouseState::MouseState()
{
	interval = 0.4f;
	
	for (int i = 0; i < 3; i++) {
		curMouseState[i] = MOUSE_UP;
		clickEvent[i] = false;
		releaseEvent[i] = false;

		doubleClickEvent[i] = false;
		
		xClick[i] = yClick[i] = 0;

		//初始赋一个较小的负值
		clickTimes[i] = -1000;

		isPressMsg[i] = isReleaseMsg[i] = false;
	}
}

//设置双击触发的两次点击最大时间间隔（单位：秒）
void MouseState::setIntervalTime(double time_seconds)
{
	interval = (time_seconds > 0) ? time_seconds : 0;
}

//重置鼠标按键状态，必须在每一帧中，处理鼠标消息之前调用
void MouseState::resetState()
{
	for (int i = 0; i < 3; i++) {

		clickEvent[i] = false;
		releaseEvent[i] = false;

		doubleClickEvent[i] = false;

		isPressMsg[i] = isReleaseMsg[i] = false;
	}
}


//鼠标消息处理函数
void MouseState::handleMouseMsg(mouse_msg msg)
{
	bool isKey[3] = { msg.is_left(), msg.is_mid(), msg.is_right()};
	
	for (int i = 0; i < 3; i++) {
		isPressMsg[i] = false;
		isReleaseMsg[i] = false;
	}
	//点击事件检查
	for (int i = 0; i < 3; i++) {
		if (isKey[i]) {
			//鼠标点击
			if (msg.is_down()) {
				isPressMsg[i] = true;
				isReleaseMsg[i] = false;
				curMouseState[i] = MOUSE_DOWN;
				clickEvent[i] = true;
				xClick[i] = msg.x;
				yClick[i] = msg.y;
			}
			//鼠标松开
			else if (msg.is_up()) {
				isPressMsg[i] = false;
				isReleaseMsg[i] = true;
				curMouseState[i] = MOUSE_UP;
			}

			checkDoubleClick(i);

			//鼠标消息只能属于一个键,其它键不用再检测
			break;
		}
	}
}

//检测鼠标双击事件
void MouseState::checkDoubleClick(int keyType) {
	double curTime = fclock();
	/*鼠标双击事件检查*/
	if (clickEvent[keyType]) {
		if (curTime - clickTimes[keyType] > interval) {
			clickTimes[keyType] = curTime;
		}
		else {
			doubleClickEvent[keyType] = true;
			clickTimes[keyType] = 0;
		}
	}							
}

//获取鼠标点击位置
void MouseState::getLeftClickPos(int* x, int* y)
{
	*x = xClick[0];
	*y = yClick[0];
}
void MouseState::getMidClickPos(int* x, int* y)
{
	*x = xClick[1];
	*y = yClick[1];
}
void MouseState::getRightClickPos(int* x, int* y)
{
	*x = xClick[2];
	*y = yClick[2];
}