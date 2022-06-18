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

#pragma comment(lib,"winmm.lib")
#include "logic.h"
#include"Init.h"

void GameOver()
{
	mciSendString("open ./source/boom.wav", NULL, 0, NULL);
	mciSendString("play ./source/boom.wav", NULL, 0, NULL);
	int finalscore;
	finalscore = FinalScore(Gamestate.gametime);
	if (Mypassive.passive == 1)
	{
		finalscore = finalscore * TIMES;
	}
	char scores[50] = { "你输了,本局的得分为：" };
	HWND zzz = GetStdHandle(STD_OUTPUT_HANDLE);
	SetWindowText(zzz, "游戏结束");
	itoa(finalscore, scores + 19, 10);
	UpdateList(finalscore);
	int isok1 = MessageBox(NULL, scores, "游戏结束", 0);
	mciSendString("close ./source/boom.wav", NULL, 0, NULL);
	
};

void Win()
{
	int finalscore;
	finalscore = FinalScore(Gamestate.gametime);
	if (Mypassive.passive == 1)
	{
		finalscore = finalscore * TIMES;
	}
	int Remain = 0;
	for (int i = 0; i < MAXROW; i++)
	{
		for (int j = 0; j < MAXCOL; j++)
		{
			if (Mine[i][j].ifCovered == 0)
			{
				Remain++;
			}
		}
	}
	if (Remain == 40 && Gamestate.mapnum != OVER)
	{
		char scores[50] = { "恭喜你赢了！本局的得分为：" };
		HWND zzz = GetStdHandle(STD_OUTPUT_HANDLE);
		SetWindowText(zzz, "Win!");
		itoa(finalscore, scores + 26, 10);
		UpdateList(finalscore);
		int isok1 = MessageBox(NULL, scores, "Win!", 0);
		cancelTimer(GameTimer);
	}
}

static bool InBox(double x, double y, double x1, double x2, double y1, double y2) 
{
	return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
}

