#include "stdafx.h"
#include <glut.h>

#define N 1000 //数组下限

int ww, hh;     // for display window width and height

int line[N][2];
int k = 0;//计数器

void Myinit(void);
void Reshape(int w, int h);
void Display(void);
void mymouse(int button, int state, int x, int y);
void mymotion(int x, int y);

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
	glutCreateWindow("鼠标画线小程序演示"); // 创建显示窗口
	Myinit();

	glutDisplayFunc(Display);  //注册显示回调函数
	glutReshapeFunc(Reshape);  //注册窗口改变回调函数
	glutMouseFunc(mymouse);// 鼠标按钮响应回调函数
	glutMotionFunc(mymotion);// 鼠标按钮按下时移动响应函数

	glutMainLoop();  //进入事件处理循环
	return 0;
}


void Myinit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glLineWidth(3.0);
}

//渲染绘制子程序--------------------------------------------------------------------------
void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);   //刷新颜色缓冲区；
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i<k; i++)
		glVertex2f(line[i][0], line[i][1]);
	glEnd();
	glutSwapBuffers();  //双缓冲的刷新模式；
}

//-----------------------------------------------
void Reshape(int w, int h)  //窗口改变时自动获取显示窗口的宽w和高h
{
	glMatrixMode(GL_PROJECTION);  //投影矩阵模式
	glLoadIdentity();     //矩阵堆栈清空
	glViewport(0, 0, w, h);  //设置视区大小
	gluOrtho2D(0, w, 0, h);   //设置裁剪窗口大小
	ww = w;
	hh = h;
}

void mymouse(int x, int y, int button, int state)
{
	if (state == GLUT_DOWN &&button == GLUT_LEFT_BUTTON) { //左键按下
		line[k][0] = x;
		line[k][1] = hh - y;
		k++;
	}
	if (state == GLUT_UP &&button == GLUT_LEFT_BUTTON) { //左键松开
		line[k][0] = x;
		line[k][1] = hh - y;

	}

	glutPostRedisplay(); //重画
}

void mymotion(int x, int y) {
	line[k][0] = x;
	line[k][1] = hh - y;
	k++;
	glutPostRedisplay(); //重画
}
