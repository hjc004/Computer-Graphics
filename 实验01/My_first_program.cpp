//��������My_first_program.cpp
#include "stdafx.h"
#include <glut.h>
void display(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  //����������ɫ
	glClear(GL_COLOR_BUFFER_BIT);   //ˢ����ɫ��������

	glFlush();   //����ˢ��������кͻ�������ʹ������δ��ִ�е�OpenGL����õ�ִ�У�
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

	glutInit(&argc, argv);    //��ʼ��GLUT�⣻
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   //������ʾģʽ�������壬��ɫ���ͣ�
	glutInitWindowSize(500, 500); //��ͼ���ڴ�С
	glutInitWindowPosition(1024 / 2 - 250, 768 / 2 - 250); //�������Ͻ�����Ļ��λ��
	glutCreateWindow("hello");  //�������ڣ�����Ϊ��hello����
	glutDisplayFunc(display);  //���ڻ��Ƶ�ǰ���ڣ�
	glutMainLoop();   //��ʾ��ʼ���г������ڳ���Ľ�β��
	return 0;
}