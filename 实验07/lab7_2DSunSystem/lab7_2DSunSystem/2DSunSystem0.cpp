#include "stdafx.h"
#include <glut.h>
#include <math.h>



void Display(void);
void Reshape(int w, int h);
void mytime(int value);
void myinit(void);

int APIENTRY _tWinMain(HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPTSTR    lpCmdLine,
        int       nCmdShow)
{
 UNREFERENCED_PARAMETER(hPrevInstance);
 UNREFERENCED_PARAMETER(lpCmdLine);
 char *argv[] = {"hello ", " "};
 int argc = 2; // must/should match the number of strings in argv
 glutInit(&argc, argv);  //��ʼ��GLUT�⣻
 glutInitWindowSize(700,700);  //������ʾ���ڴ�С
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  //������ʾģʽ����ע��˫���壩
 glutCreateWindow("A Rotating Sun System"); // ������ʾ����
 glutDisplayFunc(Display);  //ע����ʾ�ص�����
 glutReshapeFunc(Reshape);  //ע�ᴰ�ڸı�ص�����
   myinit();
 glutTimerFunc(200, mytime, 10);
 glutMainLoop();  //�����¼�����ѭ��
 return 0;
}

void myinit()
{
	

}

void Display(void)
{
 glClear(GL_COLOR_BUFFER_BIT); 
 glMatrixMode(GL_MODELVIEW); //���þ���ģʽΪģ�ͱ任ģʽ����ʾ����������ϵ��
 glLoadIdentity();   //����ǰ��������Ϊ��λ����


 glutSwapBuffers();   //˫�����ˢ��ģʽ��
}

void mytime(int value)
{
 
 glutPostRedisplay();  //�ػ����൱��10���µ���Display(),�ı��ı������Դ������ƺ���

 glutTimerFunc(200, mytime, 10);

}
void Reshape(GLsizei w,GLsizei h)
{
 glMatrixMode(GL_PROJECTION);  //ͶӰ����ģʽ
 glLoadIdentity();  //�����ջ���
  glViewport(0,0,w,h); //����������С
  
  gluOrtho2D(0,w,0,h);  //���òü����ڴ�С  
 glMatrixMode(GL_MODELVIEW);  //ģ�;���ģʽ

}


