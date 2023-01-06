#include "stdafx.h"
#include <glut.h>

int angle = 0;
int flag = 1;
float tz = 0;

void reshape(int w, int h);
void init();
void display();
void mytime(int value);


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

							  //设置深度检测下的显示模式；（缓冲，颜色类型，深度值）
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 500);
	glutInitWindowPosition(1024 / 2 - 250, 768 / 2 - 250);
	glutCreateWindow("简单机器人");  //创建窗口，标题为“…”；
	glutReshapeFunc(reshape);
	init();
	glutDisplayFunc(display);  //用于绘制当前窗口；
	glutTimerFunc(100, mytime, 10);
	glutMainLoop();   //表示开始运行程序，用于程序的结尾；

	return 0;
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-10, 10, -10 * h / w, 10 * h / w, 1, 200);    //定义三维观察体
	gluPerspective(70, w / h, 1, 200);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void init()
{
	//反走样
	/*glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);*/

	glLineWidth(3);
	glEnable(GL_DEPTH_TEST);  //启用深度检测

}

void mytime(int value)
{

	//your code here;
	tz += 0.2;
	if (tz >= 10)  tz = 0;

	if ((angle >= 32) || (angle <= -32)) flag = -flag;

	if (flag == 1)
		angle += 5;
	else
		angle -= 5;

	glutPostRedisplay();

	glutTimerFunc(100, mytime, 10);
}

