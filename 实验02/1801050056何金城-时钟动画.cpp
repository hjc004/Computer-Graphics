#include "stdafx.h"
#include <glut.h>
#include <time.h>
#include <Windows.h>
#include <stdio.h>
#include <math.h>
#define PI 3.1415926

float hour;
float minute;
float second;
int week;

float lastSecond;

GLuint textList;

char* weekStr[] = { "星期天", "星期一", "星期二", "星期三", "星期四", "星期五", "星期六"};


void getTime()
{
	time_t now;
	struct tm timenow;

	time(&now);
	localtime_s(&timenow, &now);

	lastSecond = second;

	hour = timenow.tm_hour;
	minute = timenow.tm_min;
	second = timenow.tm_sec;

	week = timenow.tm_wday;
}

void selectFont(int size, const char* face)
{
	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);

	glDeleteLists(textList, 256);

	textList = glGenLists(256);
	wglUseFontBitmaps(wglGetCurrentDC(), 0, 256, textList);
}

void drawString(int x, int y, char* str)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glLoadIdentity();
	glRasterPos2i(x, y);

	int len = 0;
	int i = 0;
	wchar_t* wstr;
	HDC hDC = wglGetCurrentDC();
	GLuint list = glGenLists(1);

	for (i = 0; str[i] != '\0'; ++i)
	{
		if (IsDBCSLeadByte(str[i]))
		{
			++i;
		}
		++len;
	}

	wstr = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, wstr, len);
	wstr[len] = L'\0';

	for (i = 0; i < len; ++i)
	{
		wglUseFontBitmapsW(hDC, wstr[i], 1, list);
		glCallList(list);
	}

	free(wstr);

	glDeleteLists(list, 1);
}

void drawCircle(float x, float y, float r)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_STRIP);

	float step = 0.1f;
	float dx = x;
	float dy = y;

	for (float angle = 0.0f; angle <= 3.14159265f * 2.0f; angle += step)
	{
		dx = x + r * sin(angle);
		dy = y + r * cos(angle);

		glVertex3f(dx, dy, 0);
	}
	dx = x + r * sin(0.0f);
	dy = y + r * cos(0.0f);
	glVertex3f(dx, dy, 0);

	glEnd();
}

void init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glShadeModel(GL_SMOOTH);
	//glEnable(GL_POINT_SMOOTH);
	//glEnable(GL_LINE_SMOOTH);

	glViewport(0, 0, 800, 600);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-400.0f, 400.0f, -300.0f, 300.0f, -1.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	selectFont(24, "楷体");
}

void update()
{
	getTime();

	if (lastSecond != second)
	{
		glutPostRedisplay();
	}
}

void mouseMove(int x, int y)
{
}

void mouseClick(int button, int state, int x, int y)
{
}

void keyDown(unsigned char key, int x, int y)
{
}

void keyUp(unsigned char key, int x, int y)
{
}

void timeTicks(int value)
{
	glutTimerFunc(1000, timeTicks, 1);
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	// 表盘
	glLineWidth(1.0f);
	drawCircle(0.0f, 0.0f, 150.0f);
	drawCircle(0.0f, 0.0f, 155.0f);

	for (float w = 0.0f; w < 360.f; w += 6.0f)
	{
		glLoadIdentity();
		glRotatef(w, 0, 0, -1);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINES);
		glVertex2i(0, 150);
		glVertex2i(0, 145);
		glEnd();
	}

	glLineWidth(3.0f);
	for (float z = 0.0f; z < 360.f; z += 30.0f)
	{
		glLoadIdentity();
		glRotatef(z, 0, 0, -1);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINES);
		glVertex2i(0, 150);
		glVertex2i(0, 140);
		glEnd();
	}

	glLineWidth(1.0f);
	// hour
	glLoadIdentity();
	glRotatef(((float)((int)hour % 12) / 12.0f) * 360.0f + (minute / 60.0f) * 30.0f, 0, 0, -1);
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex2i(0, 0);
	glVertex2i(0, 50);
	glVertex2i(0, 50);
	glVertex2i(-3, 40);
	glVertex2i(0, 50);
	glVertex2i(3, 40);
	glEnd();

	// minute
	glLoadIdentity();
	glRotatef((minute / 60.0f) * 360.0f + (second / 60.0f) * 6.0f, 0, 0, -1);
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2i(0, 0);
	glVertex2i(0, 100);
	glVertex2i(0, 100);
	glVertex2i(-3, 90);
	glVertex2i(0, 100);
	glVertex2i(3, 90);
	glEnd();

	// second
	glLoadIdentity();
	glRotatef((second / 60.0f) * 360.0f, 0, 0, -1);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2i(0, -20);
	glVertex2i(0, 150);
	glVertex2i(0, 150);
	glVertex2i(-3, 140);
	glVertex2i(0, 150);
	glVertex2i(3, 140);
	glEnd();

	// 文字
	char str[100];
	sprintf_s(str, 100, "%02d:%02d:%02d\0", (int)hour, (int)minute, (int)second);
	drawString(-50, -200, str);

	drawString(-40, -230, weekStr[week]);

	glFlush();

	glutSwapBuffers();
}


int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	char *argv[] = { "hello ", " " };
	int argc = 2; // must/should match the number of strings in argv

	glutInit(&argc, argv);  //初始化GLUT库；
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  //设置显示模式；（注意双缓冲）
	glutInitWindowPosition(300, 300);
	glutInitWindowSize(800, 600);  //设置显示窗口大小

	glutCreateWindow("时钟动画"); // 创建显示窗口

	glutDisplayFunc(Display);  //注册显示回调函数
	glutIdleFunc(update);

	glutMotionFunc(mouseMove);
	glutMouseFunc(mouseClick);
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);

	glutTimerFunc(1000, timeTicks, 1); //1000毫秒后调用时间函数 mytime

	init();

	glutMainLoop();  //进入事件处理循环

	return 0;
}
