#include "stdafx.h"
#include <glut.h>
#include <math.h>
#define PI 3.14159  //����Բ����
int n = 6, R = 10;  //����α��������Բ�뾶
float cx = 0, cy = 0;
float sx = 1, sy = 1;
int flag = 1;

float theta = 0.0;  //��ת��ʼ�Ƕ�ֵ
void Display(void);
void Reshape(GLsizei w, GLsizei h);
void Myidle();

void Display(void)  //���ƺ���
{
	//glClearColor(0.0f, 1.0f, 0.0f, 0.0f);  //����������ɫ
	//glClear(GL_COLOR_BUFFER_BIT);   //ˢ����ɫ��������

	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //���þ���ģʽΪģ�ͱ任ģʽ����ʾ����������ϵ��
	glLoadIdentity();   //����ǰ��������Ϊ��λ����

	glRotatef(theta, 0, 0, 1); //��ԭ����תALPHA�Ƕ�
	glScalef(sx, sy, 1);  //��������
	glTranslatef(-cx, -cy, 0);  //ƽ�ƻ�ԭ��

	//����ɫ����
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

	//������
	//�������
	glColor3f(0.3, 0.71, 0.85);
	glRectf(-0.5, -0.6, 0.5, 0.1);
	glEnd();
	//�ݶ�
	glColor3f(0.85, 0.27, 0.87);
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.6, 0.1); //����1
	glVertex2f(0, 0.55); //����2
	glVertex2f(0.6, 0.1); //����3
	glEnd();
	//����
	glColor3f(0.45, 0.95, 0.65);
	glRectf(-0.4, -0.3, -0.1, 0);
	glEnd();
	//���ڱ߿�
	glColor3f(0.63, 0.35, 0.02);
	glBegin(GL_LINES);
	glVertex2f(-0.4, -0.15);  //�˵�1
	glVertex2f(-0.1, -0.15); //�˵�2
	glEnd();

	glColor3f(0.63, 0.35, 0.02);
	glBegin(GL_LINES);
	glVertex2f(-0.25, 0);  //�˵�1
	glVertex2f(-0.25, -0.3); //�˵�2
	glEnd();
	//��
	glColor3f(0.47, 0.5, 0.62);
	glRectf(0.1, -0.6, 0.4, -0.1);
	glEnd();
	//�Ű���
	/*glPointSize(5.0); //��Ĵ�С����
	glBegin(GL_POINTS);
	glColor3f(0, 0, 0);
	glVertex2f(0.15, -0.35);
	glEnd();*/

	//glFlush();   //����ˢ��������кͻ�������ʹ������δ��ִ�е�OpenGL����õ�ִ�У�
	glutSwapBuffers();   //˫�����ˢ��ģʽ��
}

void Myidle()
{

	theta += 0.5;                              //������ת�ٶ�
	if (theta >= 360) theta -= 360;

	if (flag == 1)
	{
		//�������ӷŴ�һ������
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

	glutPostRedisplay();  //�ػ����൱�����µ���Display(),�ı��ı������Դ������ƺ���
}

//��������----------------------
void Reshape(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);  //ͶӰ����ģʽ
	glLoadIdentity();  //�����ջ���
	gluOrtho2D(-1.5*R*w / h, 1.5*R*w / h, -1.5*R, 1.5*R);  //���òü����ڴ�С
	glViewport(0, 0, w, h); //����������С
	glMatrixMode(GL_MODELVIEW);  //ģ�;���ģʽ 
}

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	char *argv[] = { "hello ", " " };
	int argc = 2; // must/should match the number of strings in argv

	glutInit(&argc, argv);    //��ʼ��GLUT�⣻
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);   //������ʾģʽ�������壬��ɫ���ͣ�
	glutInitWindowSize(700, 700); //��ͼ���ڴ�С
	glutInitWindowPosition(1024 / 2 - 250, 768 / 2 - 250); //�������Ͻ�����Ļ��λ��
	glutCreateWindow("����ħ��תȦȦ~~");  //�������ڣ�����Ϊ�� ����
	glutDisplayFunc(Display);  //ע����ʾ�ص�����
	glutReshapeFunc(Reshape);  //ע�ᴰ�ڸı�ص�����
	glutIdleFunc(Myidle);    //ע�����ûص�����
	glutMainLoop();  //�����¼�����ѭ��
	return 0;
}