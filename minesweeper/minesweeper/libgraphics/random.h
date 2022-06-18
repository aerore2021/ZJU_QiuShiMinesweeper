/*
 * File: random.h
 * Version: 1.0
 * Last modified on Fri Jul 22 16:44:36 1994 by eroberts
 * -----------------------------------------------------
 * This interface provides several functions for generating					该接口提供了几个用于生成伪随机数的函数。
 * pseudo-random numbers.
 */

#ifndef _random_h
#define _random_h

#include "genlib.h"
#include <stdlib.h>

/*
 * Constant: RAND_MAX														常量：RAND_MAX
 * ------------------														------------------
 * Unfortunately, several libraries that supposedly conform to				不幸的是，一些据称符合 ANSI 标准的库没有在 <stdlib.h> 中定义 RAND_MAX。
 * the ANSI standard do not define RAND_MAX in <stdlib.h>.  To				为了减少可移植性问题，此接口将 RAND_MAX 定义为未定义的最大正整数。
 * reduce portability problems, this interface defines RAND_MAX
 * to be the largest positive integer if it is undefined.
 */

#ifndef RAND_MAX
#  define RAND_MAX ((int) ((unsigned) ~0 >> 1))
#endif

/*
 * Function: Randomize														函数：Randomize
 * Usage: Randomize();														使用：Randomize();
 * -------------------														-------------------
 * This function sets the random seed so that the random sequence			该函数设置随机种子，使随机序列不可预测。
 * is unpredictable.  During the debugging phase, it is best not			在调试阶段，最好不要调用这个函数，这样程序的行为才是可重复的。
 * to call this function, so that program behavior is repeatable.
 */

void Randomize(void);

/*
 * Function: RandomInteger													函数：RandomInteger
 * Usage: n = RandomInteger(low, high);										使用：n = RandomInteger(low, high);
 * ------------------------------------										------------------------------------
 * This function returns a random integer in the range low to high,			此函数返回从低到高（含）范围内的随机整数。
 * inclusive.
 */

int RandomInteger(int low, int high);

/*
 * Function: RandomReal														函数：RandomReal
 * Usage: d = RandomReal(low, high);										使用：d = RandomReal(low, high);
 * ---------------------------------										---------------------------------
 * This function returns a random real number in the half-open				该函数在半开区间 [low , high) 中返回一个随机实数，
 * interval [low .. high), meaning that the result is always				这意味着结果始终大于或等于 low 但严格小于 high。
 * greater than or equal to low but strictly less than high.
 */

double RandomReal(double low, double high);

/*
 * Function: RandomChance													函数：RandomChance
 * Usage: if (RandomChance(p)) . . .										使用：if (RandomChance(p)) . . .
 * ---------------------------------										---------------------------------
 * The RandomChance function returns TRUE with the probability				RandomChance 函数以 p 表示的概率返回 TRUE，
 * indicated by p, which should be a floating-point number between			p 应该是介于 0（表示从不）和 1（表示始终）之间的浮点数。
 * 0 (meaning never) and 1 (meaning always).  For example, calling			例如，调用 RandomChance(.30) 有 30% 的时间返回 TRUE。
 * RandomChance(.30) returns TRUE 30 percent of the time.
 */

bool RandomChance(double p);

#endif
