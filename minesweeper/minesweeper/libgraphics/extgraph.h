/*
 * File: extgraph.h
 * Version: 3.0
 * Last modified on Tue Oct  4 11:24:41 1994 by eroberts
 * -----------------------------------------------------
 * This interface is the extended graphics interface.               该接口是扩展图形接口。
 * It includes all of the facilities in graphics.h, plus            它包括 graphics.h 中的所有功能，
 * several additional functions that are designed to                及一些旨在支持更复杂、交互式图形的附加功能。
 * support more sophisticated, interactive graphics.
 */

#ifndef _extgraph_h
#define _extgraph_h

#include "genlib.h"

/* Exported functions */                                           

/* Section 1 -- Basic functions from graphics.h */

#include "graphics.h"

/* Section 2 -- Elliptical arcs */                                  /*第二部分 -- 椭圆弧*/

/*
 * Function: DrawEllipticalArc                                      函数：画椭圆弧                                           
 * Usage: DrawEllipticalArc(rx, ry, start, sweep);                  
 * -----------------------------------------------
 * This procedure draws an elliptical arc.  It is exactly           此过程绘制椭圆弧。 
 * the same in its operation as DrawArc in the graphics.h           其操作与 graphics.h 界面中的 DrawArc 完全相同，
 * interface, except that the radius is different along the         只是半径沿两个轴不同。
 * two axes.
 */

void DrawEllipticalArc(double rx, double ry,
                       double start, double sweep);

/* Section 3 -- Graphical regions*/                                 /*第三部分 -- 图形区域*/

/*
 * Functions: StartFilledRegion, EndFilledRegion
 * Usage: StartFilledRegion(density);
 *        . . . other calls . . .
 *        EndFilledRegion();
 * ------------------------------
 * These calls make it possible to draw filled shapes on the        这是用来填充形状的调用。
 * display.  After calling StartFilledRegion, any calls to          调用 StartFilledRegion 后，         
 * DrawLine and DrawArc are used to create a shape definition       对 DrawLine 和 DrawArc 的任何调用都用于创建对于形状的定义，
 * and do not appear on the screen until EndFilledRegion is         并且在调用 EndFilledRegion 之前不会出现在屏幕上。
 * called.  The lines and arcs must be consecutive, in the          线条和弧线必须是连续的，即每个新元素必须从最后一个元素结束的地方开始。
 * sense that each new element must start where the last            MovePen 调用只能发生在区域的开头或结尾，而不会发生在内部。
 * one ended.  MovePen calls may occur at the beginning             当 EndFilledRegion 被调用时，整个区域出现在屏幕上，其内部被填充。
 * or the end of the region, but not in the interior. When          密度参数(density)是一个介于 0 和 1 之间的数字，指示如何将点密度用于填充图案。
 * EndFilledRegion is called, the entire region appears on the      如果密度为1，则形状将填充为纯色； 如果为 0，则填充将不可见。
 * screen, with its interior filled in.  The density parameter      在这两者之间，则以一些点着色、另一些点不着色为实施。
 * is a number between 0 and 1 and indicates how the dot density
 * to be used for the fill pattern.  If density is 1, the shape
 * will be filled in a solid color; if it is 0, the fill will be
 * invisible.  In between, the implementation will use a dot
 * pattern that colors some of the screen dots but not others.
 */

void StartFilledRegion(double density);
void EndFilledRegion(void);

/* Section 4 -- String functions */                                 /*第四部分 -- 字符串函数*/

/*
 * Function: DrawTextString                                         函数：DrawTextString
 * Usage: DrawTextString(text);                                     使用：DrawTextString(text);
 * ----------------------------                                     ----------------------------
 * This function displays the string text at the current point      该函数以当前字体和大小显示当前点的字符串文本。
 * in the current font and size.  The current point is updated      目前点会被更新，以便下一个 DrawTextString 命令将从下一个字符位置继续。
 * so that the next DrawTextString command would continue from      字符串不得包含换行符。
 * the next character position.  The string may not include the
 * newline character.
 */