void AddBGM() { 
	PlaySound("./source/bkmusic.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}


void GetMouseButton(int x, int y, int button, int event) {
	double mx = ScaleXInches(x);
	double my = ScaleYInches(y);
	uiGetMouse(x, y, button, event);
	int row = (CHECKERBOARDROW - MOVEROW - my) / (MINESIZE);
	int col = (mx - CHECKERBOARDCOL - MOVECOL) / (MINESIZE);
	Mousestate.mousex = mx;
	Mousestate.mousey = my;
	switch (event)
	{
	case BUTTON_UP:
		if (button == LEFT_BUTTON)
		{
			if (Gamestate.mapnum == GAME)
			{
				if (Mousestate.mousex > CHECKERBOARDCOL + MOVECOL && Mousestate.mousex < CHECKERBOARDCOL + MOVECOL + MAXCOL * MINESIZE)
				{
					if (Mousestate.mousey < CHECKERBOARDROW - MOVEROW && Mousestate.mousey > CHECKERBOARDROW - MOVEROW - MAXCOL * MINESIZE)
					{
						if (Mine[row][col].ifCovered == 0 && Mine[row][col].flag == 0)
						{
							if (Mine[row][col].ifMine == TRUE)
							{
								
								if (Mypassive.passive == 3 && Mypassive.ifUse == 0)
								{
									Mine[row][col].flag = 1;
									Mypassive.ifUse = 1;
									Mypassive.deadcol = col;
									Mypassive.deadrow = row;
								}
								else
								{
									Mine[row][col].ifCovered = 1;
									cancelTimer(GameTimer);
									Gamestate.mapnum = OVER;
									GameOver();
								}
								
							}
							else if (Mine[row][col].ifMine == FALSE)
							{
								Clear(row, col);
								Win();
							}
						}
					}

				}
			}
			if (Mousestate.mousex >= 0.5 && Mousestate.mousex <= 2) {
				Mypassive.ifChoose = TRUE;
				if (Mousestate.mousey >= 5.2 && Mousestate.mousey <= 8)Mypassive.passive = 3;
				if (Mousestate.mousey >= 2.8 && Mousestate.mousey <= 5)Mypassive.passive = 2;
				if (Mousestate.mousey >= 0 && Mousestate.mousey <= 2.1)Mypassive.passive = 1;
			}
		}

		else if (button == RIGHT_BUTTON && Gamestate.mapnum == GAME)
		{
			if (Mousestate.mousex > CHECKERBOARDCOL + MOVECOL && Mousestate.mousex < CHECKERBOARDCOL + MOVECOL + MAXCOL * MINESIZE)
			{
				if (Mousestate.mousey < CHECKERBOARDROW - MOVEROW && Mousestate.mousey > CHECKERBOARDROW - MOVEROW - MAXCOL * MINESIZE)
				{
					if (Mine[row][col].flag == 0 && Mine[row][col].ifCovered == 0 && (MAXMINE - Gamestate.minenum) > 0)
					{
						Mine[row][col].flag = 1;
					}
					else if (Mine[row][col].flag == 1 && Mine[row][col].ifCovered == 0)
					{
						Mine[row][col].flag = 0;
					}
				}
			}
		}
		break;

	default:
		break;

	}
}

void GetCurrentPlace() {
	Mousestate.CurrentX = GetCurrentX();
	Mousestate.CurrentY = GetCurrentY();
}

void DrawMine(double x, double y) {

		SetPenColor("Red");
		SetPenSize(0.005);
		MovePen(x + 0.27 * MINESIZE, y + 0.4 * MINESIZE);
		StartFilledRegion(1);
		DrawLine(-0.0199 * 3, 0.0276 * 3);//1
		DrawLine(0.0283 * 3, -0.0096 * 3);//2
		DrawLine(0.0023 * 3, 0.0265 * 3);//3
		DrawLine(0.0093 * 3, -0.0225 * 3);//4
		DrawLine(0.0224 * 3, 0.0235 * 3);//5
		DrawLine(-0.0052 * 3, -0.0226 * 3);//6
		DrawLine(0.0228 * 3, -0.0009 * 3);//7
		DrawLine(-0.019 * 3, -0.0141 * 3);//8
		DrawLine(0.0189 * 3, -0.0146 * 3);//9
		DrawLine(-0.0246 * 3, 0.0015 * 3);//10
		DrawLine(-0.0006 * 3, -0.0208 * 3);//11
		DrawLine(-0.0135 * 3, 0.0204 * 3);//12
		DrawLine(-0.0171 * 3, -0.0167 * 3);//13
		DrawLine(0.0026 * 3, 0.0191 * 3);//14
		DrawLine(-0.0252 * 3, -0.0105 * 3);//15
		DrawLine(0.0185 * 3, 0.0157 * 3);//16
		EndFilledRegion();
		SetPenColor("Yellow");
		MovePen(x + 0.4 * MINESIZE, y + 0.4 * MINESIZE);
		StartFilledRegion(1);
		DrawLine(-0.0199 * 1.5, 0.0276 * 1.5);//1
		DrawLine(0.0283 * 1.5, -0.0096 * 1.5);//2
		DrawLine(0.0023 * 1.5, 0.0265 * 1.5);//3
		DrawLine(0.0093 * 1.5, -0.0225 * 1.5);//4
		DrawLine(0.0224 * 1.5, 0.0235 * 1.5);//5
		DrawLine(-0.0052 * 1.5, -0.0226 * 1.5);//6
		DrawLine(0.0228 * 1.5, -0.0009 * 1.5);//7
		DrawLine(-0.019 * 1.5, -0.0141 * 1.5);//8
		DrawLine(0.0189 * 1.5, -0.0146 * 1.5);//9
		DrawLine(-0.0246 * 1.5, 0.0015 * 1.5);//10
		DrawLine(-0.0006 * 1.5, -0.0208 * 1.5);//11
		DrawLine(-0.0135 * 1.5, 0.0204 * 1.5);//12
		DrawLine(-0.0171 * 1.5, -0.0167 * 1.5);//13
		DrawLine(0.0026 * 1.5, 0.0191 * 1.5);//14
		DrawLine(-0.0252 * 1.5, -0.0105 * 1.5);//15
		DrawLine(0.0185 * 1.5, 0.0157 * 1.5);//16
		EndFilledRegion();
	
}

void DrawFlag(double x, double y) {
	double FlagHeight = 0.7 * MINESIZE;
	double FlagWidth = 0.5 * MINESIZE;
	SetPenColor("Black");
	MovePen(x + 0.25 * MINESIZE, y + 0.1 * MINESIZE);
	DrawLine(0, FlagHeight);
	DrawLine(FlagWidth, -0.25 * FlagHeight);
	DrawLine(-FlagWidth, -0.25 * FlagHeight);
	SetPenColor("Red");
	StartFilledRegion(1);
	DrawLine(0, 0.5 * FlagHeight);
	DrawLine(FlagWidth, -0.25 * FlagHeight);
	DrawLine(-FlagWidth, -0.25 * FlagHeight);
	EndFilledRegion();
}

void DrawWhiteFlag(double x, double y) {
	double FlagHeight = 0.7 * MINESIZE;
	double FlagWidth = 0.5 * MINESIZE;
	SetPenColor("Black");
	MovePen(x + 0.25 * MINESIZE, y + 0.1 * MINESIZE);
	DrawLine(0, FlagHeight);
	DrawLine(FlagWidth, -0.25 * FlagHeight);
	DrawLine(-FlagWidth, -0.25 * FlagHeight);
	SetPenColor("White");
	StartFilledRegion(1);
	DrawLine(0, 0.5 * FlagHeight);
	DrawLine(FlagWidth, -0.25 * FlagHeight);
	DrawLine(-FlagWidth, -0.25 * FlagHeight);
	EndFilledRegion();
}

void TurnLight(double x, double y) {
	MovePen(x, y);
	SetPenColor("Light Gray");
	StartFilledRegion(1);
	DrawLine(0, -MINESIZE);
	DrawLine(MINESIZE, 0);
	DrawLine(0, MINESIZE);
	DrawLine(-MINESIZE, 0);
	EndFilledRegion();
	SetPenColor("Black");
	DrawLine(0, -MINESIZE);
	DrawLine(MINESIZE, 0);
	DrawLine(0, MINESIZE);
	DrawLine(-MINESIZE, 0);
}

void DrawGrid(void) {
	GetCurrentPlace();
	SetPenColor("Dark Gray");
	StartFilledRegion(1);
	DrawLine(0, -MINESIZE);
	DrawLine(MINESIZE, 0);
	DrawLine(0, MINESIZE);
	DrawLine(-MINESIZE, 0);
	EndFilledRegion();
	SetPenColor("Black");
	DrawLine(0, -MINESIZE);
	DrawLine(MINESIZE, 0);
	DrawLine(0, MINESIZE);
	DrawLine(-MINESIZE, 0);
}

char NumToString[16][16][20];

void DrawChessBoard(void) {
	double cx = GetWindowWidth();
	double cy = GetWindowHeight();
	double x, y;
	extern char NumToString[16][16][20];
	int k, j;
	int nowminenum = 0;
	y = 3 * cy / 4 + MAXROW * MINESIZE / 2 - MOVEROW;
	x = cx / 2 - MAXCOL * MINESIZE / 2 + MOVECOL;
	MovePen(x, y);
	for (k = 0; k < MAXROW; k++) {
		for (j = 0; j < MAXCOL; j++) {

			DrawGrid();
			GetCurrentPlace();
			MovePen(Mousestate.CurrentX + MINESIZE, Mousestate.CurrentY);
		}
		GetCurrentPlace();
		MovePen(Mousestate.CurrentX - (MAXCOL)*MINESIZE, Mousestate.CurrentY - MINESIZE);
	}
	for (k = 0; k < MAXROW; k++) {
		for (j = 0; j < MAXCOL; j++) {

			if (Mine[k][j].ifCovered == 1) {
				TurnLight(x + j * MINESIZE, y - k * MINESIZE);
				if (Mine[k][j].ifMine == 1)
				{
					DrawMine(x + j * MINESIZE, y - k * MINESIZE - MINESIZE);

				}
				else if (Mine[k][j].ifMine == 0)
				{
					if (Mine[k][j].num) {
						drawBox(x + j * MINESIZE, y - k * MINESIZE - MINESIZE, MINESIZE, MINESIZE, 0, NumToString[k][j], '1', "Red");
					}
				}
			}
			if (Mine[k][j].flag == 1 && Mine[k][j].ifCovered == 0)
			{
				nowminenum = nowminenum + 1;
				Gamestate.minenum = nowminenum;
				if (Mypassive.passive == 3 && Mypassive.ifUse == 1 && k == Mypassive.deadrow && j == Mypassive.deadcol)
				{
					DrawWhiteFlag(x + j * MINESIZE, y - k * MINESIZE - MINESIZE);
				}
				else 
				{
					DrawFlag(x + j * MINESIZE, y - k * MINESIZE - MINESIZE);
				}
			}
			else if (Mine[k][j].flag == 0 && Mine[k][j].ifCovered == 0)
			{
				MovePen(x + j * MINESIZE, y - k * MINESIZE);
				DrawGrid();
			}

		}
	}
	for (k = 0; k < MAXCOL; k++) {
		for (j = 0; j < MAXROW; j++) {
			if (InBox(Mousestate.mousex, Mousestate.mousey, x + j * MINESIZE, x + j * MINESIZE + MINESIZE, y - k * MINESIZE - MINESIZE, y - k * MINESIZE) && Mine[k][j].ifCovered == 0 && Gamestate.mapnum == GAME) {
				TurnLight(x + j * MINESIZE, y - k * MINESIZE);
			}
		}
	}

}



void DrawMenu() {
	setMenuColors("BLACK", "WHITE", "Gray", "WHITE", 1);
	setButtonColors("BLACK", "WHITE", "Gray", "WHITE", 1);
	SetFont("微软雅黑");
	SetPointSize(14);
	double cx = GetWindowWidth();
	double cy = GetWindowHeight();

	static char* MENUMORE[] = { "更多",
		"开发者名单",
		"关闭背景音乐",
		"打开背景音乐",
		"排行榜"
	};

	double FH = GetFontHeight();
	double x = 10;
	double y = cy;
	double h = FH * 1.8;
	double w = TextStringWidth(MENUMORE[0]) * 3;
	double wlist = TextStringWidth(MENUMORE[1]) * 1.3;
	int selection;

	selection = button(GenUIID(0), x, y - 5 * h, w, wlist / 3, "打开种子");
	if (selection == 1) {
		Gamestate.ifSeed = 1;
		Gamestate.seednum = 0;
	}
	selection = button(GenUIID(0), x, y - 7.7 * h, w, wlist / 3, "开始游戏");
	if (selection == 1) {
		Renew();
		startTimer(GameTimer, 1000);   
		startTimer(MineTimer, 20);
		cancelTimer(MenuTimer);
		Gamestate.mapnum = GAME;
		
	}
	selection = button(GenUIID(0), x, y - 10.4 * h, w, wlist / 3, "退出游戏");
	if (selection == 1) {
		exit(-1);
	}
	selection = button(GenUIID(0), x, y - 13.1 * h, w, wlist / 3, "帮助");
	if (selection == 1) {
		HWND zzz = GetStdHandle(STD_OUTPUT_HANDLE);
		SetWindowText(zzz, "帮助");
		int isok1 = MessageBox(NULL, "快捷键：	重新开始游戏                          ——回车键\n	更换地图/打开种子/清空种子  ——Ctrl\n	使用技能                                    ——E\n	退出游戏                                ——Esc\n提示：	1.输入种子请使用数字键盘，不同的数字代表不同的种子,种子值的取值范围为		1-99999999；\n	2.鼠标左键点击打开格子，右键点击插旗标雷；\n	3.游戏时间越短，插对的旗子数越多，得分越高；\n	4.点中地雷时游戏失败，除了地雷以外所有格子都被打开时游戏胜利；\n	5.为了得取更高的分数，尽可能多地插上旗子吧！\n	6.在游戏开始前和游玩过程中都能选择游戏角色，但游戏结束时都没选择的		话，就白嫖不到技能辣！", "帮助", 0);
	}
	selection = menuList(GenUIID(0), x, y - 15.8 * h, w, wlist, wlist/3, MENUMORE, sizeof(MENUMORE) / sizeof(MENUMORE[0]));
	if (selection == 1) {
		HWND zzz = GetStdHandle(STD_OUTPUT_HANDLE);
		SetWindowText(zzz, "开发者名单");
		int isok1 = MessageBox(NULL, "本游戏由 aerore2021 && Saul_GM && 好心市民咸鱼叶 合作开发", "开发者名单", 0);
	}
	if (selection == 2) {
		PlaySound( NULL, 0, NULL);
	}
	if (selection == 3) {
		AddBGM();
	}
	if (selection == 4) {
		Rank();
	}
	SetFont("宋体");

	setButtonColors("WHITE", "BLACK", "Gray", "BLACK", 1);

}

void Rank() {
	FILE* fp;
	fp = fopen("list.txt", "r");
	if (fp) {
		char* String = (char*)malloc(sizeof(char) * LINELENGTH);
		int cnt = 1;
		int score;
		char temp_score[7];
		char serial[6];
		fgets(temp_score, 7, fp);
		score = atoi(temp_score);
		sprintf(String, "[1] %d \n", score);
		while (!feof(fp) && cnt < 10) {
			fgets(temp_score, 7, fp);
			String = realloc(String, sizeof(char) * LINELENGTH * (cnt + 1));
			sprintf(serial, "[%d] ", cnt + 1);
			strcat(String, serial);
			strcat(String, temp_score);
			cnt++;
		}
		fclose(fp);
		int isok1 = MessageBox(NULL, String, "排行榜", 0);
	}
	else {
		int isok1 = MessageBox(NULL, "没有成绩，请至少完成一局游戏！", "错误", MB_ICONERROR);
	}
}


void TimerEventProcess(int  timerID)
{
	switch (timerID)
	{
	case GameTimer:
		Gamestate.gametime = Gamestate.gametime + 1;
		Display();
		break;

	case MineTimer:
		Display();
		break;
	case MenuTimer:
		Display();
	}
}

void Renew()
{
	Gamestate.gametime = 0;
	Gamestate.minenum = 0;
	Mypassive.ifChoose = 0;
	Mypassive.ifUse = 0;
	Gamestate.ifSeed = FALSE;
	Gamestate.ifSure = TRUE;
	CreateMine();
	Display();
	cancelTimer(GameTimer);
	startTimer(MenuTimer, 10);
	Gamestate.mapnum = START;
	CreateMap();
	if (Gamestate.seednum == 0 && Gamestate.ifSeed == FALSE)
	{
		FisrtSquare(); 
	}
	else if (Gamestate.seednum != 0 && Gamestate.ifSeed == FALSE)
	{
		SeedFirst(Gamestate.seednum);
	}
}



void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key, event);

	switch (event)
	{
	case KEY_UP:
		if (key == VK_ESCAPE)
			exit(0);

		else if (key == VK_RETURN && (Gamestate.mapnum == GAME) || (Gamestate.mapnum == OVER))
		{
			Renew();
			startTimer(GameTimer, 1000);
			startTimer(MineTimer, 20);
			cancelTimer(MenuTimer);
			Gamestate.mapnum = GAME;
		}
		else if(key == 0x45)
		{
			if (Mypassive.ifUse == 0)
			{
				UseSkill();
			}
		}
		else if (key == VK_CONTROL)
		{
			Gamestate.ifSure = FALSE;
			Gamestate.ifSeed = TRUE;
			Gamestate.seednum = 0;
		}
		else if (key == VK_NUMPAD1 && Gamestate.ifSeed == TRUE && Gamestate.seednum < 10000000)
		{
			Gamestate.seednum = 10 * Gamestate.seednum + 1;
		}
		else if (key == VK_NUMPAD2 && Gamestate.ifSeed == TRUE && Gamestate.seednum < 10000000)
		{
			Gamestate.seednum = 10 * Gamestate.seednum + 2;
		}
		else if (key == VK_NUMPAD3 && Gamestate.ifSeed == TRUE && Gamestate.seednum < 10000000)
		{
			Gamestate.seednum = 10 * Gamestate.seednum + 3;
		}
		else if (key == VK_NUMPAD4 && Gamestate.ifSeed == TRUE && Gamestate.seednum < 10000000)
		{
			Gamestate.seednum = 10 * Gamestate.seednum + 4;
		}
		else if (key == VK_NUMPAD5 && Gamestate.ifSeed == TRUE && Gamestate.seednum < 10000000)
		{
			Gamestate.seednum = 10 * Gamestate.seednum + 5;
		}
		else if (key == VK_NUMPAD6 && Gamestate.ifSeed == TRUE && Gamestate.seednum < 10000000)
		{
			Gamestate.seednum = 10 * Gamestate.seednum + 6;
		}
		else if (key == VK_NUMPAD7 && Gamestate.ifSeed == TRUE && Gamestate.seednum < 10000000)
		{
			Gamestate.seednum = 10 * Gamestate.seednum + 7;
		}
		else if (key == VK_NUMPAD8 && Gamestate.ifSeed == TRUE && Gamestate.seednum < 10000000)
		{
			Gamestate.seednum = 10 * Gamestate.seednum + 8;
		}
		else if (key == VK_NUMPAD9 && Gamestate.ifSeed == TRUE && Gamestate.seednum < 10000000)
		{
			Gamestate.seednum = 10 * Gamestate.seednum + 9;
		}
		else if (key == VK_BACK && Gamestate.ifSeed == TRUE)
		{
			Gamestate.seednum = Gamestate.seednum / 10;
		}
		break;

	default:
		break;
	}
}

