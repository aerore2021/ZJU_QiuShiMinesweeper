/*
 * File: genlib.h
 * Version: 1.0
 * Last modified on Sun Jul 24 10:32:49 1994 by eroberts
 * -----------------------------------------------------
 * This file contains several definitions that form the						该文件包含几个定义，这些定义构成了由 Eric Roberts 开发的通用 ANSI C 库的核心。
 * core of a general-purpose ANSI C library developed by Eric				该库的目标是提供一组基本的工具和约定，以提高 C 程序的可读性，
 * Roberts.  The goal of this library is to provide a basic					尤其是在教学环境中使用它们时。
 * set of tools and conventions that increase the readability	
 * of C programs, particularly as they are used in a teaching
 * environment.
 *
 * The basic definitions provided by genlib.h are:							genlib.h 提供的基本定义是：
 *
 *    1.  Declarations for several new "primitive" types						1. 声明几个新的“原始”类型（最重要的是 bool 和 string），
 *        (most importantly bool and string) that are							   在其他库和应用程序中用作基本类型。
 *        used throughout the other libraries and
 *        applications as fundamental types.
 *
 *    2.  A new set of functions for memory allocation.							2. 一组新的内存分配函数。
 *
 *    3.  A function for error handling.										3. 错误处理功能。
 *
 *    4.  A repeat statement for loops with interior exits.						4. 带有内部出口的循环的重复语句。
 */

#ifndef _genlib_h
#define _genlib_h
                                                                           
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "boolean.h"

/* Section 1 -- Define new "primitive" types */                             /*第一部分 -- 定义新的“原始”类型*/

/*
 * Type: string                                                             类型：string
 * ------------                                                             ------------    
 * The type string is identical to the type char *, which is                字符串类型与传统上用于 C 程序的 char * 类型相同。
 * traditionally used in C programs.  The main point of defining a          定义新类型的主要目的是提高程序的可读性。
 * new type is to improve program readability.   At the abstraction         在使用字符串类型的抽象级别上，将字符串分解为其组成字符通常并不重要。
 * levels at which the type string is used, it is usually not               将其声明为字符串强调了这种原子性。
 * important to take the string apart into its component characters.        我看不懂，反正扫雷也用不到。
 * Declaring it as a string emphasizes this atomicity.
 */

typedef char *string;

/*
 * Type: stream                                                             类型：stream
 * ------------                                                             ------------    
 * Like string, the stream type is used to provide additional               与string一样，stream类型用于提供额外的可读性，
 * readability and is defined to be equivalent to FILE *                    并且被定义为等同于 FILE *（这特别令人困惑，因为它违反了标准大小写约定）。
 * (which is particularly confusing because it violates                     这种类型在文本中没有使用，但保存在 genlib.h 中，
 * standard case conventions).  This type is not used in                    因此可以在不暴露任何指针的情况下教授所有 CS1。
 * the text but is preserved in genlib.h, so it is possible                 
 * to teach all of CS1 without exposing any pointers.
 */

typedef FILE *stream;

/*
 * Constant: UNDEFINED                                                      常量：UNDEFINED
 * -------------------                                                      -------------------
 * Besides NULL, the only other constant of pointer type is                 除了 NULL 之外，唯一的其他指针类型常量是 UNDEFINED，
 * UNDEFINED, which is used in certain packages as a special                它在某些包中用作特殊标记，以指示未定义的指针值。
 * sentinel to indicate an undefined pointer value.  In many                在许多这样的情况下，NULL 是一个合法的数据值，因此不适合作为吹哨人(用词真迷)。
 * such contexts, NULL is a legitimate data value and is
 * therefore inappropriate as a sentinel.
 */

#define UNDEFINED ((void *) undefined_object)

extern char undefined_object[];

/* Section 2 -- Memory allocation */                                        /*第二部分 -- 内存分配*/

/*
 * General notes:                                                           一般注意事项：
 * --------------                                                           --------------
 * These functions provide a common interface for memory                    这些函数为内存分配提供了一个通用接口。
 * allocation.  All functions in the library that allocate                  库中所有分配内存的函数都使用 GetBlock 和 FreeBlock。
 * memory do so using GetBlock and FreeBlock.  Even though                  尽管 ANSI 标准出于相同目的定义了 malloc 和 free，
 * the ANSI standard defines malloc and free for the same                   但使用 GetBlock 和 FreeBlock 提供了与非 ANSI 实现的更大兼容性、
 * purpose, using GetBlock and FreeBlock provides greater                   自动内存不足错误检测以及替代垃圾回收分配器的可能性。
 * compatibility with non-ANSI implementations, automatic
 * out-of-memory error detection, and the possibility of
 * substituting a garbage-collecting allocator.
 */

