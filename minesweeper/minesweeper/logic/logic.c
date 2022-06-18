#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "logic.h"
#include "random.h"
#include "boolean.h"
#include "linkedlist.h"
#include "time.h"

void CreateMine() {
	int i = 0;
	for (; i < MAXROW; i++) {
		for (int j = 0; j < MAXCOL; j++) {
			Mine[i][j].ifMine = FALSE;
			Mine[i][j].ifCovered = FALSE;
			Mine[i][j].num = 0;
			Mine[i][j].flag = 0;
		}
	}
}

void RandomMine() {
	Seed = time(NULL);
	srand(Seed);
	int cnt = 1;
	int index;
	int col, row;
	while (cnt <= MAXMINE) {
		index = (int)(MAXCOL * MAXROW * rand() / (RAND_MAX + 1.0));
		col = index % MAXCOL;
		row = (index - 1) / MAXROW;
		if (Mine[row][col].ifMine) continue;
		else Mine[row][col].ifMine = TRUE;
		cnt++;
	}

}

void FisrtSquare() {
	int index;
	int col, row;
	srand(Seed);
	while (1) {
		index = (int)(MAXCOL * MAXROW * rand() / (RAND_MAX + 1.0));
		col = index % MAXCOL;
		row = (index - 1) / MAXROW;
		if (Mine[row][col].ifMine || Mine[row][col].num) continue;
		else {
			Clear(row, col);
			break;
		}
	}

}

void SeedFirst(unsigned int seed) {
	int index;
	int col, row;
	srand(seed);
	while (1) {
		index = (int)(MAXCOL * MAXROW * rand() / (RAND_MAX + 1.0));
		col = index % MAXCOL;
		row = (index - 1) / MAXROW;
		if (Mine[row][col].ifMine || Mine[row][col].num) continue;
		else {
			Clear(row, col);
			break;
		}
	}
}

void SeedRand(unsigned int seed) {
	srand(seed);
	int index;
	int col, row;
	int i = 1;
	while (i <= MAXMINE) {
		seed += seed % i;
		index = (int)(MAXCOL * MAXROW * rand() / (RAND_MAX + 1.0));
		col = index % MAXCOL;
		row = (index - 1) / MAXROW;
		if (Mine[row][col].ifMine) {
			continue;
		}
		else Mine[row][col].ifMine = TRUE;
		i++;
	}
}

int Count(int i, int j) {
	int num;
	if (i == 0) {
		if (j == 0)	num = Mine[i + 1][j].ifMine + Mine[i + 1][j + 1].ifMine + Mine[i][j + 1].ifMine;
		else if (j == MAXCOL - 1)
			num = Mine[i + 1][j].ifMine + Mine[i + 1][j - 1].ifMine + Mine[i][j - 1].ifMine;
		else		num = Mine[i + 1][j].ifMine + Mine[i + 1][j - 1].ifMine + Mine[i][j - 1].ifMine + Mine[i][j + 1].ifMine + Mine[i + 1][j + 1].ifMine;
	}
	else if (i == MAXROW - 1) {
		if (j == 0) num = Mine[i - 1][j].ifMine + Mine[i - 1][j + 1].ifMine + Mine[i][j + 1].ifMine;
		else if (j == MAXCOL - 1)
			num = Mine[i - 1][j].ifMine + Mine[i - 1][j - 1].ifMine + Mine[i][j - 1].ifMine;
		else		num = Mine[i - 1][j].ifMine + Mine[i - 1][j - 1].ifMine + Mine[i][j - 1].ifMine + Mine[i][j + 1].ifMine + Mine[i - 1][j + 1].ifMine;
	}
	else if (j == 0) {
		num = Mine[i - 1][j].ifMine + Mine[i - 1][j + 1].ifMine + Mine[i][j + 1].ifMine + Mine[i + 1][j].ifMine + Mine[i + 1][j + 1].ifMine;
	}
	else if (j == MAXCOL - 1) {
		num = Mine[i - 1][j].ifMine + Mine[i - 1][j - 1].ifMine + Mine[i][j - 1].ifMine + Mine[i + 1][j].ifMine + Mine[i + 1][j - 1].ifMine;
	}
	else {
		num = Mine[i - 1][j].ifMine + Mine[i - 1][j - 1].ifMine + Mine[i][j - 1].ifMine + Mine[i + 1][j].ifMine + Mine[i + 1][j - 1].ifMine + Mine[i - 1][j + 1].ifMine + Mine[i][j + 1].ifMine + Mine[i + 1][j + 1].ifMine;
	}
	return num;
}

