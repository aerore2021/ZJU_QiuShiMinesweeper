#include<stdio.h>
#include "logic.h"
#include"Init.h"

void Main()
{
	SetWindowSize(12, 7.5);
	InitGraphics();

	AddBGM();
	CreateMap();
	DrawBackground();
	setButtonColors("Dark Gray", "Black", "Gray", "Black", 1);
	SetWindowTitle("求是扫雷 Hot hot hot!!!");
	startTimer(MenuTimer, 10);
	Display();
	registerKeyboardEvent(KeyboardEventProcess);// 键盘
	registerMouseEvent(MouseEventProcess);      // 鼠标
	registerTimerEvent(TimerEventProcess);      // 定时器
}