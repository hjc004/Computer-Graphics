//样本程序My_first_program.cpp
#include "stdafx.h"
#include <glut.h>
void display(void)  //绘制函数
{
	//glClearColor(0.0f, 1.0f, 0.0f, 0.0f);  //设置清屏颜色
	//glClear(GL_COLOR_BUFFER_BIT);   //刷新颜色缓冲区；
	
	//渐变色背景
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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
	glEnd();

	//画房子
	 //主体矩形
	glColor3f(0.3, 0.71, 0.85);
	glRectf(-0.5, -0.6, 0.5, 0.1);
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
	 //门把手
	glPointSize(5.0); //点的大小设置
	glBegin(GL_POINTS);
	glColor3f(0, 0, 0);
	glVertex2f(0.15, -0.35);
	glEnd();


	glFlush();   //用于刷新命令队列和缓冲区，使所有尚未被执行的OpenGL命令得到执行；
}

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine,int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	char *argv[] = { "hello ", " " };
	int argc = 2; // must/should match the number of strings in argv

	glutInit(&argc, argv);    //初始化GLUT库；
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   //设置显示模式；（缓冲，颜色类型）
	glutInitWindowSize(500, 500); //绘图窗口大小
	glutInitWindowPosition(1024 / 2 - 250, 768 / 2 - 250); //窗口左上角在屏幕的位置
	glutCreateWindow("我的房子");  //创建窗口，标题为“ ”；
	glutDisplayFunc(display);  //用于绘制当前窗口；
	glutMainLoop();   //表示开始运行程序，用于程序的结尾；
	return 0;
}