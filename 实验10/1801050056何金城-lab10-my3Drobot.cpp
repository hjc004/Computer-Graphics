#include "stdafx.h"
#include <glut.h>

int angle = 0;
int flag = 1;
float tz = 0;

void reshape(int w, int h);
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

	char *argv[] = { "hello ", " " };
	int argc = 2; // must/should match the number of strings in argv


	glutInit(&argc, argv);    //��ʼ��GLUT�⣻

							  //������ȼ���µ���ʾģʽ�������壬��ɫ���ͣ����ֵ��
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 500);
	glutInitWindowPosition(1024 / 2 - 250, 768 / 2 - 250);
	glutCreateWindow("�򵥻�����");  //�������ڣ�����Ϊ��������
	glutReshapeFunc(reshape);
	init();
	glutDisplayFunc(display);  //���ڻ��Ƶ�ǰ���ڣ�
	glutTimerFunc(100, mytime, 10);
	glutMainLoop();   //��ʾ��ʼ���г������ڳ���Ľ�β��

	return 0;
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-10, 10, -10 * h / w, 10 * h / w, 1, 200);    //������ά�۲���
	gluPerspective(70, w / h, 1, 200);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void init()
{
	//������
	/*glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);*/

	glLineWidth(3);
	glEnable(GL_DEPTH_TEST);  //������ȼ��

}

void mytime(int value)
{

	//your code here;
	tz += 0.2;
	if (tz >= 10)  tz = 0;

	if ((angle >= 32) || (angle <= -32)) flag = -flag;

	if (flag == 1)
		angle += 5;
	else
		angle -= 5;

	glutPostRedisplay();

	glutTimerFunc(100, mytime, 10);
}

