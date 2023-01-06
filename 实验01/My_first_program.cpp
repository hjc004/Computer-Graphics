//样本程序My_first_program.cpp
#include "stdafx.h"
#include <glut.h>
void display(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  //设置清屏颜色
	glClear(GL_COLOR_BUFFER_BIT);   //刷新颜色缓冲区；

	glFlush();   //用于刷新命令队列和缓冲区，使所有尚未被执行的OpenGL命令得到执行；
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	char *argv[] = { "hello ", " " };
	int argc = 2; // must/should match the number of strings in argv

	glutInit(&argc, argv);    //初始化GLUT库；
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   //设置显示模式；（缓冲，颜色类型）
	glutInitWindowSize(500, 500); //绘图窗口大小
	glutInitWindowPosition(1024 / 2 - 250, 768 / 2 - 250); //窗口左上角在屏幕的位置
	glutCreateWindow("hello");  //创建窗口，标题为“hello”；
	glutDisplayFunc(display);  //用于绘制当前窗口；
	glutMainLoop();   //表示开始运行程序，用于程序的结尾；
	return 0;
}