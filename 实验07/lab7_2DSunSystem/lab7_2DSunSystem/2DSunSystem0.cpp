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
 glutInit(&argc, argv);  //初始化GLUT库；
 glutInitWindowSize(700,700);  //设置显示窗口大小
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  //设置显示模式；（注意双缓冲）
 glutCreateWindow("A Rotating Sun System"); // 创建显示窗口
 glutDisplayFunc(Display);  //注册显示回调函数
 glutReshapeFunc(Reshape);  //注册窗口改变回调函数
   myinit();
 glutTimerFunc(200, mytime, 10);
 glutMainLoop();  //进入事件处理循环
 return 0;
}

void myinit()
{
	

}

void Display(void)
{
 glClear(GL_COLOR_BUFFER_BIT); 
 glMatrixMode(GL_MODELVIEW); //设置矩阵模式为模型变换模式，表示在世界坐标系下
 glLoadIdentity();   //将当前矩阵设置为单位矩阵


 glutSwapBuffers();   //双缓冲的刷新模式；
}

void mytime(int value)
{
 
 glutPostRedisplay();  //重画，相当于10重新调用Display(),改编后的变量得以传给绘制函数

 glutTimerFunc(200, mytime, 10);

}
void Reshape(GLsizei w,GLsizei h)
{
 glMatrixMode(GL_PROJECTION);  //投影矩阵模式
 glLoadIdentity();  //矩阵堆栈清空
  glViewport(0,0,w,h); //设置视区大小
  
  gluOrtho2D(0,w,0,h);  //设置裁剪窗口大小  
 glMatrixMode(GL_MODELVIEW);  //模型矩阵模式

}


