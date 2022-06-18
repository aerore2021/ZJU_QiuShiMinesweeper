/*
 * File: exception.h
 * Version: 1.0
 * Last modified on Sun Jul 24 10:26:20 1994 by eroberts
 * -----------------------------------------------------
 * The exception package provides a general exception
 * handling mechanism for use with C that is portable
 * across a variety of compilers and operating systems.
 */

#ifndef _exception_h
#define _exception_h

/*
 * Overview:
 * --------
 * 
 * The exception package makes it possible for clients to                exception package使客户端可以以语法可读的方式为异常条件指定处理程序。 
 * specify a handler for an exceptional conditions in a                  作为客户,
 * syntactically readable way.  As a client, your first step             您的第一步是通过声明异常类型的变量来声明异常条件名称，   
 * is to declare an exception condition name by declaring                   
 * a variable of type exception, as in                                   如
 *
 *       exception MyException;                                          exception Myexception; 
 *
 * Normal visibility rules apply, so that you should declare             由于正常可见性规则，您应该在适当的level声明异常变量。
 * example, if an exception is local to an implementation,               例如，如果异常是某个模块的本地异常，则应在该模块中静态声明。 
 * the exception variable at the appropriate level.  For                 如果一个异常条件由多个模块共享，
 * it should be declared statically within that module.  If              则应在接口中声明异常变量并将其导出到所有需要它的客户端。
 * an exception condition is shared by many modules, the
 * exception variable should be declared in an interface
 * and exported to all clients that need it.  This package
 * defines and exports the exception ErrorException, which
 * is likely to be sufficient for many clients.
 *
 * The basic functionality of exceptions is that one piece               异常的基本功能是一段代码可以“引发”异常，
 * of code can "raise" an exception so that it can then be               然后它可以由程序中动态封闭的部分中的特殊代码“处理”。 
 * "handled" by special code in a dynamically enclosing                  通过使用异常名称调用伪函数 raise 引发异常。
 * section of the program.  Exceptions are raised by calling
 * the pseudo-function raise with the exception name, as in              如   
 *
 *     raise(MyException);                                               raise(MyException);      
 *
 * Exceptions are handled using the "try" statement                      使用“try”语句（实际上是使用宏实现）处理异常，
 * (actually implemented using macros), which has the form:              其形式如下：
 *
 *     try {                                                             try {
 *        . . . statements in the body of the block . . .                    . . . 块(block)中的语句 . . .   
 *     except(exception1)                                                except(exception1)
 *        . . . statements to handle exception 1 . . .                       . . . 处理exception 1的语句 . . .
 *     except(exception2)                                                except(exception2)
 *        . . . statements to handle exception 2 . . .                       . . . 处理exception 2的语句 . . .
 *     except(ANY)                                                       except（ANY)       
 *        . . . statements to handle any exception . . .                     . . . 处理ANY异常的语句 . . .
 *     } endtry                                                          } endtry       
 *
 * Any number of except clauses may appear (up to a                      可以出现任意数量的 except 子句
 * maximum defined by the constant MaxExceptionsPerScope),               （最多由常量 MaxExceptionsPerScope 定义），
 * and the ANY clause is optional.                                       并且 ANY 子句是可选的。   
 *
 * When the program encounters the "try" statement, the                  当程序遇到“try”语句时，执行“try”中的语句。
 * statements in the body are executed.  If no exception                 如果在执行期间(无论是在此块中还是通过嵌套在此块内的函数调用)   
 * conditions are raised during that execution, either                   没有引发异常条件，   
 * in this block or by a function call nested inside                     执行完块(block)的语句，就直接来到try的末尾；
 * this block, control passes to the end of the "try"                    如果在块的动态执行期间引发异常，
 * statement when the last statement in the block is                     则控制立即传递给适当的 except 子句中的语句。
 * executed.  If an exception is raised during the                       仅执行该子句中的语句；退出块不需要 break 语句。
 * dynamic execution of the block, control immediately                   如果在控制历史中的任何地方都没有出现引发异常的处理程序，
 * passes to the statements in the appropriate except                    则程序将错误地退出。
 * clause.  Only the statements in that clause are
 * executed; no break statement is required to exit
 * the block.  If no handler for the raised exception
 * appears anywhere in the control history, the program
 * exits with an error.
 *
 * Examples of use:                                                      运用实例：
 *
 * 1.  Catching errors.                                                  1.  捕捉Errors。  
 *
 * The following code fragment traps calls to Error, so                  以下代码片段捕获对 Error（genlib.h） 的调用，
 * that the program does not quit but instead returns                    因此程序不会退出，
 * to the top-level read-and-execute loop.                               而是返回到顶层(top-level)读取和执行循环。
 *
 *     while (TRUE) {
 *         try {
 *             printf("> ");
 *             cmd = ReadCommand();
 *             ExecuteCommand(cmd);
 *         except(ErrorException)
 *             -- additional handling code, if any --
 *         } endtry
 *     }
 *
 * If either ReadCommand or ExecuteCommand calls Error,                  如果 ReadCommand 或 ExecuteCommand 调用了 Error，
 * control will be passed back to the main loop, after                   则在执行任何其他处理程序代码后，
 * executing any additional handler code.  (The error                    控制将被传递回主循环。
 * message is printed by the Error routine, so it is                     （错误消息由 Error 例程打印，因此通常不需要额外的工作。）
 * often the case that no additional work is needed.)                    没看懂就看例2.
 *
 * 2.  Handling control-C                                                2.  处理 control-C   
 *
 * The following code extends the example above so that                  以下代码扩展了上面的示例，以便键入 ^C 也返回到顶层。
 * typing ^C also returns to top-level.
 *
 *     #include <signal.h>
 *
 *     static exception ControlCException;
 *     static int errorCount = 0;
 *     static int ControlCHandler();
 *
 *     main()
 *     {
 *         string cmd;
 *
 *         signal(SIGINT, ControlCHandler);
 *         while (TRUE) {
 *             try {
 *                 printf("> ");
 *                 cmd = ReadCommand();
 *                 ExecuteCommand(cmd);
 *             except(ControlCException);
 *                 printf("^C\n");
 *                 signal(SIGINT, ControlCHandler);
 *             except(ErrorException)
 *                 errorCount++;
 *             } endtry
 *         }
 *     }
 *
 *     static int ControlCHandler()
 *     {
 *         raise(ControlCException);
 *     }
 */