void DrawTextString(string text);

/*
 * Function: TextStringWidth                                        函数：TextStringWidth
 * Usage: w = TextStringWidth(text);                                使用：w = TextStringWidth(text);
 * ---------------------------------                                ----------------------------
 * This function returns the width of the text string if displayed  如果以当前字体和大小显示，此函数返回文本字符串的宽度。
 * at the current font and size.
 */

double TextStringWidth(string text);

/*
 * Function: SetFont                                                函数：SetFont
 * Usage: SetFont(font);                                            使用：SetFont(font);
 * ---------------------                                            ---------------------
 * This function sets a new font according to the font string,      该函数根据字体字符串设置新字体，不区分大小写。
 * which is case-independent.  Different systems support different  不同的系统支持不同的字体，但通常支持“Times”和“Courier”等常见字体。
 * fonts, although common ones like "Times" and "Courier" are often 最初，字体设置为始终支持的“默认”，而底层字体取决于系统。
 * supported.  Initially, the font is set to "Default" which is     如果字体名称无法识别，则不会产生错误，字体保持不变。
 * always supported, although the underlying font is system         如果您需要检测这种情况，您可以调用 GetFont 来查看更改是否生效。
 * dependent.  If the font name is unrecognized, no error is        通过在这种情况下不产生错误，程序变得更加可移植。
 * generated, and the font remains unchanged.  If you need to
 * detect this condition, you can call GetFont to see if the
 * change took effect.  By not generating an error in this case,
 * programs become more portable.
 */

void SetFont(string font);

/*
 * Function: GetFont                                                函数：GetFont
 * Usage: font = GetFont();                                         使用：font = GetFont();            
 * ------------------------                                         ------------------------
 * This function returns the current font name as a string.         不解释。
 */

string GetFont(void);

/*
 * Function: SetPointSize                                           函数：SetPointSize                             
 * Usage: SetPointSize(size);                                       使用：SetPointSize(size);            
 * --------------------------                                       ------------------------
 * This function sets a new point size.  If the point size is       如果特定字体不支持磅值，则选择最接近的现有大小。
 * not supported for a particular font, the closest existing
 * size is selected.
 */

void SetPointSize(int size);

/*
 * Function: GetPointSize                                           函数：GetPointSize
 * Usage: size = GetPointSize();                                    使用：size = GetPointSize();
 * -----------------------------
 * This function returns the current point size.
 */

int GetPointSize(void);

/*
 * Text style constants                                             文本样式常量
 * --------------------                                             --------------------
 * The constants Bold and Italic are used in the SetStyle           在 SetStyle 命令中使用常量 Bold 和 Italic 来指定所需的文本样式。
 * command to specify the desired text style.  They may also        它们也可以通过将这些常量加在一起来组合使用，如粗体 + 斜体。
 * be used in combination by adding these constants together,       常量 Normal 表示默认样式。
 * as in Bold + Italic.  The constant Normal indicates the
 * default style.
 */

#define Normal  0
#define Bold    1
#define Italic  2

/*
 * Function: SetStyle                                               函数：SetStyle
 * Usage: SetStyle(style);
 * -----------------------                                          -----------------------
 * This function establishes the current style properties           此函数根据参数 style 建立文本的当前样式属性，
 * for text based on the parameter style, which is an integer       该参数是一个整数，表示任何文本样式常量的总和。
 * representing the sum of any of the text style constants.
 */

void SetStyle(int style);

/*
 * Function: GetStyle                                               函数：GetStyle
 * Usage: style = GetStyle();
 * --------------------------
 * This function returns the current style.
 */

int GetStyle(void);