void MouseEventProcess(int x, int y, int button, int event) {

	GetMouseButton(x, y, button, event);
}


void CreateString(void) {

	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			itoa(Mine[i][j].num, NumToString[i][j], 10);
		}
	}
}


void Display() {
	DisplayClear();
	DrawBackground();
	CrtItat();
	double cx = GetWindowWidth();
	double cy = GetWindowHeight();
	MovePen(cx / 2, cy / 2);
	DrawChessBoard();
	DrawMenu();

	double label_x;
	double label_y;
	label_x = CHECKERBOARDCOL + MOVECOL;
	label_y = CHECKERBOARDROW - MOVEROW + 0.1;
	double w = 1;
	double h = 0.25;
	double s = MAXCOL * MINESIZE - w;
	char num[600] = { "Time:" };
	itoa(Gamestate.gametime, num + 5, 10);
	char minecurrent[99] = { "Mine:" };
	itoa(MAXMINE - Gamestate.minenum, minecurrent + 5, 10);
	char yourseed[100] = { "Seed:" };
	itoa(Gamestate.seednum, yourseed + 5, 10);
	
	SetPenColor("Black");
	drawBox(label_x, label_y, w, h, 0, num, 'C', "Black");
	drawBox(label_x + s, label_y, w, h, 0, minecurrent, 'C', "Black");
	if (Gamestate.seednum != 0 || Gamestate.ifSeed == TRUE)
	{
		drawBox(label_x + (MINESIZE * MAXROW - 2 * w) / 2, label_y , 2 * w, h, 0, yourseed, 'C', "Black");
	}

}

