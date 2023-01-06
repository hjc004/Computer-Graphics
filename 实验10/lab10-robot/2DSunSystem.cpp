#include "stdafx.h"  //��׼��
#include <glut.h>  //glut��
#include <math.h>  //��ѧ��

void Display(void);  //���ƺ���
void Reshape(int w, int h); //���ڸı�
void mytime(int value); //ʱ�亯��
void myinit(void); //��ʼ������
void sun();  //̫��
void earth(); //����
void moon();  //����
void selectFont(int size, int charset, const char* face); //ѡ������
void drawCNString(const char* str); //�����������庯��


float rs=50, re=30, rm=10;  //̫�������������뾶
float xs=0,ys=0,xe=150,ye=0,xm=200,ym=0; //̫�������������
float as,ae,am,aes,ame,ams;  //̫��������������ת��������̫����ת��ת�Ƕ�

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
	myinit();  //��ʼ������
	glutTimerFunc(200, mytime, 10);
	glutMainLoop();  //�����¼�����ѭ��
	return 0;
}

void myinit()
{
	glPointSize(16);  //���С
	glLineWidth(10);  //�߿�

	/*����������*/
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
	glClear(GL_COLOR_BUFFER_BIT);  //������Ĭ��Ϊ�ڱ���ɫ
	glMatrixMode(GL_MODELVIEW); //���þ���ģʽΪģ�ͱ任ģʽ����ʾ����������ϵ��
	glLoadIdentity();   //����ǰ��������Ϊ��λ����
   
	sun(); //����̫��
	earth(); //���Ƶ���
	moon();  //��������

	glutSwapBuffers();   //˫�����ˢ��ģʽ��
}


void sun()
{
  glPushMatrix(); 

   /* ��̫�����ĵ�(����ԭ�㣩��ת*/
    glRotatef(as,0,0,1); 

	 /*����̫����*/
	glColor3f(1,0,0);
	glutWireSphere(rs,40,40);  //�뾶Ϊre����������ԭ��

	/*��̫��Բ���ϻ���*/
	glColor3f(1,1,0);
	glBegin(GL_POINTS);
      glVertex2f(xs+rs,ys);
	glEnd();
	
	 /*�ڻ��Ʋ��ֵ������庯����д������*/
	selectFont(24, GB2312_CHARSET, "����_GB2312");  //�������忬��24����
	glRasterPos2f(xs,ys);  //��λ����λ��
	drawCNString("̫��");  //д�֡�̫����
	
  glPopMatrix();

}

void earth()
{
	
    glPushMatrix();

		/*��̫�����ĵ�(����ԭ�㣩��ת*/
		glRotatef(aes,0,0,1);  

		/*�Ƶ������ĵ���ת*/
		glTranslatef(xe,ye,0);
		glRotatef(ae,0,0,1);
		glTranslatef(-xe,-ye,0);


	  glPushMatrix();
		/*���Ƶ���*/
		glPushMatrix();
		glColor3f(0,0,1);
		glTranslatef(xe,ye,0);
		glutWireSphere(re,40,40);  //�뾶Ϊre����������ԭ��
		glPopMatrix();

	    
		/*�ڵ���Բ���ϻ���*/
		glColor3f(1,1,0);	
		glBegin(GL_POINTS);
		glVertex2f(xe+re,ye);
		glEnd();
		
		/*�ڻ��Ʋ��ֵ������庯����д������*/
		selectFont(24, GB2312_CHARSET, "����_GB2312");  //�������忬��24����
		glRasterPos2f(xe,ye);  //��λ����λ��
		drawCNString("����");  //д�֡�����

	  glPopMatrix();

  glPopMatrix();



}
void moon()
{

	glPushMatrix();

		 /*��̫�����ĵ�(����ԭ�㣩��ת*/
		glRotatef(ams,0,0,1);

		/*�Ƶ������ĵ㹫ת*/
		glTranslatef(xe,ye,0);
		glRotatef(ame,0,0,1);
		glTranslatef(-xe,-ye,0);

		/*���������ĵ���ת*/
		glTranslatef(xm,ym,0);
		glRotatef(am,0,0,1);
		glTranslatef(-xm,-ym,0);


		glPushMatrix();

			 /*��������*/
			glPushMatrix();
			glColor3f(1,1,1);
			glTranslatef(xm,ym,0);
			glutWireSphere(rm,40,40);  //�뾶Ϊrm����������ԭ��
			glPopMatrix();

			/*������Բ���ϻ���*/
			glColor3f(1,1,0);
			glBegin(GL_POINTS);
			glVertex2f(xm+rm,ym);
			glEnd();
			
			//�ڻ��Ʋ��ֵ������庯����д������
			selectFont(24, GB2312_CHARSET, "����_GB2312");  //�������忬��24����
			glRasterPos2f(xm,ym);  //��λ����λ��
			drawCNString("����");  //д�֡�����


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

	glutPostRedisplay();  //�ػ����൱��10���µ���Display(),�ı��ı������Դ������ƺ���

	glutTimerFunc(100, mytime, 10);

}
void Reshape(GLsizei w,GLsizei h)
{
	glMatrixMode(GL_PROJECTION);  //ͶӰ����ģʽ
	glLoadIdentity();  //�����ջ���
	glViewport(0,0,w,h); //����������С
	gluOrtho2D(-xm-rm-10,xm+rm+10,-xm-rm-10,xm+rm+10);  //���òü����ڴ�С  
	glMatrixMode(GL_MODELVIEW);  //ģ�;���ģʽ
	glLoadIdentity();  //�����ջ���

}

/************************************************************************/
/* ѡ�����庯��                                                                     */
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
/* �����������庯��                                                                     */
/************************************************************************/
void drawCNString(const char* str)
{
	int len, i;
	wchar_t* wstring;
	HDC hDC = wglGetCurrentDC();
	GLuint list = glGenLists(1);

	// �����ַ��ĸ���
	// �����˫�ֽ��ַ��ģ����������ַ����������ֽڲ���һ���ַ�
	// ����һ���ֽ���һ���ַ�
	len = 0;
	for(i=0; str[i]!='\0'; ++i)
	{
		if( IsDBCSLeadByte(str[i]) )
			++i;
		++len;
	}

	// ������ַ�ת��Ϊ���ַ�
	wstring = (wchar_t*)malloc((len+1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len);
	wstring[len] = L'\0';

	// �������ַ�
	for(i=0; i<len; ++i)
	{
		wglUseFontBitmapsW(hDC, wstring[i], 1, list);
		glCallList(list);
	}

	// ����������ʱ��Դ
	free(wstring);
	glDeleteLists(list, 1);
}

