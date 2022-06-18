/*
 * File: graphics.h
 * Version: 1.0
 * Last modified on Mon Jun  6 11:03:27 1994 by eroberts
 * -----------------------------------------------------
 * This interface provides access to a simple library of
 * functions that make it possible to draw lines and arcs
 * on the screen.  This interface presents a portable
 * abstraction that can be used with a variety of window
 * systems implemented on different hardware platforms.
 */

#ifndef _graphics_h
#define _graphics_h
/*
 * Overview
 * --------
 * This library provides several functions for drawing lines                这个库提供了几个函数，用于在定义为“图形窗口”的屏幕区域中绘制直线和圆弧。
 * and circular arcs in a region of the screen that is                      一旦绘制出来，这些线条和弧线就保持在它们的位置，
 * defined as the "graphics window."  Once drawn, these                     这意味着该包只能用于静态图片，不能用于动画。
 * lines and arcs stay in their position, which means that
 * the package can only be used for static pictures and not
 * for animation.
 *
 * Individual points within the window are specified by                     窗口内的各个点通过给出它们的 x 和 y 坐标来指定。
 * giving their x and y coordinates.  These coordinates are                 这些坐标是以英寸为单位的实数，原点在左下角，就像在传统数学中一样。
 * real numbers measured in inches, with the origin in the
 * lower left corner, as it is in traditional mathematics.
 *
 * The calls available in the package are listed below.  More               
 * complete descriptions are included with each function                    
 * description.
 *
 *   InitGraphics();
 *   MovePen(x, y);
 *   DrawLine(dx, dy);
 *   DrawArc(r, start, sweep);
 *   width = GetWindowWidth();
 *   height = GetWindowHeight();
 *   x = GetCurrentX();
 *   y = GetCurrentY();
 */

/*
 * Function: InitGraphics                                                   函数：InitGraphics 
 * Usage: InitGraphics();                                                   使用：InitGraphics();
 * ----------------------                                                   ----------------------
 * This procedure creates the graphics window on the screen.                此过程在屏幕上创建图形窗口。 
 * The call to InitGraphics must precede any calls to other                 对 InitGraphics 的调用必须在对该包中其他函数的任何调用之前，
 * functions in this package and must also precede any printf               并且还必须在任何 printf 输出之前。
 * output.  In most cases, the InitGraphics call is the first               在大多数情况下，InitGraphics 调用是函数 main 中的第一条语句。
 * statement in the function main.
 */

void DrawBackground();

void InitGraphics(void);

void InitConsole(void);

/*
 * Function: MovePen                                                        函数：MovePen
 * Usage: MovePen(x, y);                                                    使用：MovePen(x, y);
 * ---------------------                                                    ---------------------    
 * This procedure moves the current point to the position                   此过程将当前点移动到位置 (x, y)，而不画线。
 * (x, y), without drawing a line.  The model is that of                    该模型是笔从图形窗口表面抬起然后移动到新位置的模型。
 * the pen being lifted off the graphics window surface and
 * then moved to its new position.
 */

void MovePen(double x, double y);


/*
 * Function: DrawLine                                                       函数：DrawLine
 * Usage: DrawLine(dx, dy);                                                 使用：DrawLine(dx, dy);
 * ------------------------                                                 ------------------------    
 * This procedure draws a line extending from the current                   此过程通过在 x 方向移动笔 dx 英寸和在 y 方向移动 dy 英寸来绘制一条从当前点延伸的线。
 * point by moving the pen dx inches in the x direction                     最终位置成为新的当前点。
 * and dy inches in the y direction.  The final position
 * becomes the new current point.
 */

void MsgOut();

void DrawLine(double dx, double dy);