void CreateMap()
{
	CreateMine();
	if (Gamestate.seednum == 0 && Gamestate.ifSeed == FALSE)
	{
		RandomMine(); 
		Gamestate.seednum = Seed;

	}
	else if (Gamestate.seednum != 0 && Gamestate.ifSeed == FALSE)
	{
		SeedRand(Gamestate.seednum);
	}
	int i, j;
	for (i = 0; i < MAXROW; i++) {
		for (j = 0; j < MAXCOL; j++) {
			Mine[i][j].num = Count(i, j); 
		}
	}
	CreateString();
}

void UseSkill()
{
	if (Mypassive.passive == 2)
	{
		int row = (CHECKERBOARDROW - MOVEROW - Mousestate.mousey) / (MINESIZE);
		int col = (Mousestate.mousex - CHECKERBOARDCOL - MOVECOL) / (MINESIZE);
		Passive_Cui(row,col);
		Mypassive.ifUse = 1;
	}
}

void DrawBackground() {
	extern int pixelWidth, pixelHeight;
	HBITMAP hbg = (HBITMAP)LoadImage(NULL, "./source/bg.bmp", IMAGE_BITMAP, pixelWidth, pixelHeight, LR_LOADFROMFILE);
	HDC mdc;
	extern HDC osdc;
	
	mdc = CreateCompatibleDC(osdc);
	SelectObject(mdc, hbg);
	BitBlt(osdc, 0, 0, pixelWidth, pixelHeight, mdc, 0, 0, SRCCOPY);
	DeleteObject(hbg);
	DeleteDC(mdc);
}