/*
 * Functions: GetFontAscent, GetFontDescent, GetFontHeight          函数：GetFontAscent, GetFontDescent, GetFontHeight
 * Usage: ascent = GetFontAscent();
 *        descent = GetFontDescent();
 *        height = GetFontHeight();
 * -------------------------------------------------------          -------------------------------------------------------
 * These functions return properties of the current font that are   这些函数返回当前字体的属性，用于计算如何在页面上垂直放置文本。
 * used to calculate how to position text vertically on the page.   FontAscent是从基线到最大字符顶部的距离；
 * The ascent of a font is the distance from the baseline to the    FontDescent是任何字符延伸到基线以下的最大距离。
 * top of the largest character; the descent is the maximum         FontHeigh是两行文本之间的总距离，包括行间距（称为行距）。
 * distance any character extends below the baseline.  The height
 * is the total distance between two lines of text, including the
 * interline space (which is called leading).
 *
 * Examples:                                                        例：
 *   To change the value of y so that it indicates the next text        要更改 y 的值以使其指向下一个文本行，
 *   line, you need to execute                                          您需要执行
 *
 *        y -= GetFontHeight();                                              y -= GetFontHeight();
 *
 *   To center text vertically around the coordinate y, you need        在坐标 y 垂直居中文本，
 *   to start the pen at                                                您需要将笔从
 *
 *       y - GetFontAscent() / 2                                            y - GetFontAscent() / 2
 */

double GetFontAscent(void);
double GetFontDescent(void);
double GetFontHeight(void);

/* Section 5 -- Mouse support */                                        /*第五部分 -- 鼠标支持*/

/*
 * Functions: GetMouseX, GetMouseY                                      函数：GetMouseX, GetMouseY
 * Usage: x = GetMouseX();
 *        y = GetMouseY();                                      
 * -------------------------------                                      -------------------------------
 * These functions return the x and y coordinates of the mouse,         不解释。
 * respectively.  The coordinate values are real numbers measured
 * in inches from the origin and therefore match the drawing
 * coordinates.
 */

double GetMouseX(void);
double GetMouseY(void);

/*
 * Functions: MouseButtonIsDown                                         函数：MouseButtonIsDown
 * Usage: if (MouseButtonIsDown()) . . .                                使用：Usage: if (MouseButtonIsDown()) . . .
 * -------------------------------------                                -------------------------------------
 * This function returns TRUE if the mouse button is currently          如果鼠标按钮当前按下，此函数返回 TRUE。
 * down.  For maximum compatibility among implementations, the          为了最大兼容性，假定鼠标具有一个按钮。
 * mouse is assumed to have one button.  If the mouse has more          如果鼠标有多个按钮，则此函数在任何按钮按下时返回 TRUE。
 * than one button, this function returns TRUE if any button
 * is down.
 */

bool MouseButtonIsDown(void);

/*
 * Functions: WaitForMouseDown, WaitForMouseUp                          函数：WaitForMouseDown, WaitForMouseUp 
 * Usage: WaitForMouseDown();                                           使用：WaitForMouseDown();
 *        WaitForMouseUp();                                                   WaitForMouseUp();
 * -------------------------------------------                          -------------------------------------------
 * The WaitForMouseDown function waits until the mouse button           WaitForMouseDown 函数等待直到按下鼠标按钮然后返回。 
 * is pressed and then returns.  WaitForMouseUp waits for the           WaitForMouseUp 等待按钮被释放。
 * button to be released.
 */

void WaitForMouseDown(void);
void WaitForMouseUp(void);

/* Section 6 -- Color support */                                        /*第六部分 -- 颜色支持*/

/*
 * Function: HasColor                                                   函数：HasColor
 * Usage: if (HasColor()) . . .                                         使用：if (HasColor()) . . .
 * ----------------------------                                         ----------------------------
 * This function returns TRUE if the graphics window can display a      如果图形窗口可以显示彩色图像，此函数返回 TRUE。
 * color image.  Note that this condition is stronger than simply       请注意，此条件比简单地检查彩色显示器是否可用要强。
 * checking whether a color display is available.  Because color        因为彩色窗口比黑白窗口需要更多的内存，
 * windows require more memory than black and white ones, this          所以如果没有足够的内存来存储彩色图像，此函数将返回 FALSE 并显示彩色屏幕。
 * function will return FALSE with a color screen if there is           例如，在 Macintosh 上，通常需要将分区大小增加到至少 1MB，然后才能创建彩色窗口。
 * not enough memory to store a colored image.  On the Macintosh,
 * for example, it is usually necessary to increase the partition
 * size to at least 1MB before color windows can be created.
 */

