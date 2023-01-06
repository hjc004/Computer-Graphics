#include "stdafx.h"  //标准库
#include <glut.h>  //glut库
#include <math.h>  //数学库

void Display(void);  //绘制函数
void Reshape(int w, int h); //窗口改变
void mytime(int value); //时间函数
void myinit(void); //初始化函数
void sun();  //太阳
void earth(); //地球
void moon();  //月球
void selectFont(int size, int charset, const char* face); //选择字体
void drawCNString(const char* str); //生成中文字体函数


float rs=50, re=30, rm=10;  //太阳、地球和月球半径
float xs=0,ys=0,xe=150,ye=0,xm=200,ym=0; //太阳、地球和月球
float as,ae,am,aes,ame,ams;  //太阳、地球、月球自转、地球绕太阳公转旋转角度

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
	myinit();  //初始化设置
	glutTimerFunc(200, mytime, 10);
	glutMainLoop();  //进入事件处理循环
	return 0;
}

void myinit()
{
	glPointSize(16);  //点大小
	glLineWidth(10);  //线宽

	/*反走样代码*/
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);


}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);  //清屏，默认为黑背景色
	glMatrixMode(GL_MODELVIEW); //设置矩阵模式为模型变换模式，表示在世界坐标系下
	glLoadIdentity();   //将当前矩阵设置为单位矩阵
   
	sun(); //绘制太阳
	earth(); //绘制地球
	moon();  //绘制月球

	glutSwapBuffers();   //双缓冲的刷新模式；
}


void sun()
{
  glPushMatrix(); 

   /* 绕太阳中心点(坐标原点）自转*/
    glRotatef(as,0,0,1); 

	 /*绘制太阳球*/
	glColor3f(1,0,0);
	glutWireSphere(rs,40,40);  //半径为re的球，球心在原点

	/*在太阳圆弧上画点*/
	glColor3f(1,1,0);
	glBegin(GL_POINTS);
      glVertex2f(xs+rs,ys);
	glEnd();
	
	 /*在绘制部分调用字体函数，写中文字*/
	selectFont(24, GB2312_CHARSET, "楷体_GB2312");  //设置字体楷体24号字
	glRasterPos2f(xs,ys);  //定位首字位置
	drawCNString("太阳");  //写字“太阳”
	
  glPopMatrix();

}

void earth()
{
	
    glPushMatrix();

		/*绕太阳中心点(坐标原点）公转*/
		glRotatef(aes,0,0,1);  

		/*绕地球中心点自转*/
		glTranslatef(xe,ye,0);
		glRotatef(ae,0,0,1);
		glTranslatef(-xe,-ye,0);


	  glPushMatrix();
		/*绘制地球*/
		glPushMatrix();
		glColor3f(0,0,1);
		glTranslatef(xe,ye,0);
		glutWireSphere(re,40,40);  //半径为re的球，球心在原点
		glPopMatrix();

	    
		/*在地球圆弧上画点*/
		glColor3f(1,1,0);	
		glBegin(GL_POINTS);
		glVertex2f(xe+re,ye);
		glEnd();
		
		/*在绘制部分调用字体函数，写中文字*/
		selectFont(24, GB2312_CHARSET, "楷体_GB2312");  //设置字体楷体24号字
		glRasterPos2f(xe,ye);  //定位首字位置
		drawCNString("地球");  //写字“地球”

	  glPopMatrix();

  glPopMatrix();



}
void moon()
{

	glPushMatrix();

		 /*绕太阳中心点(坐标原点）公转*/
		glRotatef(ams,0,0,1);

		/*绕地球中心点公转*/
		glTranslatef(xe,ye,0);
		glRotatef(ame,0,0,1);
		glTranslatef(-xe,-ye,0);

		/*绕月球中心点自转*/
		glTranslatef(xm,ym,0);
		glRotatef(am,0,0,1);
		glTranslatef(-xm,-ym,0);


		glPushMatrix();

			 /*绘制月球*/
			glPushMatrix();
			glColor3f(1,1,1);
			glTranslatef(xm,ym,0);
			glutWireSphere(rm,40,40);  //半径为rm的球，球心在原点
			glPopMatrix();

			/*在月球圆弧上画点*/
			glColor3f(1,1,0);
			glBegin(GL_POINTS);
			glVertex2f(xm+rm,ym);
			glEnd();
			
			//在绘制部分调用字体函数，写中文字
			selectFont(24, GB2312_CHARSET, "楷体_GB2312");  //设置字体楷体24号字
			glRasterPos2f(xm,ym);  //定位首字位置
			drawCNString("月球");  //写字“月球”


	   glPopMatrix();

	glPopMatrix();


}
void mytime(int value)
{

	as+=1;

	ae+=1;

	am+=1;

	aes+=2;

    ame+=2; 

	ams+=2;

	glutPostRedisplay();  //重画，相当于10重新调用Display(),改编后的变量得以传给绘制函数

	glutTimerFunc(100, mytime, 10);

}
void Reshape(GLsizei w,GLsizei h)
{
	glMatrixMode(GL_PROJECTION);  //投影矩阵模式
	glLoadIdentity();  //矩阵堆栈清空
	glViewport(0,0,w,h); //设置视区大小
	gluOrtho2D(-xm-rm-10,xm+rm+10,-xm-rm-10,xm+rm+10);  //设置裁剪窗口大小  
	glMatrixMode(GL_MODELVIEW);  //模型矩阵模式
	glLoadIdentity();  //矩阵堆栈清空

}

/************************************************************************/
/* 选择字体函数                                                                     */
/************************************************************************/
void selectFont(int size, int charset, const char* face) 
{
	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
		charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);
}




/************************************************************************/
/* 生成中文字体函数                                                                     */
/************************************************************************/
void drawCNString(const char* str)
{
	int len, i;
	wchar_t* wstring;
	HDC hDC = wglGetCurrentDC();
	GLuint list = glGenLists(1);

	// 计算字符的个数
	// 如果是双字节字符的（比如中文字符），两个字节才算一个字符
	// 否则一个字节算一个字符
	len = 0;
	for(i=0; str[i]!='\0'; ++i)
	{
		if( IsDBCSLeadByte(str[i]) )
			++i;
		++len;
	}

	// 将混合字符转化为宽字符
	wstring = (wchar_t*)malloc((len+1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len);
	wstring[len] = L'\0';

	// 逐个输出字符
	for(i=0; i<len; ++i)
	{
		wglUseFontBitmapsW(hDC, wstring[i], 1, list);
		glCallList(list);
	}

	// 回收所有临时资源
	free(wstring);
	glDeleteLists(list, 1);
}

