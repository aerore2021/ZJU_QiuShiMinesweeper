/*
 * File: strlib.h
 * Version: 1.0
 * Last modified on Fri Jul 15 14:10:40 1994 by eroberts
 * -----------------------------------------------------
 * The strlib.h file defines the interface for a simple					strlib.h 文件定义了一个简单字符串库的接口。													
 * string library.  In the context of this package, strings				在此包中，字符串被认为是一种抽象数据类型，
 * are considered to be an abstract data type, which means				这意味着客户端仅依赖于为该类型定义的操作，而不依赖于底层表示。
 * that the client relies only on the operations defined for
 * the type and not on the underlying representation.
 */

/*
 * Cautionary note:														注意事项：
 * ----------------														----------------
 * Although this interface provides an extremely convenient				尽管此接口为处理字符串提供了极其方便的抽象，但它并不适用于所有应用程序。
 * abstraction for working with strings, it is not appropriate			在此接口中，返回字符串值的函数（例如 Concat 和 SubString）通过分配新内存来实现。
 * for all applications.  In this interface, the functions that			随着时间的推移，使用此包的程序将消耗越来越多的内存并最终耗尽可用的内存。
 * return string values (such as Concat and SubString) do so			如果您正在编写一个运行时间很短并停止的程序，那么程序包消耗内存的事实不是问题。
 * by allocating new memory.  Over time, a program that uses			但是，如果您正在编写一个必须长时间运行的应用程序，
 * this package will consume increasing amounts of memory				则使用此包需要您为释放任何已分配的存储空间做一些准备。
 * and eventually exhaust the available supply.  If you are
 * writing a program that runs for a short time and stops,
 * the fact that the package consumes memory is not a problem.
 * If, however, you are writing an application that must run
 * for an extended period of time, using this package requires
 * that you make some provision for freeing any allocated
 * storage.
 */

#ifndef _strlib_h
#define _strlib_h

#include "genlib.h"

/* Section 1 -- Basic string operations */								/*第一部分 -- 基础字符串操作*/

/*
 * Function: Concat														函数：Concat
 * Usage: s = Concat(s1, s2);											使用：s = Concat(s1, s2);
 * --------------------------											--------------------------
 * This function concatenates two strings by joining them end			此函数通过将两个字符串首尾相连来连接它们。
 * to end.  For example, Concat("ABC", "DE") returns the string			例如，Concat("ABC", "DE") 返回字符串“ABCDE”。
 * "ABCDE".
 */

string Concat(string s1, string s2);

/*
 * Function: IthChar													函数：IthChar
 * Usage: ch = IthChar(s, i);											使用：ch = IthChar(s, i);
 * --------------------------											--------------------------
 * This function returns the character at position i in the				此函数返回字符串 s 中位置 i 处的字符。
 * string s.  It is included in the library to make the type			它包含在库中以使类型字符串成为真正的抽象类型，因为可以使用函数调用所有必要的操作。
 * string a true abstract type in the sense that all of the				调用 IthChar(s, i) 就像选择 s[i] 一样，
 * necessary operations can be invoked using functions. Calling			只是 IthChar 检查 i 是否在合法索引位置的范围内，从 0 延伸到 StringLength(s)。
 * IthChar(s, i) is like selecting s[i], except that IthChar			IthChar(s, StringLength(s)) 返回字符串末尾的空字符。	
 * checks to see if i is within the range of legal index
 * positions, which extend from 0 to StringLength(s).
 * IthChar(s, StringLength(s)) returns the null character
 * at the end of the string.
 */

char IthChar(string s, int i);