bool HasColor(void);

/*
 * Function: SetPenColor                                                函数：SetPenColor
 * Usage: SetPenColor(color);                                           使用：SetPenColor(color);
 * --------------------------                                           --------------------------
 * This function sets the color of the pen used for any drawing,        此函数设置用于任何绘图的笔的颜色，包括线条、文本和填充区域。
 * including lines, text, and filled regions.  The color is a           颜色是一个字符串，通常是以下预定义颜色名称之一：
 * string, which will ordinarily be one of the following
 * predefined color names:
 *
 *    Black, Dark Gray, Gray, Light Gray, White,                            黑色，深灰色，灰色，浅灰色，白色，
 *    Red, Yellow, Green, Cyan, Blue, Magenta                               红色、黄色、绿色、青色、蓝色、品红色
 *
 * The first line corresponds to standard gray scales and the           第一行对应标准灰度，第二行对应光的原色和二次色。
 * second to the primary and secondary colors of light.  The            内置设置仅限于这些颜色，因为它们可能在所有硬件设备上都是相同的。
 * built-in set is limited to these colors because they are             对于更精细的颜色控制，您也可以使用 DefineColor 函数来创建新的颜色名称。
 * likely to be the same on all hardware devices.  For finer
 * color control, you can use the DefineColor function to
 * create new color names as well.
 */

void SetPenColor(string color);

/*
 * Function: GetPenColor                                                函数：GetPenColor
 * Usage: color = GetPenColor();
 * -----------------------------
 * This function returns the current pen color as a string.
 */

string GetPenColor(void);

/*
 * Function: SetPenSize                                                 函数：SetPenSize
 * Usage: SetPenSize(size);
 * -----------------------------------------
 * This function sets the size(in pixels) of the pen used for any drawing.
 */

void SetPenSize(int size);

/*
 * Function: GetPenSize                                                 函数：GetPenSize
 * Usage: size = GetPenSize();
 * -----------------------------------------
 * This function returns the size(in pixels) of the pen used for any drawing.
 */

int GetPenSize(void);

/*
 * Function: DefineColor                                                函数：DefineColor
 * Usage: DefineColor(name, red, green, blue);                          使用：DefineColor(name, red, green, blue);
 * -------------------------------------------                          -------------------------------------------
 * This function allows the client to define a new color name           此功能允许客户端通过为红色、绿色和蓝色（它们是光的原色）提供强度级别来定义新的颜色名称。
 * by supplying intensity levels for the colors red, green,             颜色值以 0 到 1 之间的实数形式提供，表示该颜色的强度。
 * and blue, which are the primary colors of light.  The                例如，预定义的颜色洋红色(Magenta)具有全强度的红色和蓝色，
 * color values are provided as real numbers between 0 and 1,           但没有绿色，因此定义为：
 * indicating the intensity of that color.  For example,
 * the predefined color Magenta has full intensity red and
 * blue but no green and is therefore defined as:
 *
 *      DefineColor("Magenta", 1, 0, 1);                                    DefineColor("Magenta", 1, 0, 1);
 *
 * DefineColor allows you to create intermediate colors on              DefineColor 允许您在许多显示器上创建中间颜色，尽管结果因硬件而异。
 * many displays, although the results vary significantly               (同时你得知道各种颜色是怎么配出来的。)
 * depending on the hardware.  For example, the following               例如，以下通常给出棕色的合理近似值：
 * usually gives a reasonable approximation of brown:
 *
 *      DefineColor("Brown", .35, .20, .05);                                DefineColor("Brown", .35, .20, .05);
 */

void DefineColor(string name,
                 double red, double green, double blue);

