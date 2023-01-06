//�������� ��ת��������
#include "stdafx.h"
#include <glut.h>
#include <math.h>
#define PI 3.14159  //����Բ����
int n = 6, R = 10;  //����α��������Բ�뾶
float cx = 0, cy = 0;
float sx = 1, sy = 1;
int flag = 1;

float theta = 0.0;  //��ת��ʼ�Ƕ�ֵ
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

	glutInit(&argc, argv);  //��ʼ��GLUT�⣻
	glutInitWindowSize(700, 700);  //������ʾ���ڴ�С
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  //������ʾģʽ����ע��˫���壩
	glutCreateWindow("A Rotating Square"); // ������ʾ����
	glutDisplayFunc(Display);  //ע����ʾ�ص�����
	glutReshapeFunc(Reshape);  //ע�ᴰ�ڸı�ص�����
	glutIdleFunc(myidle);    //ע�����ûص�����
	glutMainLoop();  //�����¼�����ѭ��

	return 0;
}


void Display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);


	glMatrixMode(GL_MODELVIEW); //���þ���ģʽΪģ�ͱ任ģʽ����ʾ����������ϵ��
	glLoadIdentity();   //����ǰ��������Ϊ��λ����
	glTranslatef(cx, cy, 0);   //ƽ�ƻ�ȥ

	glRotatef(theta, 0, 0, 1); //��ԭ����תALPHA�Ƕ�
	glScalef(sx, sy, 1);  //��������
	glTranslatef(-cx, -cy, 0);  //ƽ�ƻ�ԭ��

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

	glutSwapBuffers();   //˫�����ˢ��ģʽ��

}

void myidle()
{

	theta += 0.2;
	if (theta >= 360) theta -= 360;

	if ( flag == 1)
	{
		//�������ӷŴ�һ������
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

	glutPostRedisplay();  //�ػ����൱�����µ���Display(),�ı��ı������Դ������ƺ���
}

void Reshape(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);  //ͶӰ����ģʽ
	glLoadIdentity();  //�����ջ���
	gluOrtho2D(-1.5*R*w / h, 1.5*R*w / h, -1.5*R, 1.5*R);  //���òü����ڴ�С
	glViewport(0, 0, w, h); //����������С
	glMatrixMode(GL_MODELVIEW);  //ģ�;���ģʽ 
}
