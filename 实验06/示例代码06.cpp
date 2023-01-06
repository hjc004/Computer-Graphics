//样本程序： 旋转的六边形
#include "stdafx.h"
#include <glut.h>
#include <math.h>
#define PI 3.14159  //设置圆周率
int n = 6, R = 10;  //多边形变数，外接圆半径
float cx = 0, cy = 0;
float sx = 1, sy = 1;
int flag = 1;

float theta = 0.0;  //旋转初始角度值
void Keyboard(unsigned char key, int x, int y);
void Display(void);
void Reshape(int w, int h);
void myidle();

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
	glutDisplayFunc(Display);  //注册显示回调函数
	glutReshapeFunc(Reshape);  //注册窗口改变回调函数
	glutIdleFunc(myidle);    //注册闲置回调函数
	glutMainLoop();  //进入事件处理循环

	return 0;
}


void Display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);


	glMatrixMode(GL_MODELVIEW); //设置矩阵模式为模型变换模式，表示在世界坐标系下
	glLoadIdentity();   //将当前矩阵设置为单位矩阵
	glTranslatef(cx, cy, 0);   //平移回去

	glRotatef(theta, 0, 0, 1); //绕原点旋转ALPHA角度
	glScalef(sx, sy, 1);  //比例缩放
	glTranslatef(-cx, -cy, 0);  //平移回原点

	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(0, R);
	glEnd();

	glColor3f(1, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(0, R / 2.0);
	glVertex2f(0, R);
	glVertex2f(R / 2.0, R);
	glEnd();

	glutSwapBuffers();   //双缓冲的刷新模式；

}

void myidle()
{

	theta += 0.2;
	if (theta >= 360) theta -= 360;

	if ( flag == 1)
	{
		//比例因子放大一个增量
		sx = sx*1.0001;
		sy = sy*1.0001;
	}
	else
	{
		sx = sx*0.999;
		sy = sy*0.999;
	}

	if ((sx >= 2) || (sy >= 2))
		flag = -1;
	if ((sx <= 0.1) || (sy <= 0.1))
		flag = 1;

	glutPostRedisplay();  //重画，相当于重新调用Display(),改编后的变量得以传给绘制函数
}

void Reshape(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);  //投影矩阵模式
	glLoadIdentity();  //矩阵堆栈清空
	gluOrtho2D(-1.5*R*w / h, 1.5*R*w / h, -1.5*R, 1.5*R);  //设置裁剪窗口大小
	glViewport(0, 0, w, h); //设置视区大小
	glMatrixMode(GL_MODELVIEW);  //模型矩阵模式 
}
