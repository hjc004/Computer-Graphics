#include "stdafx.h"
#include <glut.h>

void reshape(int w,int h);
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
 
	char *argv[] = {"hello ", " "};
	int argc = 2; // must/should match the number of strings in argv


	glutInit(&argc, argv);    //��ʼ��GLUT�⣻

//������ȼ���µ���ʾģʽ�������壬��ɫ���ͣ����ֵ��
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB|GLUT_DEPTH);   
	glutInitWindowSize(600, 500);
	glutInitWindowPosition(1024 / 2 - 250, 768 / 2 - 250);
	glutCreateWindow("�򵥻�����");  //�������ڣ�����Ϊ��������
	 glutReshapeFunc(reshape);
	init();
	glutDisplayFunc(display);  //���ڻ��Ƶ�ǰ���ڣ�
	glutTimerFunc(100,mytime,10);
	glutMainLoop();   //��ʾ��ʼ���г������ڳ���Ľ�β��

	return 0;
}

  void reshape(int w,int h)
{   glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10,10,-10*h/w,10*h/w,1,200);    //������ά�۲���

	//gluPerspective(60,w/h,1,200);
    glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();   
}
void init()
{ 

   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        glEnable(GL_POINT_SMOOTH);
        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
        glEnable(GL_LINE_SMOOTH);
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
       glEnable(GL_POLYGON_SMOOTH);

    glLineWidth(3);
	glEnable(GL_DEPTH_TEST);  //������ȼ��

  }

void mytime(int value)
{

	//your code here;

	glutPostRedisplay();

	glutTimerFunc(100,mytime,10);
}

void display()
 {  

// glClear(GL_COLOR_BUFFER_BIT);  //����

//������ȼ���µ�����ģʽglClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); 

      glMatrixMode(GL_MODELVIEW);  //����ģʽ����
      glLoadIdentity();   //��վ����ջ
        gluLookAt(0,0,10,0.0,0.0,0.0,0.0,1.0,0.0);  //�����ӵ�     
	  
       //your code here;
	 
	   glPushMatrix();
	     glColor3f(1,0,0);  
         //your code here;
	     glutSolidCube(1);  //������������                
	   glPopMatrix();


	   glPushMatrix();
	     glColor3f(1,1,0);
         //your code here;
	     glutSolidCube(1);  //����������ͷ                
	   glPopMatrix();


	   glPushMatrix();
	     glColor3f(1,0.5,0.2);
         //your code here;
	     glutSolidCube(1);  //������������
	   glPopMatrix();

	   glPushMatrix();
	     glColor3f(1,0.5,0.2);
         //your code here;
         glutSolidCube(1);  //������������                
	   glPopMatrix();

	   glPushMatrix();
	     glColor3f(0.5,0.5,1);
         //your code here;
         glutSolidCube(1);  //������������                
	   glPopMatrix();

	   glPushMatrix();
	     glColor3f(0.5,0.5,1);
          //your code here;
	     glutSolidCube(1);  //������������                
	    glPopMatrix();
	 
      glutSwapBuffers();  //˫�����µ�ˢ�·���
}       


