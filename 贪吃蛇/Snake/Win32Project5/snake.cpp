#include "stdafx.h"
#include <GL/glut.h> 
#include <stdlib.h>

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

#include<vector>
#include<cmath>
using namespace std;
vector<int> x;
vector<int> y;
int point_x, point_y;
int direction = GLUT_KEY_RIGHT;
int level = 150;

void restart()
{
	x.clear();
	y.clear();
	int i;
	for (i = 0; i < 30; i++)
	{
		x.push_back(30 - i);
		y.push_back(75);
	}
	direction = GLUT_KEY_RIGHT;
}

void menu(int input)
{
	level = input;
	glutPostRedisplay();
}

double random(double start, double end)
{
	return start + (end - start)*rand() / (RAND_MAX + 1.0);
}

void createpoint()
{
	int i;
	bool state = true;
	while (1)
	{
		point_x = random(0, 200);
		point_y = random(0, 150);
		for (i = 0; i < x.size(); i++)
		{
			if ((x[i] == point_x) && (y[i] == point_y))
			{
				state = false;
				break;
			}
		}
		if (state == true)
			break;
	}
}

void move()
{
	int i;
	for (i = x.size() - 1; i > 0; i--)
	{
		x[i] = x[i - 1];
		y[i] = y[i - 1];
	}
}

void special(int key, int x, int y)
{
	if ((key != direction) && (abs(key - direction) != 2))
		direction = key;
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void display(void)
{
	int i;
	if ((x[0] < 0) || (x[0] > 200) || (y[0] < 0) || (y[0] > 150))
		restart();
	for (i = 1; i < x.size(); i++)
	{
		if ((x[0] == x[i]) && (y[0] == y[i]))
		{
			restart();
			break;
		}
	}
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 0.0);
	glPointSize(5);
	for (i = 0; i < x.size(); i++)
	{
		glBegin(GL_POINTS);
		glVertex2i(x[i], y[i]);
		glEnd();
	}
	if ((x[0] == point_x) && (y[0] == point_y))
	{
		x.push_back(x[0]);
		y.push_back(y[0]);
		createpoint();
	}
	glBegin(GL_POINTS);
	glVertex2i(point_x, point_y);
	glEnd();
	glFlush();
}

void timer(int i) {

	move();  switch (direction)

	{

	case GLUT_KEY_RIGHT: ::x[0]++; break;

	case GLUT_KEY_UP: ::y[0]++; break;

	case GLUT_KEY_LEFT: ::x[0]--; break;

	case GLUT_KEY_DOWN: ::y[0]--; break;

	}

	glutTimerFunc(level, timer, 1);

	glutPostRedisplay();

}

int main(int argc, char** argv)
{
	int i;
	for (i = 0; i < 30; i++)
	{
		x.push_back(30 - i);
		y.push_back(75);
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(700, 600);
	glutCreateWindow("1801050056-何金城-贪吃蛇");
	init();
	glutCreateMenu(menu);
	glutAddMenuEntry("低级", 150);
	glutAddMenuEntry("中级", 100);
	glutAddMenuEntry("高级", 50);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	createpoint();
	glutDisplayFunc(display);
	glutSpecialFunc(special);
	glutTimerFunc(level, timer, 1);
	glutMainLoop();
}