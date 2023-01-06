#include "stdafx.h"
#include <glut.h>
#include <math.h>

#define N 1000       //maximum line numbers
#define PI 3.1415926
#define MAX_CHAR 128

int ww, hh;     // for display window width and height
int line[N][2], k = 0;  //for line's endpoint coordinates and line number
int sline[N][4], k2 = 0;
int m = 1;
float R = 0;
const int n = 300;
int rectf[N][4], k3 = 0;
int circle[N][4], k4 = 0;//rectf
int flag = 1;

void Myinit(void);
void Reshape(int w, int h);
void myMouse(int button, int state, int x, int y);
void myMotion(int x, int y);
void Display(void);
void drawcaotu();
void drawrectf();
void drawlines();
void drawcircle();
void mykeyboard(unsigned char key, int x, int y);
void drawString(const char* str) {
	static int isFirstCall = 1;
	static GLuint lists;

	if (isFirstCall) { 
		isFirstCall = 0;

		lists = glGenLists(MAX_CHAR);

		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	for (; *str != '\0'; ++str)
		glCallList(lists + *str);
}

void selectFont(int size, int charset, const char* face); //选择字体
void drawCNString(const char* str); //生成中文字体函数

//主函数
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
	glutInitWindowSize(800, 600);  //设置显示窗口大小
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  //设置显示模式；（注意双缓冲）
	glutCreateWindow("鼠标交互绘制图形"); // 创建显示窗口
	Myinit();
	glutDisplayFunc(Display);  //注册显示回调函数
	glutMouseFunc(myMouse);    //注册鼠标按钮回调函数
	glutMotionFunc(myMotion);  //注册鼠标移动回调函数
	glutKeyboardFunc(mykeyboard);
	glutReshapeFunc(Reshape);  //注册窗口改变回调函数
	glutMainLoop();  //进入事件处理循环
	return 0;
}

//初始化
void Myinit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glLineWidth(3.0);
}

//绘制函数
void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);   //刷新颜色缓冲区；
	selectFont(12, GB2312_CHARSET, "黑体"); //设置字体
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(0, 560);
	drawCNString("数字1自由画笔");
	glRasterPos2f(0, 540);
	drawCNString("数字2直线画笔");
	glRasterPos2f(0, 520);
	drawCNString("数字3矩形画笔");
	glRasterPos2f(0, 500);
	drawCNString("数字4圆形画笔");
	if (m == 1) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		if (flag == 1) {
			drawcaotu();
		}
		if (flag == 2) {
			drawlines();
		}
		if (flag == 3) {
			drawrectf();
		}
		if (flag == 4) {
			drawcircle();
		}
	}
	if (m == 2) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		if (flag == 1) {
			drawcaotu();
		}
		if (flag == 2) {
			drawlines();
		}
		if (flag == 3) {
			drawrectf();
		}
		if (flag == 4) {
			drawcircle();
		}
	}
	glutSwapBuffers();
}

void Reshape(int w, int h)  //窗口改变时自动获取显示窗口的宽w和高h
{
	glMatrixMode(GL_PROJECTION);  //投影矩阵模式
	glLoadIdentity();     //矩阵堆栈清空
	glViewport(0, 0, w, h);  //设置视区大小
	gluOrtho2D(0, w, 0, h);   //设置裁剪窗口大小
	ww = w;
	hh = h;
}

void myMouse(int button, int state, int x, int y)//
{
	if (flag == 1) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			line[k][0] = x;   //线段起点x坐标
			line[k][1] = hh - y;  //线段终点y坐标
			k++;
		}
		if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		{
			line[k][0] = x;   //线段起点x坐标
			line[k][1] = hh - y;   //线段终点y坐标
		}
	}
	if (flag == 2) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			sline[k2][0] = x;
			sline[k2][1] = hh - y;
		}
		if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		{
			sline[k2][2] = x;
			sline[k2][3] = hh - y;
			k2++;
		}
	}
	if (flag == 3) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			rectf[k3][0] = x;
			rectf[k3][1] = hh - y;
		}
		if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		{
			rectf[k3][2] = x;
			rectf[k3][3] = hh - y;
			k3++;
		}
	}
	if (flag == 4) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			circle[k4][0] = x;
			circle[k4][1] = hh - y;
		}
		if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		{
			circle[k4][2] = x;
			circle[k4][3] = hh - y;
			k4++;
		}
	}

}


void myMotion(int x, int y)
{
	if (flag == 1) {
		line[k][0] = x;   //动态终点的x坐标
		line[k][1] = hh - y;  //动态终点的y坐标
		k++;
	}
	if (flag == 2) {
		sline[k2][2] = x;
		sline[k2][3] = hh - y;
	}
	if (flag == 3) {
		rectf[k3][2] = x;
		rectf[k3][3] = hh - y;
	}
	if (flag == 4) {
		circle[k4][2] = x;
		circle[k4][3] = hh - y;
	}

	glutPostRedisplay();
}
void drawcaotu() {
	glColor3f(1, 1, 1);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i<k; i++) {
		glVertex2f(line[i][0], line[i][1]);
	}
	glEnd();
}
void drawlines() {
	for (int i = 0; i <= k2; i++) {
		glColor3f(1, 1, 1);
		glBegin(GL_LINE_STRIP);
		glVertex2f(sline[i][0], sline[i][1]);
		glVertex2f(sline[i][2], sline[i][3]);
		glEnd();
	}
}
void drawrectf()
{
	glColor3f(1, 1, 1);
	for (int i = 0; i <= k3; i++)
	{
		glRectf(rectf[i][0], rectf[i][1], rectf[i][2], rectf[i][3]);
	}
}
void drawcircle() {
	for (int i = 0; i <= k4; i++) {
		R = (circle[i][2] - circle[i][0])*(circle[i][2] - circle[i][0]) + (circle[i][3] - circle[i][1])*(circle[i][3] - circle[i][1]);
		glBegin(GL_POLYGON);
		for (int j = 0; j<n; ++j) {
			glVertex2f(circle[i][0] + sqrt(R) * cos(2 * PI*j / n), circle[i][1] + sqrt(R) * sin(2 * PI*j / n));
		}
		glEnd();
	}
}
void mykeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		flag = 1;
		break;
	case '2':
		flag = 2;
		break;
	case '3':
		flag = 3;
		break;
	case '4':
		flag = 4;
		break;
	case'5':
		m = 1;
		break;
	case'6':
		m = 2;
		break;
	}
	glutPostRedisplay();
}

void selectFont(int size, int charset, const char* face)
{
	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
		charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);
}

//汉字设置
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