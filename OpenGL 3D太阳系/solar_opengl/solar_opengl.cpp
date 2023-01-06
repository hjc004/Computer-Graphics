// solar_opengl.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#pragma warning(disable : 4996)

#include <iostream>
#include <cmath>
#include <cstdlib>
#ifdef _WIN32
#include <Windows.h>
#endif
#include <gl\gl.h>
#include <gl\glut.h>
#include <GL\glu.h>

#include "tga.h"
#include "solarsystem.h"
#include "camera.h"
#include "globals.h"

int screenWidth, screenHeight;

TGA *welcome, *stars, *moon;
//轨道显示开关
bool showOrbits = true;

bool welcomeDialogue = true;

SolarSystem solarSystem;

Camera camera;

double time;
double timeSpeed;

int counter = 0;

//控制开关
struct ControlStates
{
	bool forward, backward;
	bool left, right;
	bool yawLeft, yawRight;
	bool pitchUp, pitchDown;
	bool rollLeft, rollRight;
} controls;

//定时器
void timer(int)
{
	glutPostRedisplay();
	glutTimerFunc(10, timer, 0); //10ms循环一次
}

//随机数
float random(float max)
{
	return (float)(std::rand() % 1000) * max * 0.001;
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	GLfloat matSpecular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat matAmbience[] = {0.3, 0.3, 0.3, 1.0};
	GLfloat matShininess[] = {20.0};
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbience);

	GLfloat lightAmbient[] = {0.3, 0.3, 0.3, 1.0};
	GLfloat lightDiffuse[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat lightSpecular[] = {1.0, 1.0, 1.0, 1.0};

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDisable(GL_LIGHTING);

	//加载图片
	welcome = new TGA((char *)"images/welcome3.tga");
	stars = new TGA((char *)"images/stars.tga");
	moon = new TGA((char *)"images/moon.tga");

	TGA *sun = new TGA((char *)"images/sun.tga");
	TGA *mercury = new TGA((char *)"images/mercury.tga");
	TGA *venus = new TGA((char *)"images/venus.tga");
	TGA *earth = new TGA((char *)"images/earth.tga");
	TGA *mars = new TGA((char *)"images/mars.tga");
	TGA *jupiter = new TGA((char *)"images/jupiter.tga");
	TGA *saturn = new TGA((char *)"images/saturn.tga");
	TGA *uranus = new TGA((char *)"images/uranus.tga");
	TGA *neptune = new TGA((char *)"images/neptune.tga");
	TGA *pluto = new TGA((char *)"images/pluto.tga");

	solarSystem.addPlanet(0, 1, 500, 695500, sun->getTextureHandle());					   //太远
	solarSystem.addPlanet(57910000, 88, 58.6, 2440, mercury->getTextureHandle());		   //水星
	solarSystem.addPlanet(108200000, 224.65, 243, 6052, venus->getTextureHandle());		   //金星
	solarSystem.addPlanet(149600000, 365, 1, 6371, earth->getTextureHandle());			   //地球
	solarSystem.addPlanet(227939100, 686, 1.03f, 3389, mars->getTextureHandle());		   //火星
	solarSystem.addPlanet(778500000, 4332, 0.4139, 69911, jupiter->getTextureHandle());	   //木星
	solarSystem.addPlanet(1433000000, 10759, 0.44375, 58232, saturn->getTextureHandle());  //土星
	solarSystem.addPlanet(2877000000, 30685, 0.718056, 25362, uranus->getTextureHandle()); //天王星
	solarSystem.addPlanet(4503000000, 60188, 0.6713, 24622, neptune->getTextureHandle());  //海王星
	solarSystem.addPlanet(5906380000, 90616, 6.39, 1137, pluto->getTextureHandle());	   //冥王星
	solarSystem.addMoon(3, 7000000, 27.3, 27.3, 1738, moon->getTextureHandle());		   //月球

	time = 2.552f;
	timeSpeed = 0.1f;

	//控制开关初始化
	controls.forward = false;
	controls.backward = false;
	controls.left = false;
	controls.right = false;
	controls.rollLeft = false;
	controls.rollRight = false;
	controls.pitchUp = false;
	controls.pitchDown = false;
	controls.yawLeft = false;
	controls.yawRight = false;

	timer(0);
}