void Clear(int row, int col) {
	if (Mine[row][col].ifMine == TRUE);
	else if (Mine[row][col].num == 0 && Mine[row][col].ifCovered == FALSE && Mine[row][col].flag == 0) {
		Mine[row][col].ifCovered = TRUE;
		if (row == 0) {
			if (col == 0) {
				Clear(row + 1, col);
				Clear(row, col + 1);
			}
			else if (col == MAXCOL - 1) {
				Clear(row + 1, col);
				Clear(row, col - 1);
			}
			else {
				Clear(row + 1, col);
				Clear(row, col - 1);
				Clear(row, col + 1);
			}
		}
		else if (row == MAXROW - 1) {
			if (col == 0) {
				Clear(row - 1, col);
				Clear(row, col + 1);
			}
			else if (col == MAXCOL - 1) {
				Clear(row - 1, col);
				Clear(row, col - 1);
			}
			else {
				Clear(row - 1, col);
				Clear(row, col - 1);
				Clear(row, col + 1);
			}
		}
		else if (col == 0) {
			Clear(row - 1, col);
			Clear(row, col + 1);
			Clear(row + 1, col);
		}
		else if (col == MAXCOL - 1) {
			Clear(row - 1, col);
			Clear(row, col - 1);
			Clear(row + 1, col);
		}
		else {
			Clear(row - 1, col);
			Clear(row, col - 1);
			Clear(row + 1, col);
			Clear(row, col + 1);
		}
	}
	else if (Mine[row][col].flag == 0)
	{
		Mine[row][col].ifCovered = TRUE;
	}
}

int FinalScore(int gametime) {
	int RightFlag = 0;
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			if (Mine[i][j].flag == 1 && Mine[i][j].ifMine == 1)
			{
				RightFlag++;
			}
		}
	}
	double timetimes;
	if (gametime <= 100)
	{
		timetimes = 10 - 0.02 * gametime;
	}
	else if (gametime > 100 && gametime <= 300)
	{
		timetimes = 9.5 - 0.015 * gametime;
	}
	else if (gametime > 300 && gametime < 600)
	{
		timetimes = 9 - 4 * gametime / 300;
	}
	else if (gametime >= 600)
	{
		timetimes = 1;
	}
	double flagtimes;
	if (RightFlag <= 10)
	{
		flagtimes = 0.4 * RightFlag + 1;
	}
	else if (RightFlag > 10)
	{
		flagtimes = 23 * RightFlag * RightFlag / 900 - RightFlag / 9 + 32 / 9;
	}
	double score = 100 * timetimes * flagtimes;
	return score;
}

void  UpdateList(int score) {
	FILE* fp;
	FILE* fpnew;
	char putin_score[7];
	linkedlistADT head, p, q, t;
	head = NewLinkedList();
	q = head;
	char temp_score[7];
	itoa(score, putin_score, 10);

	fp = fopen("list.txt", "r");
	if (fp) {
		p = (linkedlistADT)malloc(sizeof(*(linkedlistADT)NULL));
		fgets(temp_score, 7, fp);
		p->dataptr = atoi(temp_score);
		q->next = p;
		q = p;
		//形成关于fp的链表
		while (!feof(fp)) {
			p = (linkedlistADT)malloc(sizeof(*(linkedlistADT)NULL)); fgets(temp_score, 7, fp);
			printf("%d ", atoi(temp_score));
			p->dataptr = atoi(temp_score);
			q->next = p;
			q = p;
		}
		printf("\n");
		fclose(fp);
		q->next = NULL;
		t = (linkedlistADT)malloc(sizeof(*(linkedlistADT)NULL));
		p = (linkedlistADT)malloc(sizeof(*(linkedlistADT)NULL));
		t->dataptr = score;
		//插入score节点
		for (p = head->next; p; p = p->next) {
			if (p == head->next) {
				if (t->dataptr >= p->dataptr) {
					InsertNode(head, head, t->dataptr);
					break;
				}

			}
			if (p->next == NULL) {
				if (t->dataptr < p->dataptr) {
					InsertNode(head, p, t->dataptr);
					break;
				}
			}
			if (t->dataptr <= p->dataptr && t->dataptr >= p->next->dataptr) {
				InsertNode(head, p, t->dataptr);
				break;
			}
		}
		fpnew = fopen("roam.txt", "w");
		p = (linkedlistADT)malloc(sizeof(*(linkedlistADT)NULL));
		p = head->next;
		while (p) {
			itoa(p->dataptr, temp_score, 10);
			if (p == head->next) fputs(temp_score, fpnew);
			else {
				fputs("\n", fpnew);
				fputs(temp_score, fpnew);
			}
			p = p->next;
		}

		fclose(fpnew);
		remove("list.txt");
		rename("roam.txt", "list.txt");
	}
	else {
		fpnew = fopen("list.txt", "w");
		fputs(putin_score, fpnew);
		fclose(fpnew);
	}
}

void Passive_Cui(int row, int col) {
	int i = -2, j;
	for (i; i <= 2; i++) {
		if (row + i > MAXROW) break;
		for (j = -2; j <= 2; j++) {
			if (col + j > MAXCOL) break;
			if (row + i < 0 || col + j < 0)continue;
			else if (Mine[row + i][col + j].ifMine == TRUE) Mine[row + i][col + j].flag = TRUE;
			else Mine[row + i][col + j].ifCovered = TRUE;//反正就是翻格子，忘了你是哪个了
		}
	}
}