void Draw_ZeroTwo(bool flag) {
	HDC mdc;
	extern HDC osdc;
	extern int pixelHeight;
	mdc = CreateCompatibleDC(osdc);
	if (flag == FALSE) {
		HBITMAP h02 = (HBITMAP)LoadImage(NULL, "./source/02.bmp", IMAGE_BITMAP, 280, 224, LR_LOADFROMFILE);
		SelectObject(mdc, h02);
		BitBlt(osdc, 50, pixelHeight - 220, 140, 200, mdc, 140, 0, SRCAND);
		BitBlt(osdc, 50, pixelHeight - 220, 140, 200, mdc, 0, 0, SRCPAINT);
		DeleteObject(h02);
	}
	else {
		HBITMAP h02 = (HBITMAP)LoadImage(NULL, "./source/02.bmp", IMAGE_BITMAP, 392, 313, LR_LOADFROMFILE); 
		SelectObject(mdc, h02);
		BitBlt(osdc, 22, pixelHeight - 276, 196, 313, mdc, 196, 0, SRCAND);
		BitBlt(osdc, 22, pixelHeight - 276, 196, 313, mdc, 0, 0, SRCPAINT);
		DeleteObject(h02);
	}
	
	DeleteDC(mdc);
}

void Draw_Cui(bool flag) {
	
	HDC mdc;
	extern HDC osdc;
	extern int pixelHeight;
	mdc = CreateCompatibleDC(osdc);
	
	if (flag == FALSE) {
		HBITMAP hCui = (HBITMAP)LoadImage(NULL, "./source/翠星石.bmp", IMAGE_BITMAP, 280, 188.5, LR_LOADFROMFILE);
		SelectObject(mdc, hCui);
		BitBlt(osdc, 44, pixelHeight - 438, 140, 180, mdc, 140, 0, SRCAND);
		BitBlt(osdc, 44, pixelHeight - 438, 140, 180, mdc, 0, 0, SRCPAINT);
		DeleteObject(hCui);
	}
	else {
		HBITMAP hCui = (HBITMAP)LoadImage(NULL, "./source/翠星石.bmp", IMAGE_BITMAP, 392, 264, LR_LOADFROMFILE);
		SelectObject(mdc, hCui);
		BitBlt(osdc, 20, pixelHeight - 460, 196, 252, mdc, 196, 0, SRCAND);
		BitBlt(osdc, 20, pixelHeight - 460, 196, 252, mdc, 0, 0, SRCPAINT);
		DeleteObject(hCui);
	}
	DeleteDC(mdc);
}