//绘制skybox
void drawCube(void)
{
	glBegin(GL_QUADS);

	//前
	glTexCoord2f(0.0f, 0.0f);//纹理载入函数
	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	//后
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);

	//左
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);

	//右
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	//上
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);

	//下
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	glEnd();
}

void display(void)
{
	//欢迎页
	if (counter < 300)//3s
		counter++;
	else if (welcomeDialogue == 1)
		welcomeDialogue = 0;

	time += timeSpeed;
	solarSystem.calculatePositions(time);

	if (controls.forward)
		camera.forward();
	if (controls.backward)
		camera.backward();
	if (controls.left)
		camera.left();
	if (controls.right)
		camera.right();
	if (controls.yawLeft)
		camera.yawLeft();
	if (controls.yawRight)
		camera.yawRight();
	if (controls.rollLeft)
		camera.rollLeft();
	if (controls.rollRight)
		camera.rollRight();
	if (controls.pitchUp)
		camera.pitchUp();
	if (controls.pitchDown)
		camera.pitchDown();

	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	//设置透视矩阵以渲染三维世界
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0f, (float)screenWidth / (float)screenHeight, 0.001f, 500.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//相机方向变换
	camera.transformOrientation();

	//绘制skybox
	glBindTexture(GL_TEXTURE_2D, stars->getTextureHandle());
	drawCube();

	//相机平移变换
	camera.transformTranslation();

	GLfloat lightPosition[] = {0.0, 0.0, 0.0, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	solarSystem.render();
	glDisable(GL_LIGHTING);

	//渲染轨道
	if (showOrbits)
		solarSystem.renderOrbits();

	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)screenWidth, (GLdouble)screenHeight, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//欢迎页
	if (welcomeDialogue)
	{
		glBindTexture(GL_TEXTURE_2D, welcome->getTextureHandle());
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f((GLdouble)screenWidth, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2f((GLdouble)screenWidth, (GLdouble)screenHeight);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(0.0f, (GLdouble)screenHeight);
		glEnd();
	}

	glFlush();
	glutSwapBuffers();
}

//键盘控制
void keyDown(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '-':
		timeSpeed /= 2.0f; // 速率减半
		break;
	case '=':
		timeSpeed *= 2.0f; // 速率加倍
		break;
	case '[':
		planetSizeScale /= 1.2; // 天体半径缩小
		break;
	case ']':
		planetSizeScale *= 1.2; // 天体半径放大
		break;
	case 'o':
		showOrbits = !showOrbits; // 轨道显示开关
		break;
	case 'w':
		controls.forward = true;
		break;
	case 's':
		controls.backward = true;
		break;
	case 'a':
		controls.left = true;
		break;
	case 'd':
		controls.right = true;
		break;
	case 'k':
		controls.pitchUp = true;
		break;
	case 'j':
		controls.rollLeft = true;
		break;
	case 'l':
		controls.rollRight = true;
		break;
	case 'i':
		controls.pitchDown = true;
		break;
	case 'q':
		controls.yawLeft = true;
		break;
	case 'e':
		controls.yawRight = true;
		break;
	}
}

void keyUp(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		controls.forward = false;
		break;
	case 's':
		controls.backward = false;
		break;
	case 'a':
		controls.left = false;
		break;
	case 'd':
		controls.right = false;
		break;
	case 'j':
		controls.rollLeft = false;
		break;
	case 'l':
		controls.rollRight = false;
		break;
	case 'k':
		controls.pitchUp = false;
		break;
	case 'i':
		controls.pitchDown = false;
		break;
	case 'q':
		controls.yawLeft = false;
		break;
	case 'e':
		controls.yawRight = false;
		break;
	}
}

void reshape(int w, int h)
{
	screenWidth = w;
	screenHeight = h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1200, 700);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutMainLoop();
	return 0;
}