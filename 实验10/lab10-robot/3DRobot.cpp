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


	glutInit(&argc, argv);    //初始化GLUT库；

//设置深度检测下的显示模式；（缓冲，颜色类型，深度值）
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB|GLUT_DEPTH);   
	glutInitWindowSize(600, 500);
	glutInitWindowPosition(1024 / 2 - 250, 768 / 2 - 250);
	glutCreateWindow("简单机器人");  //创建窗口，标题为“…”；
	 glutReshapeFunc(reshape);
	init();
	glutDisplayFunc(display);  //用于绘制当前窗口；
	glutTimerFunc(100,mytime,10);
	glutMainLoop();   //表示开始运行程序，用于程序的结尾；

	return 0;
}

  void reshape(int w,int h)
{   glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10,10,-10*h/w,10*h/w,1,200);    //定义三维观察体

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
	glEnable(GL_DEPTH_TEST);  //启用深度检测

  }

void mytime(int value)
{

	//your code here;

	glutPostRedisplay();

	glutTimerFunc(100,mytime,10);
}

void display()
 {  

// glClear(GL_COLOR_BUFFER_BIT);  //清屏

//启用深度检测下的清屏模式glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); 

      glMatrixMode(GL_MODELVIEW);  //矩阵模式设置
      glLoadIdentity();   //清空矩阵堆栈
        gluLookAt(0,0,10,0.0,0.0,0.0,0.0,1.0,0.0);  //设置视点     
	  
       //your code here;
	 
	   glPushMatrix();
	     glColor3f(1,0,0);  
         //your code here;
	     glutSolidCube(1);  //绘制立方体身                
	   glPopMatrix();


	   glPushMatrix();
	     glColor3f(1,1,0);
         //your code here;
	     glutSolidCube(1);  //绘制立方体头                
	   glPopMatrix();


	   glPushMatrix();
	     glColor3f(1,0.5,0.2);
         //your code here;
	     glutSolidCube(1);  //绘制立方体手
	   glPopMatrix();

	   glPushMatrix();
	     glColor3f(1,0.5,0.2);
         //your code here;
         glutSolidCube(1);  //绘制立方体手                
	   glPopMatrix();

	   glPushMatrix();
	     glColor3f(0.5,0.5,1);
         //your code here;
         glutSolidCube(1);  //绘制立方体腿                
	   glPopMatrix();

	   glPushMatrix();
	     glColor3f(0.5,0.5,1);
          //your code here;
	     glutSolidCube(1);  //绘制立方体腿                
	    glPopMatrix();
	 
      glutSwapBuffers();  //双缓冲下的刷新方法
}       