/*
 * Function: SubString													函数：SubString
 * Usage: t = SubString(s, p1, p2);										使用：t = SubString(s, p1, p2);
 * --------------------------------										--------------------------------
 * SubString returns a copy of the substring of s consisting			SubString 返回 s 的子字符串的副本，
 * of the characters between index positions p1 and p2,					该副本由索引位置 p1 和 p2 之间的字符组成，包括索引位置。
 * inclusive.  The following special cases apply:						当遇到特殊情况时：
 *
 * 1. If p1 is less than 0, it is assumed to be 0.						1. 如果p1小于0，则假定为0。
 * 2. If p2 is greater than the index of the last string				2. 如果 p2 大于最后一个字符串位置的索引，即 StringLength(s) - 1，
 *    position, which is StringLength(s) - 1, then p2 is				   则设置 p2 等于 StringLength(s) - 1。
 *    set equal to StringLength(s) - 1.
 * 3. If p2 < p1, SubString returns the empty string.				    3. 如果 p2 < p1，SubString 返回空字符串。
 */

string SubString(string s, int p1, int p2);

/*
 * Function: CharToString												函数：CharToString
 * Usage: s = CharToString(ch);											使用：s = CharToString(ch);
 * ----------------------------											----------------------------
 * This function takes a single character and returns a					此函数接受某个字符并返回由该字符组成的单字符字符串。
 * one-character string consisting of that character.  The				CharToString 函数很有用，例如，如果您需要连接字符串和字符。
 * CharToString function is useful, for example, if you					由于 Concat 需要两个字符串，因此必须先将字符转换为字符串。
 * need to concatenate a string and a character.  Since
 * Concat requires two strings, you must first convert
 * the character into a string.
 */

string CharToString(char ch);

/*
 * Function: StringLength												函数：StringLength
 * Usage: len = StringLength(s);										懂得都懂了吧。
 * -----------------------------
 * This function returns the length of s.
 */

int StringLength(string s);

/*
 * Function: CopyString													函数：CopyString
 * Usage: newstr = CopyString(s);										使用：newstr = CopyString(s);
 * ------------------------------										------------------------------
 * CopyString copies the string s into dynamically allocated			CopyString 将字符串 s 复制到动态分配的存储中并返回新字符串。
 * storage and returns the new string.  This function is not			如果单独使用此包，通常不需要此功能，但在使用多个字符串包时通常需要此功能。
 * ordinarily required if this package is used on its own,
 * but is often necessary when you are working with more than
 * one string package.
 */

string CopyString(string s);

/* Section 2 -- String comparison functions */							/*第二部分 -- 字符串比较函数*/

/*
 * Function: StringEqual												函数：StringEqual
 * Usage: if (StringEqual(s1, s2)) ...									使用：if (StringEqual(s1, s2)) ...
 * -----------------------------------									-----------------------------------
 * This function returns TRUE if the strings s1 and s2 are				如果字符串 s1 和 s2 相等，则此函数返回 TRUE。
 * equal.  For the strings to be considered equal, every				对于被认为相等的字符串，一个字符串中的每个字符必须精确匹配另一个字符串中的相应字符。
 * character in one string must precisely match the						区分大小写。
 * corresponding character in the other.  Uppercase and
 * lowercase characters are considered to be different.
 */

bool StringEqual(string s1, string s2);

/*
 * Function: StringCompare												函数：StringCompare
 * Usage: if (StringCompare(s1, s2) < 0) ...							使用：if (StringCompare(s1, s2) < 0) ...
 * -----------------------------------------							-----------------------------------------
 * This function returns a number less than 0 if string s1				如果字符串 s1 按字母顺序在 s2 之前，则此函数返回小于 0 的数字，
 * comes before s2 in alphabetical order, 0 if they are equal,			如果它们相等则返回 0，如果 s1 在 s2 之后，则返回大于 0 的数字。
 * and a number greater than 0 if s1 comes after s2.  The				排序由用于字符的内部表示确定，通常是 ASCII。
 * ordering is determined by the internal representation used
 * for characters, which is usually ASCII.
 */

int StringCompare(string s1, string s2);

/* Section 3 -- Search functions */										/*第三部分 -- 搜索函数*/