/*
 * Function: DrawArc                                                        函数：DrawArc
 * Usage: DrawArc(r, start, sweep);                                         使用：DrawArc(r, start, sweep);
 * --------------------------------                                         --------------------------------
 * This procedure draws a circular arc, which always begins                 此过程绘制一个始终从当前点开始的圆弧。
 * at the current point.  The arc itself has radius r, and                  圆弧本身的半径为 r，并以参数 start 指定的角度相对于圆心开始。
 * starts at the angle specified by the parameter start,                    这个角度是从 3 点钟位置沿 x 轴逆时针测量的角度，与传统数学一样。
 * relative to the center of the circle.  This angle is                     例如，如果 start 为 0，则圆弧从 3 点钟位置开始；
 * measured in degrees counterclockwise from the 3 o'clock                  如果 start 为 90，则圆弧从 12 点钟位置开始；等等；
 * position along the x-axis, as in traditional mathematics.                绘制的圆弧的角度由sweep参数指定，该参数也以度为单位。
 * For example, if start is 0, the arc begins at the 3 o'clock              如果sweep为360，DrawArc画一个完整的圆；
 * position; if start is 90, the arc begins at the 12 o'clock               如果扫描为 90，则绘制四分之一圆。
 * position; and so on.  The fraction of the circle drawn is                如果 sweep 的值为正，则从当前点逆时针绘制圆弧。
 * specified by the parameter sweep, which is also measured in              如果 sweep 为负数，则从当前点顺时针绘制圆弧。
 * degrees.  If sweep is 360, DrawArc draws a complete circle;              DrawArc 操作结束时的当前点是笔沿弧线的最终位置。
 * if sweep is 90, it draws a quarter of a circle.  If the value
 * of sweep is positive, the arc is drawn counterclockwise from
 * the current point.  If sweep is negative, the arc is drawn
 * clockwise from the current point.  The current point at the
 * end of the DrawArc operation is the final position of the pen
 * along the arc.
 *
 * Examples:
 *   DrawArc(r, 0, 360)    Draws a circle to the left of the
 *                         current point.
 *   DrawArc(r, 90, 180)   Draws the left half of a semicircle
 *                         starting from the 12 o'clock position.
 *   DrawArc(r, 0, 90)     Draws a quarter circle from the 3
 *                         o'clock to the 12 o'clock position.
 *   DrawArc(r, 0, -90)    Draws a quarter circle from the 3
 *                         o'clock to the 6 o'clock position.
 *   DrawArc(r, -90, -90)  Draws a quarter circle from the 6
 *                         o'clock to the 9 o'clock position.
 */

void DrawArc(double r, double start, double sweep);

/*
 * Functions: GetWindowWidth, GetWindowHeight                               函数：GetWindowWidth, GetWindowHeight
 * Usage: width = GetWindowWidth();                                         使用：width = GetWindowWidth();
 *        height = GetWindowHeight();                                             height = GetWindowHeight();
 * ------------------------------------------                               ------------------------------------------
 * These functions return the width and height of the graphics              这些函数返回图形窗口的宽度和高度，以英寸为单位。
 * window, in inches.
 */

double GetWindowWidth(void);
double GetWindowHeight(void);

/*
 * Functions: GetCurrentX, GetCurrentY                                      函数：GetCurrentX, GetCurrentY
 * Usage: x = GetCurrentX();                                                懂得都懂。
 *        y = GetCurrentY();
 * -----------------------------------
 * These functions return the current x and y positions.
 */

double GetCurrentX(void);
double GetCurrentY(void);

void Main();

/*下面的几个枚举是很重要的*/

/*鼠标按钮*/
typedef enum
{
    NO_BUTTON = 0,
    LEFT_BUTTON,
    MIDDLE_BUTTON,
    RIGHT_BUTTON
} ACL_Mouse_Button;
/*鼠标事件*/
typedef enum 
{
    BUTTON_DOWN,
    BUTTON_DOUBLECLICK,
    BUTTON_UP,
    ROLL_UP,
    ROLL_DOWN,
    MOUSEMOVE	
} ACL_Mouse_Event;
/*键盘事件*/
typedef enum 
{
	KEY_DOWN,
	KEY_UP
} ACL_Keyboard_Event;

typedef void (*KeyboardEventCallback) (int key,int event);
typedef void (*CharEventCallback) (char c);
typedef void (*MouseEventCallback) (int x, int y, int button, int event);
typedef void (*TimerEventCallback) (int timerID);
/* 注册的函数，交互事件必需，有空的uu看看翁恺的慕课，bilibili也有，讲得很清楚*/
void registerKeyboardEvent(KeyboardEventCallback callback);
void registerCharEvent(CharEventCallback callback);
void registerMouseEvent(MouseEventCallback callback);
void registerTimerEvent(TimerEventCallback callback);

void cancelKeyboardEvent();
void cancelCharEvent();
void cancelMouseEvent();
void cancelTimerEvent();
void startTimer(int id, int timeinterval);

void DisplayClear();

#endif
