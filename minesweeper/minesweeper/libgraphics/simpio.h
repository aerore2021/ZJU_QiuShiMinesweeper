/*
 * File: simpio.h
 * Version: 1.0
 * Last modified on Wed Apr 27 07:29:13 1994 by eroberts
 * -----------------------------------------------------
 * This interface provides access to a simple package of						该接口提供对简化输入数据读取的简单函数包的访问。
 * functions that simplify the reading of input data.			
 */

#ifndef _simpio_h
#define _simpio_h

#include "genlib.h"

/*
 * Function: GetInteger															函数：GetInteger
 * Usage: i = GetInteger();														使用：i = GetInteger();
 * ------------------------														------------------------
 * GetInteger reads a line of text from standard input and scans				GetInteger 从标准输入中读取一行文本并将其扫描为整数。
 * it as an integer.  The integer value is returned.  If an						返回整数值。
 * integer cannot be scanned or if more characters follow the					如果无法扫描整数 或 数字后面有更多字符，则用户有机会重试。
 * number, the user is given a chance to retry.
 */

int GetInteger(void);

/*
 * Function: GetLong															函数：GetLong
 * Usage: l = GetLong();														懂得都懂。
 * ---------------------
 * GetLong reads a line of text from standard input and scans
 * it as a long integer.  The value is returned as a long.
 * If an integer cannot be scanned or if more characters follow
 * the number, the user is given a chance to retry.
 */

long GetLong(void);

/*
 * Function: GetReal															函数：GetReal
 * Usage: x = GetReal();														使用：x = GetReal();
 * ---------------------														---------------------
 * GetReal reads a line of text from standard input and scans					GetReal 从标准输入读取一行文本并将其扫描为双精度数字。
 * it as a double.  If the number cannot be scanned or if extra
 * characters follow after the number ends, the user is given
 * a chance to reenter the value.
 */

double GetReal(void);

/*
 * Function: GetLine															函数：GetLine
 * Usage: s = GetLine();														使用：s = GetLine();
 * ---------------------														---------------------
 * GetLine reads a line of text from standard input and returns					GetLine 从标准输入中读取一行文本并将该行作为字符串返回。
 * the line as a string.  The newline character that terminates					终止输入的换行符不存储为字符串的一部分。
 * the input is not stored as part of the string.
 */

string GetLine(void);

/*
 * Function: ReadLine															函数：ReadLine
 * Usage: s = ReadLine(infile);													使用：s = ReadLine(infile);
 * ----------------------------													----------------------------
 * ReadLine reads a line of text from the input file and						ReadLine 从输入文件中读取一行文本并将该行作为字符串返回。
 * returns the line as a string.  The newline character							终止输入的换行符不存储为字符串的一部分。
 * that terminates the input is not stored as part of the						如果 infile 位于文件末尾位置，ReadLine 函数将返回 NULL。
 * string.  The ReadLine function returns NULL if infile	
 * is at the end-of-file position.
 */

string ReadLine(FILE *infile);

#endif