/*
 * Actual interface specification                                        实际接口规范
 * ------------------------------                                        ------------------------------
 * Most of the implementation of the exception mechanism is              异常机制的大部分实现实际上都是在这个文件定义的宏中完成的。   
 * actually done in the macros defined by this file.                     客户通常应该能够阅读上面的描述而忽略下面的详细代码。
 * Clients should ordinarily be able to read the description
 * above and ignore the detailed code below.
 */

#include <setjmp.h>
#include <string.h>
#include "genlib.h"

/* Define parameters and error status indicators */

#define MaxExceptionsPerScope 10
#define ETooManyExceptClauses 101
#define EUnhandledException 102

/* Codes to keep track of the state of the try handler */

#define ES_Initialize 0
#define ES_EvalBody 1
#define ES_Exception 2

/*
 * Type: exception
 * ---------------
 * Exceptions are specified by their address, so that the
 * actual structure does not matter.  Strings are used here
 * so that exporters of exceptions can store the exception
 * name for the use of debuggers and other tools.
 */

typedef struct { string name; } exception;

/*
 * Type: context_block
 * -------------------
 * This structure is used internally to maintain a chain of
 * exception scopes on the control stack.
 */

typedef struct ctx_block {
    jmp_buf jmp;
    int nx;
    exception *array[MaxExceptionsPerScope];
    exception *id;
    void *value;
    string name;
    struct ctx_block *link;
} context_block;

/* Declare the built-in exceptions */

extern exception ErrorException;
extern exception ANY;

/* Declare a global pointer to the context stack */

extern context_block *exceptionStack;

/*
 * Function: RaiseException
 * Usage: RaiseException(&e, name, value);
 * ---------------------------------------
 * This function is called by the raise macro and does the
 * work necessary to raise the exception.  See the exception.c file
 * for details.  Clients do not ordinarily call this directly.
 */

void RaiseException(exception *e, string name, void *value);

/*
 * Function: HandlerExists
 * Usage: if (HandlerExists(&e)) ...
 * ---------------------------------
 * Determines whether a handler exists for an exception in
 * the dynamically enclosing scope.  Intended only for use
 * by special clients, such as the Error package.
 */

bool HandlerExists(exception *e);

/* Define the pseudo-functions for raise and try */

#define raise(e) RaiseException(&e, #e, NULL)

#define try \
      { \
          jmp_buf _tmpbuf; \
          context_block _ctx; \
          volatile int _es; \
          _es = ES_Initialize; \
          _ctx.nx = 0; \
          _ctx.link = exceptionStack; \
          exceptionStack = (context_block *) &_ctx; \
          if (setjmp(_tmpbuf) != 0) _es = ES_Exception; \
          memcpy((void *) _ctx.jmp, (void *) _tmpbuf, sizeof(jmp_buf)); \
          while (1) { \
              if (_es == ES_EvalBody)

#define except(e) \
                  if (_es == ES_EvalBody) exceptionStack = _ctx.link; \
                  break; \
              } \
              if (_es == ES_Initialize) { \
                  if (_ctx.nx >= MaxExceptionsPerScope) \
                      exit(ETooManyExceptClauses); \
                  _ctx.array[_ctx.nx++] = &e; \
              } else if (_ctx.id == &e || &e == &ANY) { \
                  exceptionStack = _ctx.link;

#define endtry \
              if (_es != ES_Initialize) break; \
              _es = ES_EvalBody; \
          } \
      }

#define GetExceptionName() _ctx.name
#define GetExceptionValue() _ctx.value
#define GetCurrentException() _ctx.id

#endif
