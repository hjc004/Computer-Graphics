#include "stdafx.h"
#include <glut.h>
#include <math.h>

int rs = 80, re = 20, rm = 5, rsel = 1.5;

int dse = 180; //�յؾ���rs + re + 6rm
int dsm = 220; //���¾���des + re + rm + 2rm
int dssel = 232.5; //��������dsm + rm + 2rsel
float as = 0, ae = 0, am = 0, asel = 0;//��ת�Ƕ�
float ase = 0, aem = 0, asm1 = 0, assel = 0;//��ת�Ƕ�

void sun(void);
void earth(void);
void moon(void);
void setellite(void);

void Display(void);
void Reshape(GLsizei w, GLsizei h);
void mytime(int value);
void myinit(void);

void selectFont(int size, int charset, const char* face); //ѡ������
void drawCNString(const char* str); //�����������庯��

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
	glutInitWindowSize(700, 700);  //������ʾ���ڴ�С
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
	glLineWidth(4);

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
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW); //���þ���ģʽΪģ�ͱ任ģʽ����ʾ����������ϵ��
	glLoadIdentity();   //����ǰ��������Ϊ��λ����

	sun();
	earth();
	moon();
	setellite();
	
	glutSwapBuffers();   //˫�����ˢ��ģʽ��
}

void sun()
{
	glPushMatrix();
	glColor3f(1, 0, 0);
	glRotatef(as, 0, 0, 1);
	glutWireSphere(rs, 40, 40);

	//��ǵ�---------
	glPointSize(5);
	glColor3f(1, 1, 1);
	glBegin(GL_POINTS);
	glVertex2f(rs, 0);
	glEnd();

	//����
	selectFont(20, GB2312_CHARSET, "����_GB2312");
	glRasterPos2f(0, 0);
	drawCNString("̫��");

	glPopMatrix();
}

void earth()
{
	glPushMatrix();
	//��ת-----------
	glRotatef(ase, 0, 0, 1);

	//��ת-----------
	glTranslatef(dse, 0, 0);
	glRotatef(ae, 0, 0, 1);
	glTranslatef(-dse, 0, 0);

	glColor3f(0, 0, 1);
	glTranslatef(dse, 0, 0);
	glutWireSphere(re, 40, 40);

	//��ǵ�---------
	glPointSize(5);
	glColor3f(1, 1, 1);
	glBegin(GL_POINTS);
	glVertex2f(re, 0);
	glEnd();

	//����
	selectFont(20, GB2312_CHARSET, "����_GB2312");
	glRasterPos2f(0, 0);
	drawCNString("����");

	glPopMatrix();
}

void moon()
{
	glPushMatrix();
	//��ת-----------
	glRotatef(asm1, 0, 0, 1);

	glTranslatef(dse, 0, 0);
	glRotatef(aem, 0, 0, 1);
	glTranslatef(-dse, 0, 0);

	//��ת-----------
	glTranslatef(dsm, 0, 0);
	glRotatef(am, 0, 0, 1);
	glTranslatef(-dsm, 0, 0);

	glColor3f(1, 1, 0);
	glTranslatef(dsm, 0, 0);
	glutWireSphere(rm, 30, 30);

	//��ǵ�---------
	glPointSize(5);
	glColor3f(1, 1, 1);
	glBegin(GL_POINTS);
	glVertex2f(rm, 0);
	glEnd();

	//����
	selectFont(20, GB2312_CHARSET, "����_GB2312");
	glRasterPos2f(0, 0);
	drawCNString("����");

	glPopMatrix();
}

//����---------------------------
void setellite() {
	glPushMatrix();

	//��ת-----------
	glRotatef(assel, 0, 0, 1);

	glTranslatef(dse, 0, 0);
	glRotatef(aem, 0, 0, 1);
	glTranslatef(-dse, 0, 0);

	glTranslatef(dsm, 0, 0);
	glRotatef(asel, 0, 0, 1);
	glTranslatef(-dsm, 0, 0);

	//��ת-----------
	glTranslatef(dssel, 0, 0);
	glRotatef(asel, 0, 0, 1);
	glTranslatef(-dssel, 0, 0);

	glColor3f(0.5, 0.5, 0.5);
	glTranslatef(dssel, 0, 0);
	glutWireSphere(rsel, 40, 40);

	//��ǵ�---------
	glColor3f(1, 1, 1);
	glBegin(GL_POINTS);
	glVertex2f(rsel, 0);
	glEnd();

	//����
	glColor3f(1, 0, 1);
	selectFont(20, GB2312_CHARSET, "����_GB2312");
	glRasterPos2f(0, 0);
	drawCNString("����");

	glPopMatrix();

}

//ʱ�亯��
void mytime(int value)
{
	as += 0.3;
	ae += 0.3;
	am += 0.3;
	asel += 0.3;

	ase += 0.3;
	aem += 0.3;
	asm1 += 0.3;
	assel += 0.3;

	glutPostRedisplay();  //�ػ����൱��10���µ���Display(),�ı��ı������Դ������ƺ���

	glutTimerFunc(30, mytime, 10);

}

//������������-------------------
void Reshape(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);  //ͶӰ����ģʽ
	glLoadIdentity();  //�����ջ���
	glViewport(0, 0, w, h); //����������С

	gluOrtho2D(-(dsm + 4 * rm), dsm + 4 * rm, -(dsm + 4 * rm), dsm + 4 * rm);  //���òü����ڴ�С  
	glMatrixMode(GL_MODELVIEW);  //ģ�;���ģʽ

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
	for (i = 0; str[i] != '\0'; ++i)
	{
		if (IsDBCSLeadByte(str[i]))
			++i;
		++len;
	}

	// ������ַ�ת��Ϊ���ַ�
	wstring = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len);
	wstring[len] = L'\0';

	// �������ַ�
	for (i = 0; i<len; ++i)
	{
		wglUseFontBitmapsW(hDC, wstring[i], 1, list);
		glCallList(list);
	}

	// ����������ʱ��Դ
	free(wstring);
	glDeleteLists(list, 1);
}