/* Section 7 -- Miscellaneous functions */                              /*第七部分 -- 杂项函数*/

/*
 * Function: SetEraseMode                                               函数：SetEraseMode
 * Usage: SetEraseMode(TRUE);                                           使用：SetEraseMode(TRUE);
 *        SetEraseMode(FALSE);                                                SetEraseMode(FALSE);  
 * ---------------------------                                          ---------------------------        
 * The SetEraseMode function sets the value of the internal             SetEraseMode 函数设置内部擦除标志的值。
 * erasing flag.  Setting this flag is similar to setting the           设置此标志的效果类似于将颜色设置为“白色”，但不影响当前颜色设置。
 * color to "White" in its effect but does not affect the               当擦除模式设置为 FALSE 时，使用当前颜色恢复正常绘图。
 * current color setting.  When erase mode is set to FALSE,
 * normal drawing is restored, using the current color.
 */

void SetEraseMode(bool mode);

/*
 * Function: GetEraseMode                                               函数：GetEraseMode
 * Usage: mode = GetEraseMode();
 * -----------------------------
 * This function returns the current state of the erase mode flag.
 */

bool GetEraseMode(void);

/*
 * Function: SetWindowTitle                                             函数：SetWindowTitle
 * Usage: SetWindowTitle(title);                                        使用：SetWindowTitle(title);    
 * -----------------------------                                        -----------------------------
 * This function sets the title of the graphics window, if such         最常用的函数之一。
 * an operation is possible on the display.  If it is not possible      懂得都懂。
 * for a particular implementation, the call is simply ignored.         应该在调用 InitGraphics 之前调用此函数以设置窗口的初始名称。
 * This function may be called prior to the InitGraphics call to
 * set the initial name of the window.
 */

void SetWindowTitle(string title);

/*
 * Function: GetWindowTitle                                             函数：GetWindowTitle
 * Usage: title = GetWindowTitle();
 * --------------------------------
 * This function returns the title of the graphics window.  If the
 * implementation does not support titles, this call returns the
 * empty string.
 */

string GetWindowTitle(void);

/*
 * Function: UpdateDisplay                                              函数：UpdateDisplay
 * Usage: UpdateDisplay();                                              使用：UpdateDisplay();
 * -----------------------                                              -----------------------
 * This function initiates an immediate update of the graphics          此函数启动图形窗口的一次即时更新，是动画所必需的。
 * window and is necessary for animation.  Ordinarily, the              通常，仅当程序等待用户输入时才更新图形窗口。
 * graphics window is updated only when the program waits for
 * user input.
 */

void UpdateDisplay(void);

/*
 * Function: Pause                                                      函数：Pause
 * Usage: Pause(seconds);                                               使用：Pause(seconds);
 * ----------------------                                               ----------------------        
 * The Pause function updates the graphics window and then              该函数会先更新图形窗口，然后暂停指定的秒数。
 * pauses for the indicated number of seconds.  This function           对于运动会太快的动画很有用。
 * is useful for animation where the motion would otherwise
 * be too fast.
 */

void Pause(double seconds);

/*
 * Function: ExitGraphics                                               函数：ExitGraphics
 * Usage: ExitGraphics();                                               使用：ExitGraphics();
 * ----------------------                                               ----------------------
 * The ExitGraphics function closes the graphics window and             ExitGraphics 函数关闭图形窗口并退出应用程序，
 * exits from the application without waiting for any additional        而无需等待任何额外的用户交互。
 * user interaction.
 */

void ExitGraphics(void);

