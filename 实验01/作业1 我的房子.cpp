//��������My_first_program.cpp
#include "stdafx.h"
#include <glut.h>
void display(void)  //���ƺ���
{
	//glClearColor(0.0f, 1.0f, 0.0f, 0.0f);  //����������ɫ
	//glClear(GL_COLOR_BUFFER_BIT);   //ˢ����ɫ��������
	
	//����ɫ����
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

	//������
	 //�������
	glColor3f(0.3, 0.71, 0.85);
	glRectf(-0.5, -0.6, 0.5, 0.1);
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
	 //�Ű���
	glPointSize(5.0); //��Ĵ�С����
	glBegin(GL_POINTS);
	glColor3f(0, 0, 0);
	glVertex2f(0.15, -0.35);
	glEnd();


	glFlush();   //����ˢ��������кͻ�������ʹ������δ��ִ�е�OpenGL����õ�ִ�У�
}

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine,int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	char *argv[] = { "hello ", " " };
	int argc = 2; // must/should match the number of strings in argv

	glutInit(&argc, argv);    //��ʼ��GLUT�⣻
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   //������ʾģʽ�������壬��ɫ���ͣ�
	glutInitWindowSize(500, 500); //��ͼ���ڴ�С
	glutInitWindowPosition(1024 / 2 - 250, 768 / 2 - 250); //�������Ͻ�����Ļ��λ��
	glutCreateWindow("�ҵķ���");  //�������ڣ�����Ϊ�� ����
	glutDisplayFunc(display);  //���ڻ��Ƶ�ǰ���ڣ�
	glutMainLoop();   //��ʾ��ʼ���г������ڳ���Ľ�β��
	return 0;
}