void Draw_Albedo(bool flag) { 
	HDC mdc;
	extern HDC osdc;
	extern int pixelHeight;
	mdc = CreateCompatibleDC(osdc);
	
	if (flag == FALSE) {
		HBITMAP hAlbedo = (HBITMAP)LoadImage(NULL, "./source/Albedo.bmp", IMAGE_BITMAP, 280, 188.5, LR_LOADFROMFILE);
		SelectObject(mdc, hAlbedo);
		BitBlt(osdc, 45, pixelHeight - 680, 140, 180, mdc, 140, 0, SRCAND);
		BitBlt(osdc, 45, pixelHeight - 680, 140, 180, mdc, 0, 0, SRCPAINT);
		DeleteObject(hAlbedo);
	}
	else {
		HBITMAP hAlbedo = (HBITMAP)LoadImage(NULL, "./source/Albedo.bmp", IMAGE_BITMAP, 392, 264, LR_LOADFROMFILE);
		SelectObject(mdc, hAlbedo);
		BitBlt(osdc, 17, pixelHeight - 712, 196, 252, mdc, 196, 0, SRCAND);
		BitBlt(osdc, 17, pixelHeight - 712, 196, 252, mdc, 0, 0, SRCPAINT);
		DeleteObject(hAlbedo);
	}
	DeleteDC(mdc);

}

void Dwtxtbg02() {
	HBITMAP htxtBg_02 = (HBITMAP)LoadImage(NULL, "./source/textbg02.bmp", IMAGE_BITMAP, 510, 260, LR_LOADFROMFILE);
	HDC mdc;
	extern HDC osdc;
	extern int pixelHeight;
	mdc = CreateCompatibleDC(osdc);
	SelectObject(mdc, htxtBg_02);
	BitBlt(osdc, 162, pixelHeight - 240, 255, 260, mdc, 255, 0, SRCAND);
	BitBlt(osdc, 162, pixelHeight - 240, 255, 260, mdc, 0, 0, SRCPAINT);
	DeleteObject(htxtBg_02);
	DeleteDC(mdc);
}