void display()
{

	//glClear(GL_COLOR_BUFFER_BIT);  //2D����
	
	//������ȼ���µ�3D����ģʽ
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); 

	glMatrixMode(GL_MODELVIEW);  //����ģʽ����
	glLoadIdentity();   //��վ����ջ
	gluLookAt(5, 5, 10, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);  //�����ӵ�     


	glPushMatrix();
	glColor3f(0.87, 0.23, 0.07);
	glTranslatef(0, -6, 0);
	glScalef(5, 0.5, 5);
	glutSolidCube(1);    //���Ƶ���01��
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.94, 0.44, 0.003);
	glTranslatef(5, -6, 0);
	glScalef(5, 0.5, 5);
	glutSolidCube(1);    //���Ƶ���02��
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.94, 0.44, 0.003);
	glTranslatef(-5, -6, 0);
	glScalef(5, 0.5, 5);
	glutSolidCube(1);    //���Ƶ���03��
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.87, 0.23, 0.07);
	glTranslatef(-5, -6, -5);
	glScalef(5, 0.5, 5);
	glutSolidCube(1);    //���Ƶ���04��
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.94, 0.44, 0.003);
	glTranslatef(0, -6, -5);
	glScalef(5, 0.5, 5);
	glutSolidCube(1);    //���Ƶ���05��
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.87, 0.23, 0.07);
	glTranslatef(5, -6, -5);
	glScalef(5, 0.5, 5);
	glutSolidCube(1);    //���Ƶ���06��
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.87, 0.23, 0.07);
	glTranslatef(-5, -6, 5);
	glScalef(5, 0.5, 5);
	glutSolidCube(1);    //���Ƶ���07��
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.94, 0.44, 0.003);
	glTranslatef(0, -6, 5);
	glScalef(5, 0.5, 5);
	glutSolidCube(1);    //���Ƶ���08��
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.87, 0.23, 0.07);
	glTranslatef(5, -6, 5);
	glScalef(5, 0.5, 5);
	glutSolidCube(1);    //���Ƶ���09��
	glPopMatrix();


	glTranslatef(0, 0, tz);   //����������ƽ��

	glPushMatrix();   //Push/Pop��������

	//������������
	glPushMatrix();
	glColor3f(0.23, 0.79, 0.85);
	glScalef(4, 4, 0.5);
	glutSolidCube(1);                  
	glPopMatrix();


	//����������ñ��
	glPushMatrix();
	glColor3f(0.79, 0.25, 0.99);
	glTranslatef(0, 3, 0.5);
	glScalef(1.2, 0.2, 1.2);
	glutSolidCube(1);
	glPopMatrix();
	//����������ñ��
	glPushMatrix();
	glColor3f(0.79, 0.25, 0.99);
	glTranslatef(0, 3.2, 0);
	glScalef(1, 0.7, 1);
	glutSolidCube(1);
	glPopMatrix();

	//����������ͷ
	glPushMatrix();
	glColor3f(0.99, 0.72, 0.086);
	glTranslatef(0, 2.5, 0);
	glScalef(1, 1, 0.5);
	glutSolidCube(1);                  
	glPopMatrix();


	//�������������ֱ�
	glPushMatrix();
	glColor3f(1, 0.5, 0.2);
	glTranslatef(0, 2, 0);   //��ת��
	glRotatef(angle, 1, 0, 0);   //��ת�Ƕ�
	glTranslatef(0, -2, 0);

	glTranslatef(-2.5, 0.5, 0);
	glScalef(1, 3, 0.5);
	glutSolidCube(1);  
	glPopMatrix();

	//��������������
	glPushMatrix();
	glColor3f(1, 0.5, 0.2);
	glTranslatef(0, 2, 0);   //��ת��
	glRotatef(angle, 1, 0, 0);   //��ת�Ƕ�
	glTranslatef(0, -2, 0);

	glTranslatef(-2.5, -1, 0);
	glScalef(1, 0.9, 1);
	glutSolidCube(1);
	glPopMatrix();


	//�������������ֱ�
	glPushMatrix();
	glColor3f(1, 0.5, 0.2);
	glTranslatef(0, 2, 0);
	glRotatef(-angle, 1, 0, 0);
	glTranslatef(0, -2, 0);

	glTranslatef(2.5, 0.5, 0);
	glScalef(1, 3, 0.5);
	glutSolidCube(1);              
	glPopMatrix();

	//��������������
	glPushMatrix();
	glColor3f(1, 0.5, 0.2);
	glTranslatef(0, 2, 0);   //��ת��
	glRotatef(-angle, 1, 0, 0);   //��ת�Ƕ�
	glTranslatef(0, -2, 0);

	glTranslatef(2.5, -1, 0);
	glScalef(1, 0.9, 1);
	glutSolidCube(1);
	glPopMatrix();


	//��������������      
	glPushMatrix();
	glColor3f(0.5, 0.5, 1);
	glTranslatef(0, -2, 0);  //��ת��
	glRotatef(-angle, 1, 0, 0);
	glTranslatef(0, 2, 0);

	glTranslatef(-1, -3.5, 0);
	glScalef(1, 3, 0.5);
	glutSolidCube(1);            
	glPopMatrix();

	//�������������
	glPushMatrix();
	glColor3f(0.5, 0.5, 1);
	glTranslatef(0, -2, 0);  //��ת��
	glRotatef(-angle, 1, 0, 0);
	glTranslatef(0, 2, 0);

	glTranslatef(-1, -4.9, 0);
	glScalef(1, 0.4, 1);
	glutSolidCube(1);
	glPopMatrix();


	//��������������      
	glPushMatrix();
	glColor3f(0.5, 0.5, 1);
	//your code here;
	glTranslatef(0, -2, 0);
	glRotatef(angle, 1, 0, 0);
	glTranslatef(0, 2, 0);

	glTranslatef(1, -3.5, 0);
	glScalef(1, 3, 0.5);
	glutSolidCube(1);            
	glPopMatrix();

	//�����������ҽ�
	glPushMatrix();
	glColor3f(0.5, 0.5, 1);
	//your code here;
	glTranslatef(0, -2, 0);
	glRotatef(angle, 1, 0, 0);
	glTranslatef(0, 2, 0);

	glTranslatef(1, -4.9, 0);
	glScalef(1, 0.35, 1);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();  //Push/Pop��������


	glutSwapBuffers();  //˫�����µ�ˢ�·���
}
