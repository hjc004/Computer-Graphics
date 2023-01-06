#include "stdafx.h"
#include <glut.h>
#include <math.h>

#include "math.h"
#include "time.h"
#define PI 3.1415926
SYSTEMTIME timeNow;
float hh, mm, ss;
float xs, ys, xm, ym, xh, yh, xc, yc;


int n = 6, R = 10;  //����α��������Բ�뾶

float theta = 0.0;  //��ת��ʼ�Ƕ�ֵ
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

	glutInit(&argc, argv);  //��ʼ��GLUT�⣻
	glutInitWindowSize(700, 700);  //������ʾ���ڴ�С
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  //������ʾģʽ����ע��˫���壩
	glutCreateWindow("A Rotating Square"); // ������ʾ����
	init();
	glutDisplayFunc(Display);  //ע����ʾ�ص�����
	glutReshapeFunc(Reshape);  //ע�ᴰ�ڸı�ص�����
							   // glutIdleFunc(myidle);    //ע�����ûص�����
	glutTimerFunc(0, mytime, 10); //1000��������ʱ�亯�� mytime
	glutMainLoop();  //�����¼�����ѭ��

	return 0;
}

void init()
{
	GetLocalTime(&timeNow);    //��ȡϵͳʱ��
	hh = timeNow.wHour;    //��ȡСʱʱ��
	mm = timeNow.wMinute;   //��ȡ����ʱ��
	ss = timeNow.wSecond;      //��ȡ��ʱ��
}


void Display(void)
{
	//xc,ycΪʱ�����ĵ�����
	//xs,ys, Ϊ������ֹ������ 
	//xs,ys, Ϊ������ֹ������
	xs = xc + R*cos(PI / 2.0 - ss / 60 * 2 * PI);
	ys = yc + R*sin(PI / 2.0 - ss / 60 * 2 * PI);
	xm = xc + R*cos(PI / 2.0 - (mm + ss / 60.0) / 60.0*2.0*PI);
	ym = yc + R*sin(PI / 2.0 - (mm + ss / 60.0) / 60.0*2.0*PI);
	xh = xc + (R - 5)*cos(PI / 2.0 - (hh + (mm + ss / 60.0) / 60.0) / 12.0*2.0*PI);
	yh = yc + (R - 5)*sin(PI / 2.0 - (hh + (mm + ss / 60.0) / 60.0) / 12.0*2.0*PI);

	glClear(GL_COLOR_BUFFER_BIT);
	//glColor3f(1.0, 0, 0); //���ú�ɫ��ͼ��ɫ
	//glBegin(GL_POLYGON);  //��ʼ����������
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


	glutSwapBuffers();   //˫�����ˢ��ģʽ��
}

void mytime(int t)
{
	theta += 0.1;
	if (theta >= 2 * PI) theta -= 2 * PI;
	glutPostRedisplay();  //�ػ����൱�����µ���Display(),�ı��ı������Դ������ƺ���
	glutTimerFunc(100, mytime, 10); //1000��������ʱ�亯�� mytime

	GetLocalTime(&timeNow);    //��ȡϵͳʱ��
	hh = timeNow.wHour;    //��ȡСʱʱ��
	mm = timeNow.wMinute;   //��ȡ����ʱ��
	ss = timeNow.wSecond;      //��ȡ��ʱ��
}

void Reshape(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);  //ͶӰ����ģʽ
	glLoadIdentity();  //�����ջ���
	gluOrtho2D(-1.5*R*w / h, 1.5*R*w / h, -1.5*R, 1.5*R);  //���òü����ڴ�С
	glViewport(0, 0, w, h); //����������С
	glMatrixMode(GL_MODELVIEW);  //ģ�;���ģʽ 
	glLoadIdentity();  //�����ջ���
}
