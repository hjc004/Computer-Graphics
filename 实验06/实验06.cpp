#include "stdafx.h"
#include <glut.h>
#include <math.h>
#define PI 3.14159  //设置圆周率
int n = 6, R = 10;  //多边形变数，外接圆半径
float cx = 0, cy = 0;
float sx = 1, sy = 1;
int flag = 1;

float theta = 0.0;  //旋转初始角度值
void Display(void);
void Reshape(GLsizei w, GLsizei h);
void Myidle();

void Display(void)  //绘制函数
{
	//glClearColor(0.0f, 1.0f, 0.0f, 0.0f);  //设置清屏颜色
	//glClear(GL_COLOR_BUFFER_BIT);   //刷新颜色缓冲区；

	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //设置矩阵模式为模型变换模式，表示在世界坐标系下
	glLoadIdentity();   //将当前矩阵设置为单位矩阵

	glRotatef(theta, 0, 0, 1); //绕原点旋转ALPHA角度
	glScalef(sx, sy, 1);  //比例缩放
	glTranslatef(-cx, -cy, 0);  //平移回原点

	//渐变色背景
	/*glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glPointSize(500.0);
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(-1, -1);
	glColor3f(1.0, 0.0, 1.0);
	glVertex2f(-1, 1);
	glColor3f(0.0, 1.0, 1.0);
	glVertex2f(1, 1);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(1, -1);
	glEnd();*/

	//画房子
	//主体矩形
	glColor3f(0.3, 0.71, 0.85);
	glRectf(-0.5, -0.6, 0.5, 0.1);
	glEnd();
	//屋顶
	glColor3f(0.85, 0.27, 0.87);
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.6, 0.1); //顶点1
	glVertex2f(0, 0.55); //顶点2
	glVertex2f(0.6, 0.1); //顶点3
	glEnd();
	//窗口
	glColor3f(0.45, 0.95, 0.65);
	glRectf(-0.4, -0.3, -0.1, 0);
	glEnd();
	//窗口边框
	glColor3f(0.63, 0.35, 0.02);
	glBegin(GL_LINES);
	glVertex2f(-0.4, -0.15);  //端点1
	glVertex2f(-0.1, -0.15); //端点2
	glEnd();

	glColor3f(0.63, 0.35, 0.02);
	glBegin(GL_LINES);
	glVertex2f(-0.25, 0);  //端点1
	glVertex2f(-0.25, -0.3); //端点2
	glEnd();
	//门
	glColor3f(0.47, 0.5, 0.62);
	glRectf(0.1, -0.6, 0.4, -0.1);
	glEnd();
	//门把手
	/*glPointSize(5.0); //点的大小设置
	glBegin(GL_POINTS);
	glColor3f(0, 0, 0);
	glVertex2f(0.15, -0.35);
	glEnd();*/

	//glFlush();   //用于刷新命令队列和缓冲区，使所有尚未被执行的OpenGL命令得到执行；
	glutSwapBuffers();   //双缓冲的刷新模式；
}

void Myidle()
{

	theta += 0.5;                              //调节旋转速度
	if (theta >= 360) theta -= 360;

	if (flag == 1)
	{
		//比例因子放大一个增量
		sx = sx*1.01;
		sy = sy*1.01;
	}
	else
	{
		sx = sx*0.99;
		sy = sy*0.99;
	}

	if ((sx >= 100) || (sy >= 100))
		flag = -1;
	if ((sx <= 0.1) || (sy <= 0.1))
		flag = 1;

	glutPostRedisplay();  //重画，相当于重新调用Display(),改编后的变量得以传给绘制函数
}

//视区设置----------------------
void Reshape(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);  //投影矩阵模式
	glLoadIdentity();  //矩阵堆栈清空
	gluOrtho2D(-1.5*R*w / h, 1.5*R*w / h, -1.5*R, 1.5*R);  //设置裁剪窗口大小
	glViewport(0, 0, w, h); //设置视区大小
	glMatrixMode(GL_MODELVIEW);  //模型矩阵模式 
}

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	char *argv[] = { "hello ", " " };
	int argc = 2; // must/should match the number of strings in argv

	glutInit(&argc, argv);    //初始化GLUT库；
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);   //设置显示模式；（缓冲，颜色类型）
	glutInitWindowSize(700, 700); //绘图窗口大小
	glutInitWindowPosition(1024 / 2 - 250, 768 / 2 - 250); //窗口左上角在屏幕的位置
	glutCreateWindow("爱的魔力转圈圈~~");  //创建窗口，标题为“ ”；
	glutDisplayFunc(Display);  //注册显示回调函数
	glutReshapeFunc(Reshape);  //注册窗口改变回调函数
	glutIdleFunc(Myidle);    //注册闲置回调函数
	glutMainLoop();  //进入事件处理循环
	return 0;
}