/*
 * Function: GetBlock                                                       函数：GetBlock
 * Usage: ptr = (type) GetBlock(nbytes);                                    Usage: ptr = (type) GetBlock(nbytes);
 * -------------------------------------                                    -------------------------------------
 * GetBlock allocates a block of memory of the given size.  If              GetBlock 分配给定大小的内存块。
 * no memory is available, GetBlock generates an error.                     如果没有可用内存，GetBlock 会生成错误。
 */

void *GetBlock(size_t nbytes);

/*
 * Function: FreeBlock                                                      函数：FreeBlock
 * Usage: FreeBlock(ptr);                                                   使用：FreeBlock(ptr);
 * ----------------------                                                   ----------------------
 * FreeBlock frees the memory associated with ptr, which must               FreeBlock 释放与 ptr 关联的内存，
 * have been allocated using GetBlock, New, or NewArray.                    该内存必须已使用 GetBlock、New 或 NewArray 分配。
 */

void FreeBlock(void *ptr);

/*
 * Macro: New                                                               宏：New   (这个和JAVA还挺像的)
 * Usage: p = New(pointer-type);                                            使用：p = New(pointer-type);
 * -----------------------------                                            -----------------------------
 * The New pseudofunction allocates enough space to hold an                 New 伪函数分配足够的空间来保存指针类型指向的类型的对象，
 * object of the type to which pointer-type points and returns              并返回一个指向新分配的指针的指针。
 * a pointer to the newly allocated pointer.  Note that                     请注意，“New”与 C++ 中使用的“new”运算符不同；
 * "New" is different from the "new" operator used in C++;                  前者采用指针类型，后者采用目标类型。
 * the former takes a pointer type and the latter takes the
 * target type.
 */

#define New(type) ((type) GetBlock(sizeof *((type) NULL)))

/*
 * Macro: NewArray                                                          宏：NewArray
 * Usage: p = NewArray(n, element-type);                                    使用：p = NewArray(n, element-type);
 * -------------------------------------                                    -------------------------------------    
 * NewArray allocates enough space to hold an array of n                    NewArray 分配足够的空间来保存指定元素类型的 n 个值的数组。
 * values of the specified element type.
 */

#define NewArray(n, type) ((type *) GetBlock((n) * sizeof (type)))

/* Section 3 -- Basic error handling */                                     /*第三部分 -- 基本错误处理*/

/*
 * Function: Error                                                          函数：Error
 * Usage: Error(msg, ...)                                                   使用：Error(msg, ...)
 * ----------------------                                                   ----------------------
 * Error generates an error string, expanding % constructions               Error 生成一个错误字符串，扩展出现在错误消息字符串中的 % 结构，就像 printf 一样。
 * appearing in the error message string just as printf does.               如果引入了错误处理程序异常（请参阅“exception.h”工具），
 * If an error handler exception has been introduced (see the               则会引发 ErrorException 异常，并将扩展的错误字符串作为参数。
 * "exception.h" facility), the ErrorException exception is                 如果没有定义 ErrorException，
 * raised with the expanded error string as argument.  If                   则程序退出并带有指示失败的状态代码（由常量 ErrorExitStatus 给出）。
 * there is no ErrorException defined, the program exits                    扩展后的错误消息字符串的长度不能超过 MaxErrorMessage，这是客户端的责任。
 * with a status code indicating failure (as given by the   
 * constant ErrorExitStatus).  The length of the error
 * message string following expansion must not exceed
 * MaxErrorMessage, and it is the client's responsibility
 * to ensure this.
 */

void Error(string msg, ...);

/* Section 4 -- The repeat pseudo-statement */                          /*第四部分 -- 重复的伪语句*/

/*
 * Statement form: repeat { ... }                                       语句形式：repeat { ... }
 * ------------------------------                                       ------------------------------
 * Some instructors who have taught CS1 using this library              一些使用该库教授 CS1 的教师发现，
 * have found that using                                                使用 while (TRUE) 启动带有内部出口的循环会让学生感到困惑，尤其是在课程开始时。
 *                                                                      这个宏将“repeat”定义为一个无限循环结构，供那些发现它更容易解释的教师使用，尽管它没有在文本中使用。
 *     while (TRUE)                                                     类似的宏观定义在工业中很常见。
 *
 * to initiate a loop with an interior exit is confusing to
 * students, particularly when it comes at the beginning of
 * the course.  This macro defines "repeat" as an infinite
 * loop construct for instructors who find it easier to
 * explain, although it is not used in the text.   Similar
 * macro definitions are common in industry.
 */

#define repeat for (;;)

#endif
