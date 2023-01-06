#include "stdafx.h"
#include <glut.h>

#define N 1000 //��������

int ww, hh;     // for display window width and height

int line[N][2];
int k = 0;//������

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

	glutInit(&argc, argv);  //��ʼ��GLUT�⣻
	glutInitWindowSize(800, 600);  //������ʾ���ڴ�С
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  //������ʾģʽ����ע��˫���壩
	glutCreateWindow("��껭��С������ʾ"); // ������ʾ����
	Myinit();

	glutDisplayFunc(Display);  //ע����ʾ�ص�����
	glutReshapeFunc(Reshape);  //ע�ᴰ�ڸı�ص�����
	glutMouseFunc(mymouse);// ��갴ť��Ӧ�ص�����
	glutMotionFunc(mymotion);// ��갴ť����ʱ�ƶ���Ӧ����

	glutMainLoop();  //�����¼�����ѭ��
	return 0;
}


void Myinit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glLineWidth(3.0);
}

//��Ⱦ�����ӳ���--------------------------------------------------------------------------
void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);   //ˢ����ɫ��������
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i<k; i++)
		glVertex2f(line[i][0], line[i][1]);
	glEnd();
	glutSwapBuffers();  //˫�����ˢ��ģʽ��
}

//-----------------------------------------------
void Reshape(int w, int h)  //���ڸı�ʱ�Զ���ȡ��ʾ���ڵĿ�w�͸�h
{
	glMatrixMode(GL_PROJECTION);  //ͶӰ����ģʽ
	glLoadIdentity();     //�����ջ���
	glViewport(0, 0, w, h);  //����������С
	gluOrtho2D(0, w, 0, h);   //���òü����ڴ�С
	ww = w;
	hh = h;
}

void mymouse(int x, int y, int button, int state)
{
	if (state == GLUT_DOWN &&button == GLUT_LEFT_BUTTON) { //�������
		line[k][0] = x;
		line[k][1] = hh - y;
		k++;
	}
	if (state == GLUT_UP &&button == GLUT_LEFT_BUTTON) { //����ɿ�
		line[k][0] = x;
		line[k][1] = hh - y;

	}

	glutPostRedisplay(); //�ػ�
}

void mymotion(int x, int y) {
	line[k][0] = x;
	line[k][1] = hh - y;
	k++;
	glutPostRedisplay(); //�ػ�
}