void DwtxtbgCui() {
	HBITMAP htxtBg_Cui = (HBITMAP)LoadImage(NULL, "./source/textbgCui.bmp", IMAGE_BITMAP, 510, 260, LR_LOADFROMFILE);
	HDC mdc;
	extern HDC osdc;
	extern int pixelHeight;
	mdc = CreateCompatibleDC(osdc);
	SelectObject(mdc, htxtBg_Cui);
	BitBlt(osdc, 162, pixelHeight - 480, 255, 260, mdc, 255, 0, SRCAND);
	BitBlt(osdc, 162, pixelHeight - 480, 255, 260, mdc, 0, 0, SRCPAINT);
	DeleteObject(htxtBg_Cui);
	DeleteDC(mdc);
}

void DwtxtbgAlbedo() {
	HBITMAP htxtBg_Al = (HBITMAP)LoadImage(NULL, "./source/textbgAl.bmp", IMAGE_BITMAP, 510, 260, LR_LOADFROMFILE);
	HDC mdc;
	extern HDC osdc;
	extern int pixelHeight;
	mdc = CreateCompatibleDC(osdc);
	SelectObject(mdc, htxtBg_Al);
	BitBlt(osdc, 162, pixelHeight - 720, 255, 260, mdc, 255, 0, SRCAND);
	BitBlt(osdc, 162, pixelHeight - 720, 255, 260, mdc, 0, 0, SRCPAINT);
	DeleteObject(htxtBg_Al);
	DeleteDC(mdc);
}

void DrawFrame(int current_character) {
	
	HDC mdc;
	extern HDC osdc;
	extern int pixelHeight;
	mdc = CreateCompatibleDC(osdc);
	
	if (!current_character) {
		HBITMAP hFrame = (HBITMAP)LoadImage(NULL, "./source/边框.bmp", IMAGE_BITMAP, 480, 220, LR_LOADFROMFILE);
		SelectObject(mdc, hFrame);
		BitBlt(osdc, -5, pixelHeight - 225, 240, 220, mdc, 240, 0, SRCAND);
		BitBlt(osdc, -5, pixelHeight - 225, 240, 220, mdc, 0, 0, SRCPAINT);
		BitBlt(osdc, -5, pixelHeight - 465, 240, 220, mdc, 240, 0, SRCAND);
		BitBlt(osdc, -5, pixelHeight - 465, 240, 220, mdc, 0, 0, SRCPAINT);
		BitBlt(osdc, -5, pixelHeight - 705, 240, 220, mdc, 240, 0, SRCAND);
		BitBlt(osdc, -5, pixelHeight - 705, 240, 220, mdc, 0, 0, SRCPAINT);
		DeleteObject(hFrame);
	}
	else if(current_character == 3){
		HBITMAP hFrame = (HBITMAP)LoadImage(NULL, "./source/边框.bmp", IMAGE_BITMAP, 480, 220, LR_LOADFROMFILE);
		SelectObject(mdc, hFrame);
		BitBlt(osdc, -5, pixelHeight - 465, 240, 220, mdc, 240, 0, SRCAND);
		BitBlt(osdc, -5, pixelHeight - 465, 240, 220, mdc, 0, 0, SRCPAINT);
		BitBlt(osdc, -5, pixelHeight - 705, 240, 220, mdc, 240, 0, SRCAND);
		BitBlt(osdc, -5, pixelHeight - 705, 240, 220, mdc, 0, 0, SRCPAINT);
		DeleteObject(hFrame);
		hFrame = (HBITMAP)LoadImage(NULL, "./source/边框.bmp", IMAGE_BITMAP, 672, 330, LR_LOADFROMFILE);
		SelectObject(mdc, hFrame);
		BitBlt(osdc, -53, pixelHeight - 280, 336, 330, mdc, 336, 0, SRCAND);
		BitBlt(osdc, -53, pixelHeight - 280, 336, 330, mdc, 0, 0, SRCPAINT);
		
		DeleteObject(hFrame);
	}
	else if (current_character == 2) {
		HBITMAP hFrame = (HBITMAP)LoadImage(NULL, "./source/边框.bmp", IMAGE_BITMAP, 672, 330, LR_LOADFROMFILE);
		SelectObject(mdc, hFrame);
		BitBlt(osdc, -53, pixelHeight - 520, 336, 330, mdc, 336, 0, SRCAND);
		BitBlt(osdc, -53, pixelHeight - 520, 336, 330, mdc, 0, 0, SRCPAINT);
		DeleteObject(hFrame);
		hFrame = (HBITMAP)LoadImage(NULL, "./source/边框.bmp", IMAGE_BITMAP, 480, 220, LR_LOADFROMFILE);
		SelectObject(mdc, hFrame);
		BitBlt(osdc, -5, pixelHeight - 225, 240, 220, mdc, 240, 0, SRCAND);
		BitBlt(osdc, -5, pixelHeight - 225, 240, 220, mdc, 0, 0, SRCPAINT);
		BitBlt(osdc, -5, pixelHeight - 705, 240, 220, mdc, 240, 0, SRCAND);
		BitBlt(osdc, -5, pixelHeight - 705, 240, 220, mdc, 0, 0, SRCPAINT);
		DeleteObject(hFrame);
	}
	else
	{
		HBITMAP hFrame = (HBITMAP)LoadImage(NULL, "./source/边框.bmp", IMAGE_BITMAP, 672, 330, LR_LOADFROMFILE);
		SelectObject(mdc, hFrame);
		BitBlt(osdc, -53, pixelHeight - 760, 336, 330, mdc, 336, 0, SRCAND);
		BitBlt(osdc, -53, pixelHeight - 760, 336, 330, mdc, 0, 0, SRCPAINT);
		DeleteObject(hFrame);
		hFrame = (HBITMAP)LoadImage(NULL, "./source/边框.bmp", IMAGE_BITMAP, 480, 220, LR_LOADFROMFILE);
		SelectObject(mdc, hFrame);
		BitBlt(osdc, -5, pixelHeight - 225, 240, 220, mdc, 240, 0, SRCAND);
		BitBlt(osdc, -5, pixelHeight - 225, 240, 220, mdc, 0, 0, SRCPAINT);
		BitBlt(osdc, -5, pixelHeight - 465, 240, 220, mdc, 240, 0, SRCAND);
		BitBlt(osdc, -5, pixelHeight - 465, 240, 220, mdc, 0, 0, SRCPAINT);
		DeleteObject(hFrame);
	}

	
	DeleteDC(mdc);
}