/*
 * Function: FindChar													函数：FindChar	
 * Usage: p	= FindChar(ch, text, start);								使用：p = FindChar(ch, text, start);
 * -------------------------------------								-------------------------------------
 * Beginning at position start in the string text, this					从字符串文本中的 start 位置开始，此函数搜索字符 ch 并返回它出现的第一个索引，
 * function searches for the character ch and returns the				如果没有找到匹配项，则返回 -1。
 * first index at which it appears or -1 if no match is
 * found.
 */

int FindChar(char ch, string text, int start);

/*
 * Function: FindString													函数：FindString
 * Usage: p = FindString(str, text, start);								使用：p = FindString(str, text, start);
 * ----------------------------------------								----------------------------------------
 * Beginning at position start in the string text, this					从字符串文本的 start 位置开始，此函数搜索字符串 str 并返回它出现的第一个索引，	
 * function searches for the string str and returns the					如果没有找到匹配项，则返回 -1。
 * first index at which it appears or -1 if no match is
 * found.
 */

int FindString(string str, string text, int start);

/* Section 4 -- Case-conversion functions */							/*第四部分 -- 大小写转换函数*/

/*
 * Function: ConvertToLowerCase											函数：ConvertToLowerCase
 * Usage: s = ConvertToLowerCase(s);									使用：s = ConvertToLowerCase(s);
 * ---------------------------------									---------------------------------	
 * This function returns a new string with all							返回一个全小写版本的s
 * alphabetic characters converted to lower case.
 */

string ConvertToLowerCase(string s);

/*
 * Function: ConvertToUpperCase											函数：ConvertToUpperCase
 * Usage: s = ConvertToUpperCase(s);									懂得都懂了吧。
 * ---------------------------------
 * This function returns a new string with all
 * alphabetic characters converted to upper case.
 */

string ConvertToUpperCase(string s);

/* Section 5 -- Functions for converting numbers to strings */			/*第五部分 -- 数字、字符串转换的函数*/

/*
 * Function: IntegerToString											函数：IntegerToString
 * Usage: s	= IntegerToString(n);										使用：s = IntegerToString(n);
 * ------------------------------										------------------------------
 * This function converts an integer into the corresponding				此函数将整数转换为相应的数字字符串。
 * string of digits.  For example, IntegerToString(123)					例如，IntegerToString(123) 将“123”作为字符串返回。
 * returns "123" as a string.	
 */

string IntegerToString(int n);

/*
 * Function: StringToInteger											函数：StringToInteger
 * Usage: n = StringToInteger(s);										使用：n = StringToInteger(s);
 * ------------------------------										------------------------------
 * This function converts a string of digits into an integer.			此函数将一串数字转换为整数。
 * If the string is not a legal integer or contains extraneous			如果字符串不是合法整数或包含无关字符，则 StringToInteger 会发出错误信号。
 * characters, StringToInteger signals an error condition.
 */

int StringToInteger(string s);

/*
 * Function: RealToString												函数：RealToString
 * Usage: s = RealToString(d);											使用：s = RealToString(d);
 * ---------------------------											---------------------------		
 * This function converts a floating-point number into the				此函数将浮点数转换为相应的字符串形式。
 * corresponding string form.  For example, calling						例如，调用 RealToString(23.45) 返回“23.45”。
 * RealToString(23.45) returns "23.45".  The conversion is				转换与 printf 中用于“%G”格式的转换相同。
 * the same as that used for "%G" format in printf.
 */

string RealToString(double d);

/*
 * Function: StringToReal												函数：StringToReal
 * Usage: d = StringToReal(s);											使用：d = StringToReal(s);
 * ---------------------------											---------------------------
 * This function converts a string representing a real number			此函数将表示实数的字符串转换为其对应的值。
 * into its corresponding value.  If the string is not a				如果字符串不是合法的浮点数或包含无关字符，则 StringToReal 会发出错误信号。
 * legal floating-point number or if it contains extraneous
 * characters, StringToReal signals an error condition.
 */

double StringToReal(string s);

#endif