/*
 * Functions: SaveGraphicsState, RestoreGraphicsState                   函数：SaveGraphicsState, RestoreGraphicsState
 * Usage: SaveGraphicsState();                                          使用：SaveGraphicsState();        
 *        . . . graphical operations . . .                                    . . . 图形操作 . . .
 *        RestoreGraphicsState();                                             RestoreGraphicsState();      
 * ---------------------------------------------------                  ---------------------------------------------------
 * The SaveGraphicsState function saves the current graphics            SaveGraphicsState 函数在内部保存当前图形状态（当前笔位置、字体、点大小和擦除模式标志），
 * state (the current pen position, the font, the point size,           以便下一次调用 RestoreGraphicsState 可以恢复它们。
 * and the erase mode flag) internally, so that they can be             这两个函数必须成对使用，但可以嵌套到任意深度。
 * restored by the next RestoreGraphicsState call.  These two           
 * functions must be used in pairs but may be nested to any depth.
 */

void SaveGraphicsState(void);
void RestoreGraphicsState(void);

/*
 * Functions: GetFullScreenWidth, GetFullScreenHeight                   函数：GetFullScreenWidth, GetFullScreenHeight
 * Usage: width = GetFullScreenWidth();                                 使用：width = GetFullScreenWidth();    
 *        height = GetFullScreenHeight();                                     height = GetFullScreenHeight();
 * --------------------------------------                               --------------------------------------
 * These functions return the height and width of the entire            这些函数返回整个显示屏幕的高度和宽度，而不是图形窗口。
 * display screen, not the graphics window.  Their only                 它们唯一重要的用途是用于需要根据可用屏幕空间调整图形窗口大小的应用程序。
 * significant use is for applications that need to adjust              这些函数可以在调用 InitGraphics 之前调用。
 * the size of the graphics window based on available screen
 * space.  These functions may be called before InitGraphics
 * has been called.
 */

double GetFullScreenWidth(void);
double GetFullScreenHeight(void);

/*
 * Functions: SetWindowSize                                             函数：SetWindowSize
 * Usage: SetWindowSize(width, height);                                 使用：SetWindowSize(width, height);
 * ------------------------------------                                 ------------------------------------
 * This function sets the window size to the indicated dimensions,      如果可能，此函数将窗口大小设置为指示的尺寸。
 * if possible.  This function should be called before the graphics     该函数应在 InitGraphics 创建图形窗口之前调用。
 * window is created by InitGraphics.  Attempts to change the size      大多数执行都会忽略更改现有窗口大小的尝试。
 * of an existing window are ignored by most implementations.  This     应谨慎使用此功能，因为它会降低应用程序的可移植性，
 * function should be used sparingly because it reduces the             特别是当客户端请求的空间超过屏幕上的可用空间时。
 * portability of applications, particularly if the client
 * requests more space than is available on the screen.
 */

void SetWindowSize(double width, double height);

/*
 * Functions: GetXResolution, GetYResolution                            函数：GetXResolution, GetYResolution
 * Usage: xres = GetXResolution();                                      使用：xres = GetXResolution();
 *        yres = GetYResolution();                                            yres = GetYResolution();
 * -----------------------------------------                            -----------------------------------------
 * These functions return the number of pixels per inch along           这些函数返回沿每个坐标方向每英寸的像素数，
 * each of the coordinate directions and are useful for applications    对于在点间距方面均匀表示短距离很重要的应用程序非常有用。
 * in which it is important for short distances to be represented       即使大多数显示器的 x 和 y 分辨率相同，客户端也不应依赖此属性。    
 * uniformly in terms of dot spacing.  Even though the x and y
 * resolutions are the same for most displays, clients should
 * not rely on this property.
 *
 * Note: Lines in the graphics library are one pixel unit wide and      注意：图形库中的线条为 1 个像素单位宽，长度总是比您预期的长 1 个像素。
 * have a length that is always one pixel longer than you might         例如函数调用
 * expect.  For example, the function call
 *
 *     DrawLine(2 / GetXResolution(), 0);                                   DrawLine(2 / GetXResolution(), 0);    
 *
 * draws a line from the current point to the point two pixels          从当前点画一条线到右边两个像素的点，这会产生一条三个像素的线。
 * further right, which results in a line of three pixels.
 */
 
double GetXResolution(void);
double GetYResolution(void);
 
/*pixels to inches*/
double ScaleXInches(int x);
double ScaleYInches(int y);

#endif
