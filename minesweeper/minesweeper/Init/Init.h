#ifndef _Init_h

#define _Init_h

#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "imgui.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

#include "logic.h"

#pragma comment(lib,"winmm.lib")


#define MINESIZE 0.3    //定义格子的大小
#define CHECKERBOARDCOL (GetWindowWidth() / 2 -  MINESIZE * MAXCOL / 2)//定义棋盘最左端
#define CHECKERBOARDROW 3 * GetWindowHeight() / 4 + MAXROW * MINESIZE / 2   //定义棋盘最上端
#define MOVEROW 2.4		//下移棋盘
#define MOVECOL 1.3		//右移棋盘
#define REFRESHRATE 20  //刷新率
#define LINELENGTH 13
#define BEISHU1 3
#define BEISHU2 1.5
typedef enum SIGNAL {
	START = 0,    //初始化游戏
	GAME,    //进行游戏
	OVER,    //失败，停止操作
};    //给各种信号赋值

typedef struct
{
	int gametime;    //记录游戏时间
	int minenum;    //记录已被标记的雷数，即已插旗数
	int mapnum;    //记录当前地图所在操作
	int seednum;    //记录地图种子数值
	bool ifSure;    //是否确定该种子
	bool ifSeed;    //是否开始输入种子
}GAMESTATE;
GAMESTATE Gamestate;    //记录游戏信息

typedef enum {
	GameTimer,    //控制计时器计时
	MineTimer,    //控制游戏画面刷新
	MenuTimer,    //控制菜单按钮正常运行
} MYTIMER;

typedef struct {
	double mousex;    //记录鼠标当前所在位置的x坐标
	double mousey;    //记录鼠标当前所在位置的y坐标
	double CurrentX;    
	double CurrentY;
} MOUSESTATE;
static MOUSESTATE Mousestate;    //用于判断鼠标状态

typedef struct 
{
	int passive;
	bool ifUse;
	bool ifChoose;
	int deadrow;
	int deadcol;
}PASSIVE;
PASSIVE Mypassive;
//3:Al, 2:Cui, 1:02
// 
//游戏失败时，弹出失败的弹窗
void GameOver();
//判断是否胜利，并在游戏胜利时，弹出成功的弹窗
void Win();
//判断在内部
static bool InBox(double x, double y, double x1, double x2, double y1, double y2);
//放音乐
void AddBGM();
//得到鼠标信息，并对鼠标按键进行操作
void GetMouseButton(int x, int y, int button, int event);
//得到鼠标当前位置
void GetCurrentPlace();
//画地雷
void DrawMine(double x, double y);
//画小旗子
void DrawFlag(double x, double y);
//画白旗
void DrawWhiteFlag(double x, double y);
//鼠标停留在格子上高亮
void TurnLight(double x, double y);
//画地雷格子
void DrawGrid();
//画棋盘
void DrawChessBoard();
//画操作按键
void DrawMenu();
//排行榜
void Rank();
//控制不同计时器进行响应
void TimerEventProcess(int  timerID);
//刷新地图
void Renew();
// 用户的键盘事件响应函数，对不同的按键进行不同的响应
void KeyboardEventProcess(int key, int event);
// 用户的鼠标事件响应函数
void MouseEventProcess(int x, int y, int button, int event);
//将地图上的数字层从数字转化为字符串
void CreateString(void);
//画出整个画面
void Display(void);
//生成雷层、数字层
void CreateMap();
//使用技能
void UseSkill();
//画游戏背景
void DrawBackground();
//画角色框
void DrawFrame();
//画角色：02、翠星石、雅儿贝德
void Draw_ZeroTwo(bool flag);
void Draw_Cui(bool flag);
void Draw_Albedo(bool flag);
//画角色技能栏
void Dwtxtbg02();
void DwtxtbgCui();
void DwtxtbgAlbedo();
//加游玩时背景
void DwPlaying_02();
void DwPlaying_Al();
void DwPlaying_Cui();
//交互角色
void CrtItat();
#endif