void DwPlaying_02() {
	HBITMAP htxtPl_02 = (HBITMAP)LoadImage(NULL, "./source/02_playing.bmp", IMAGE_BITMAP, 960, 580, LR_LOADFROMFILE);
	HDC mdc;
	extern HDC osdc;
	extern int pixelHeight;
	mdc = CreateCompatibleDC(osdc);
	SelectObject(mdc, htxtPl_02);
	BitBlt(osdc, 15, 200, 480, 580, mdc, 480, 0, SRCAND);
	BitBlt(osdc, 15, 200, 480, 580, mdc, 0, 0, SRCPAINT);
	DeleteObject(htxtPl_02);
	DeleteDC(mdc);
}

void DwPlaying_Al() {
	HBITMAP htxtPl_Al = (HBITMAP)LoadImage(NULL, "./source/Albedo_playing.bmp", IMAGE_BITMAP, 1160, 818, LR_LOADFROMFILE);
	HDC mdc;
	extern HDC osdc;
	extern int pixelHeight;
	mdc = CreateCompatibleDC(osdc);
	SelectObject(mdc, htxtPl_Al);
	BitBlt(osdc, 0, 150, 580, 818, mdc, 580, 0, SRCAND);
	BitBlt(osdc, 0, 150, 580, 818, mdc, 0, 0, SRCPAINT);
	DeleteObject(htxtPl_Al);
	DeleteDC(mdc);
}

void DwPlaying_Cui() {
	HBITMAP htxtPl_Cui = (HBITMAP)LoadImage(NULL, "./source/Cui_playing.bmp", IMAGE_BITMAP, 974, 701, LR_LOADFROMFILE);
	HDC mdc;
	extern HDC osdc;
	extern int pixelHeight;
	mdc = CreateCompatibleDC(osdc);
	SelectObject(mdc, htxtPl_Cui);
	BitBlt(osdc, 0, 280, 487, 701, mdc, 487, 0, SRCAND);
	BitBlt(osdc, 0, 280, 487, 701, mdc, 0, 0, SRCPAINT);
	DeleteObject(htxtPl_Cui);
	DeleteDC(mdc);
}

void CrtItat() {
	if (Mypassive.ifChoose == FALSE) {
		
		extern int pixelHeight;
		bool flag = FALSE;
		int current_character = 0;
		if (Mousestate.mousex >= 0.5 && Mousestate.mousex <= 2) {
			if (Mousestate.mousey >= 5.2 && Mousestate.mousey <= 8) current_character = 1;//Al的参数
			if (Mousestate.mousey >= 2.8 && Mousestate.mousey <= 5)current_character = 2;
			if (Mousestate.mousey >= 0 && Mousestate.mousey <= 2.1)current_character = 3; //02的参数
		}
		
		Dwtxtbg02();
		DwtxtbgAlbedo();
		DwtxtbgCui();
		DrawFrame(current_character);
		Draw_ZeroTwo(current_character == 3);
		Draw_Cui(current_character == 2);
		Draw_Albedo(current_character == 1);
		
		
	}
	else {
		switch (Mypassive.passive)
		{
		case 1: DwPlaying_02(); break;
		case 2: DwPlaying_Cui(); break;
		case 3: DwPlaying_Al(); break;
		}
	}
}