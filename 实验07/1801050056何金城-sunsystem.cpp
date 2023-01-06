#include "stdafx.h"
#include <glut.h>
#include <math.h>

int rs = 80, re = 20, rm = 5, rsel = 1.5;

int dse = 180; //日地距离rs + re + 6rm
int dsm = 220; //日月距离des + re + rm + 2rm
int dssel = 232.5; //日卫距离dsm + rm + 2rsel
float as = 0, ae = 0, am = 0, asel = 0;//自转角度
float ase = 0, aem = 0, asm1 = 0, assel = 0;//公转角度

void sun(void);
void earth(void);
void moon(void);
void setellite(void);

void Display(void);
void Reshape(GLsizei w, GLsizei h);
void mytime(int value);
void myinit(void);

void selectFont(int size, int charset, const char* face); //选择字体
void drawCNString(const char* str); //生成中文字体函数

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	char *argv[] = { "hello ", " " };
	int argc = 2; // must/should match the number of strings in argv
	glutInit(&argc, argv);  //初始化GLUT库；
	glutInitWindowSize(700, 700);  //设置显示窗口大小
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  //设置显示模式；（注意双缓冲）
	glutCreateWindow("A Rotating Sun System"); // 创建显示窗口
	glutDisplayFunc(Display);  //注册显示回调函数
	glutReshapeFunc(Reshape);  //注册窗口改变回调函数
	myinit();
	glutTimerFunc(200, mytime, 10);
	glutMainLoop();  //进入事件处理循环
	return 0;
}

void myinit()
{
	glLineWidth(4);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW); //设置矩阵模式为模型变换模式，表示在世界坐标系下
	glLoadIdentity();   //将当前矩阵设置为单位矩阵

	sun();
	earth();
	moon();
	setellite();
	
	glutSwapBuffers();   //双缓冲的刷新模式；
}

void sun()
{
	glPushMatrix();
	glColor3f(1, 0, 0);
	glRotatef(as, 0, 0, 1);
	glutWireSphere(rs, 40, 40);

	//标记点---------
	glPointSize(5);
	glColor3f(1, 1, 1);
	glBegin(GL_POINTS);
	glVertex2f(rs, 0);
	glEnd();

	//字体
	selectFont(20, GB2312_CHARSET, "楷体_GB2312");
	glRasterPos2f(0, 0);
	drawCNString("太阳");

	glPopMatrix();
}

void earth()
{
	glPushMatrix();
	//公转-----------
	glRotatef(ase, 0, 0, 1);

	//自转-----------
	glTranslatef(dse, 0, 0);
	glRotatef(ae, 0, 0, 1);
	glTranslatef(-dse, 0, 0);

	glColor3f(0, 0, 1);
	glTranslatef(dse, 0, 0);
	glutWireSphere(re, 40, 40);

	//标记点---------
	glPointSize(5);
	glColor3f(1, 1, 1);
	glBegin(GL_POINTS);
	glVertex2f(re, 0);
	glEnd();

	//字体
	selectFont(20, GB2312_CHARSET, "楷体_GB2312");
	glRasterPos2f(0, 0);
	drawCNString("地球");

	glPopMatrix();
}

void moon()
{
	glPushMatrix();
	//公转-----------
	glRotatef(asm1, 0, 0, 1);

	glTranslatef(dse, 0, 0);
	glRotatef(aem, 0, 0, 1);
	glTranslatef(-dse, 0, 0);

	//自转-----------
	glTranslatef(dsm, 0, 0);
	glRotatef(am, 0, 0, 1);
	glTranslatef(-dsm, 0, 0);

	glColor3f(1, 1, 0);
	glTranslatef(dsm, 0, 0);
	glutWireSphere(rm, 30, 30);

	//标记点---------
	glPointSize(5);
	glColor3f(1, 1, 1);
	glBegin(GL_POINTS);
	glVertex2f(rm, 0);
	glEnd();

	//字体
	selectFont(20, GB2312_CHARSET, "楷体_GB2312");
	glRasterPos2f(0, 0);
	drawCNString("月球");

	glPopMatrix();
}

//卫星---------------------------
void setellite() {
	glPushMatrix();

	//公转-----------
	glRotatef(assel, 0, 0, 1);

	glTranslatef(dse, 0, 0);
	glRotatef(aem, 0, 0, 1);
	glTranslatef(-dse, 0, 0);

	glTranslatef(dsm, 0, 0);
	glRotatef(asel, 0, 0, 1);
	glTranslatef(-dsm, 0, 0);

	//自转-----------
	glTranslatef(dssel, 0, 0);
	glRotatef(asel, 0, 0, 1);
	glTranslatef(-dssel, 0, 0);

	glColor3f(0.5, 0.5, 0.5);
	glTranslatef(dssel, 0, 0);
	glutWireSphere(rsel, 40, 40);

	//标记点---------
	glColor3f(1, 1, 1);
	glBegin(GL_POINTS);
	glVertex2f(rsel, 0);
	glEnd();

	//字体
	glColor3f(1, 0, 1);
	selectFont(20, GB2312_CHARSET, "楷体_GB2312");
	glRasterPos2f(0, 0);
	drawCNString("卫星");

	glPopMatrix();

}

//时间函数
void mytime(int value)
{
	as += 0.3;
	ae += 0.3;
	am += 0.3;
	asel += 0.3;

	ase += 0.3;
	aem += 0.3;
	asm1 += 0.3;
	assel += 0.3;

	glutPostRedisplay();  //重画，相当于10重新调用Display(),改编后的变量得以传给绘制函数

	glutTimerFunc(30, mytime, 10);

}

//窗口视区设置-------------------
void Reshape(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);  //投影矩阵模式
	glLoadIdentity();  //矩阵堆栈清空
	glViewport(0, 0, w, h); //设置视区大小

	gluOrtho2D(-(dsm + 4 * rm), dsm + 4 * rm, -(dsm + 4 * rm), dsm + 4 * rm);  //设置裁剪窗口大小  
	glMatrixMode(GL_MODELVIEW);  //模型矩阵模式

}

/************************************************************************/
/* 选择字体函数                                                                     */
/************************************************************************/
void selectFont(int size, int charset, const char* face)
{
	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
		charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);
}

/************************************************************************/
/* 生成中文字体函数                                                                     */
/************************************************************************/
void drawCNString(const char* str)
{
	int len, i;
	wchar_t* wstring;
	HDC hDC = wglGetCurrentDC();
	GLuint list = glGenLists(1);

	// 计算字符的个数
	// 如果是双字节字符的（比如中文字符），两个字节才算一个字符
	// 否则一个字节算一个字符
	len = 0;
	for (i = 0; str[i] != '\0'; ++i)
	{
		if (IsDBCSLeadByte(str[i]))
			++i;
		++len;
	}

	// 将混合字符转化为宽字符
	wstring = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len);
	wstring[len] = L'\0';

	// 逐个输出字符
	for (i = 0; i<len; ++i)
	{
		wglUseFontBitmapsW(hDC, wstring[i], 1, list);
		glCallList(list);
	}

	// 回收所有临时资源
	free(wstring);
	glDeleteLists(list, 1);
}