void display()
{

	//glClear(GL_COLOR_BUFFER_BIT);  //2D清屏
	
	//启用深度检测下的3D清屏模式
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); 

	glMatrixMode(GL_MODELVIEW);  //矩阵模式设置
	glLoadIdentity();   //清空矩阵堆栈
	gluLookAt(5, 5, 10, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);  //设置视点     


	glPushMatrix();
	glColor3f(0.87, 0.23, 0.07);
	glTranslatef(0, -6, 0);
	glScalef(5, 0.5, 5);
	glutSolidCube(1);    //绘制地面01红
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.94, 0.44, 0.003);
	glTranslatef(5, -6, 0);
	glScalef(5, 0.5, 5);
	glutSolidCube(1);    //绘制地面02黄
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.94, 0.44, 0.003);
	glTranslatef(-5, -6, 0);
	glScalef(5, 0.5, 5);
	glutSolidCube(1);    //绘制地面03黄
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.87, 0.23, 0.07);
	glTranslatef(-5, -6, -5);
	glScalef(5, 0.5, 5);
	glutSolidCube(1);    //绘制地面04红
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.94, 0.44, 0.003);
	glTranslatef(0, -6, -5);
	glScalef(5, 0.5, 5);
	glutSolidCube(1);    //绘制地面05黄
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.87, 0.23, 0.07);
	glTranslatef(5, -6, -5);
	glScalef(5, 0.5, 5);
	glutSolidCube(1);    //绘制地面06红
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.87, 0.23, 0.07);
	glTranslatef(-5, -6, 5);
	glScalef(5, 0.5, 5);
	glutSolidCube(1);    //绘制地面07红
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.94, 0.44, 0.003);
	glTranslatef(0, -6, 5);
	glScalef(5, 0.5, 5);
	glutSolidCube(1);    //绘制地面08黄
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.87, 0.23, 0.07);
	glTranslatef(5, -6, 5);
	glScalef(5, 0.5, 5);
	glutSolidCube(1);    //绘制地面09红
	glPopMatrix();


	glTranslatef(0, 0, tz);   //机器人整体平移

	glPushMatrix();   //Push/Pop复合整体

	//绘制立方体身
	glPushMatrix();
	glColor3f(0.23, 0.79, 0.85);
	glScalef(4, 4, 0.5);
	glutSolidCube(1);                  
	glPopMatrix();


	//绘制立方体帽檐
	glPushMatrix();
	glColor3f(0.79, 0.25, 0.99);
	glTranslatef(0, 3, 0.5);
	glScalef(1.2, 0.2, 1.2);
	glutSolidCube(1);
	glPopMatrix();
	//绘制立方体帽体
	glPushMatrix();
	glColor3f(0.79, 0.25, 0.99);
	glTranslatef(0, 3.2, 0);
	glScalef(1, 0.7, 1);
	glutSolidCube(1);
	glPopMatrix();

	//绘制立方体头
	glPushMatrix();
	glColor3f(0.99, 0.72, 0.086);
	glTranslatef(0, 2.5, 0);
	glScalef(1, 1, 0.5);
	glutSolidCube(1);                  
	glPopMatrix();


	//绘制立方体左手臂
	glPushMatrix();
	glColor3f(1, 0.5, 0.2);
	glTranslatef(0, 2, 0);   //旋转轴
	glRotatef(angle, 1, 0, 0);   //旋转角度
	glTranslatef(0, -2, 0);

	glTranslatef(-2.5, 0.5, 0);
	glScalef(1, 3, 0.5);
	glutSolidCube(1);  
	glPopMatrix();

	//绘制立方体左手
	glPushMatrix();
	glColor3f(1, 0.5, 0.2);
	glTranslatef(0, 2, 0);   //旋转轴
	glRotatef(angle, 1, 0, 0);   //旋转角度
	glTranslatef(0, -2, 0);

	glTranslatef(-2.5, -1, 0);
	glScalef(1, 0.9, 1);
	glutSolidCube(1);
	glPopMatrix();


	//绘制立方体右手臂
	glPushMatrix();
	glColor3f(1, 0.5, 0.2);
	glTranslatef(0, 2, 0);
	glRotatef(-angle, 1, 0, 0);
	glTranslatef(0, -2, 0);

	glTranslatef(2.5, 0.5, 0);
	glScalef(1, 3, 0.5);
	glutSolidCube(1);              
	glPopMatrix();

	//绘制立方体右手
	glPushMatrix();
	glColor3f(1, 0.5, 0.2);
	glTranslatef(0, 2, 0);   //旋转轴
	glRotatef(-angle, 1, 0, 0);   //旋转角度
	glTranslatef(0, -2, 0);

	glTranslatef(2.5, -1, 0);
	glScalef(1, 0.9, 1);
	glutSolidCube(1);
	glPopMatrix();


	//绘制立方体左腿      
	glPushMatrix();
	glColor3f(0.5, 0.5, 1);
	glTranslatef(0, -2, 0);  //旋转轴
	glRotatef(-angle, 1, 0, 0);
	glTranslatef(0, 2, 0);

	glTranslatef(-1, -3.5, 0);
	glScalef(1, 3, 0.5);
	glutSolidCube(1);            
	glPopMatrix();

	//绘制立方体左脚
	glPushMatrix();
	glColor3f(0.5, 0.5, 1);
	glTranslatef(0, -2, 0);  //旋转轴
	glRotatef(-angle, 1, 0, 0);
	glTranslatef(0, 2, 0);

	glTranslatef(-1, -4.9, 0);
	glScalef(1, 0.4, 1);
	glutSolidCube(1);
	glPopMatrix();


	//绘制立方体右腿      
	glPushMatrix();
	glColor3f(0.5, 0.5, 1);
	//your code here;
	glTranslatef(0, -2, 0);
	glRotatef(angle, 1, 0, 0);
	glTranslatef(0, 2, 0);

	glTranslatef(1, -3.5, 0);
	glScalef(1, 3, 0.5);
	glutSolidCube(1);            
	glPopMatrix();

	//绘制立方体右脚
	glPushMatrix();
	glColor3f(0.5, 0.5, 1);
	//your code here;
	glTranslatef(0, -2, 0);
	glRotatef(angle, 1, 0, 0);
	glTranslatef(0, 2, 0);

	glTranslatef(1, -4.9, 0);
	glScalef(1, 0.35, 1);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();  //Push/Pop复合整体


	glutSwapBuffers();  //双缓冲下的刷新方法
}
