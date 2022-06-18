#pragma once
#ifndef  _logic_h

#define _logic_h

#include "random.h"
#include "boolean.h"
#include "time.h"

#define MAXROW	16
#define MAXCOL	16
#define MAXMINE 40
#define TIMES   2.5
#define STANDARD_SCORE 10000
unsigned int Seed;//这次扫雷的种子值

typedef struct {
	bool ifMine;	//雷层,雷是1，非雷为0
	int  num;		//可以看作数字层
	bool ifCovered;	//判断格子是否被掀开
	bool flag;      //判断是否插旗
} MINE;

MINE Mine[MAXROW][MAXCOL];

/*
	生成一次扫雷地图的函数调用顺序（就连我本人每次用都要回想半天，我觉得你们肯定需要。）
	CreateMine(); //初始化Mine
	RandomMine(); （有种子输入，就SeedRand(seed)）//随机地雷位置
	int i, j;
	for (i = 0; i < MAXROW; i++) {
		for (j = 0; j < MAXCOL; j++) {
			Mine[i][j].num = Count(i, j);  //计算出数字层
		}
	}
	//画图//
	FisrtSquare(); //（伪）随机出初始空白区
*/

void CreateMine();
//初始化雷图，包括1.雷层全FLASE（0）分布；2.数字层计算数字；3.初始化所有格子被盖住（TRUE）。

/*关于雷图的生成，既可以纯随机，也可以用seed生成。*/
void RandomMine();
//	纯随机出雷
//  把这次的种子值赋给全局变量Seed（这个函数使用的种子值是time函数得到的。）

void SeedRand(unsigned int seed);
//  按seed生成雷

void FirstSquare();
//   翻开第一块区域（确保是个区域，而非一个点）

void SeedFirst(unsigned int seed);
//   按seed翻开第一块区域（确保是个区域，而非一个点）

int Count(int row, int col);
//计算并返回周围八个格子的雷数

void Clear(int row, int col);
//进行掀格子递归,递归的条件是数字层为零并且被盖住（后者很重要，否则会无穷递归），递归的出口是数字层非零或者是雷
//注意，当是雷的情况下，不能直接调用gameover()，不然每次clear几乎必gameover，应当在每次点击后先判断这个点是不是雷，再看情况调用clear。
//格子位置的处理我直接枚举了，本来八个方向所以分了很多类，改为四个应该不用那么多类，但我懒得再精简了，确信是能用的。

int FinalScore(gametime);
//计算分数

void Passive_Cui(int row, int col);
//（）翠星石的被动，翻开一个4*4，自动插旗；


void  UpdateList(int score);
//输入分数，结果上形成排完序的排行榜文本

#endif // !_logic_h
