#include "stdafx.h"
#include <glut.h>
#include <math.h>

#include "math.h"
#include "time.h"
#define PI 3.1415926
SYSTEMTIME timeNow;
float hh, mm, ss;
float xs, ys, xm, ym, xh, yh, xc, yc;


int n = 6, R = 10;  //多边形变数，外接圆半径

float theta = 0.0;  //旋转初始角度值
void Keyboard(unsigned char key, int x, int y);
void init();
void Display(void);
void Reshape(int w, int h);
//void myidle();
void mytime(int t);

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
	glutCreateWindow("A Rotating Square"); // 创建显示窗口
	init();
	glutDisplayFunc(Display);  //注册显示回调函数
	glutReshapeFunc(Reshape);  //注册窗口改变回调函数
							   // glutIdleFunc(myidle);    //注册闲置回调函数
	glutTimerFunc(0, mytime, 10); //1000毫秒后调用时间函数 mytime
	glutMainLoop();  //进入事件处理循环

	return 0;
}

void init()
{
	GetLocalTime(&timeNow);    //获取系统时间
	hh = timeNow.wHour;    //获取小时时间
	mm = timeNow.wMinute;   //获取分钟时间
	ss = timeNow.wSecond;      //获取秒时间
}


void Display(void)
{
	//xc,yc为时针中心点坐标
	//xs,ys, 为秒针终止点坐标 
	//xs,ys, 为秒针终止点坐标
	xs = xc + R*cos(PI / 2.0 - ss / 60 * 2 * PI);
	ys = yc + R*sin(PI / 2.0 - ss / 60 * 2 * PI);
	xm = xc + R*cos(PI / 2.0 - (mm + ss / 60.0) / 60.0*2.0*PI);
	ym = yc + R*sin(PI / 2.0 - (mm + ss / 60.0) / 60.0*2.0*PI);
	xh = xc + (R - 5)*cos(PI / 2.0 - (hh + (mm + ss / 60.0) / 60.0) / 12.0*2.0*PI);
	yh = yc + (R - 5)*sin(PI / 2.0 - (hh + (mm + ss / 60.0) / 60.0) / 12.0*2.0*PI);

	glClear(GL_COLOR_BUFFER_BIT);
	//glColor3f(1.0, 0, 0); //设置红色绘图颜色
	//glBegin(GL_POLYGON);  //开始绘制六边形
	//for (int i = 0; i<n; i++)
	//	glVertex2f(R*cos(theta + i * 2 * PI / n), R*sin(theta + i * 2 * PI / n));
	//glEnd();

	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(xc, yc);
	glVertex2f(xs, ys);
	glEnd();

	glColor3f(1, 1, 0);
	glBegin(GL_LINES);
	glVertex2f(xc, yc);
	glVertex2f(xm, ym);
	glEnd();

	glColor3f(0, 1, 1);
	glBegin(GL_LINES);
	glVertex2f(xc, yc);
	glVertex2f(xh, yh);
	glEnd();


	glutSwapBuffers();   //双缓冲的刷新模式；
}

void mytime(int t)
{
	theta += 0.1;
	if (theta >= 2 * PI) theta -= 2 * PI;
	glutPostRedisplay();  //重画，相当于重新调用Display(),改编后的变量得以传给绘制函数
	glutTimerFunc(100, mytime, 10); //1000毫秒后调用时间函数 mytime

	GetLocalTime(&timeNow);    //获取系统时间
	hh = timeNow.wHour;    //获取小时时间
	mm = timeNow.wMinute;   //获取分钟时间
	ss = timeNow.wSecond;      //获取秒时间
}

void Reshape(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);  //投影矩阵模式
	glLoadIdentity();  //矩阵堆栈清空
	gluOrtho2D(-1.5*R*w / h, 1.5*R*w / h, -1.5*R, 1.5*R);  //设置裁剪窗口大小
	glViewport(0, 0, w, h); //设置视区大小
	glMatrixMode(GL_MODELVIEW);  //模型矩阵模式 
	glLoadIdentity();  //矩阵堆栈清空
}
