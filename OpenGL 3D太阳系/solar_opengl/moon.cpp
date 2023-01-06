#pragma warning(disable : 4996)

#include "moon.h"
#include <cmath>

#ifdef _WIN32
#include <Windows.h>
#endif
#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\glut.h>
#include "globals.h"

Moon::Moon(float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle)
{
	this->distanceFromPlanet = distanceFromPlanet;
	this->orbitTime = orbitTime;
	this->rotationTime = rotationTime;
	this->radius = radius;
	this->textureHandle = textureHandle;
}

//计算位置
void Moon::calculatePosition(float time)
{
	//绕行星轨道的角度
	float angle = time * 3.1419f / orbitTime;

	//三角函数
	position[0] = sin(angle) * distanceFromPlanet;
	position[1] = cos(angle) * distanceFromPlanet;
	position[2] = 0;

	rotation = time * 360 / rotationTime;
}

//渲染
void Moon::render(void)
{
	glPushMatrix();

	// 绑定纹理
	glBindTexture(GL_TEXTURE_2D, textureHandle);

	// 移动、旋转
	glTranslatef(position[0] * distanceScale, position[1] * distanceScale, position[2] * distanceScale);
	glRotatef(-rotation, 0.0f, 0.0f, 1.0f);

	// 渲染为GLU二次对象
	GLUquadricObj *quadric = gluNewQuadric();
	gluQuadricTexture(quadric, true);
	gluQuadricNormals(quadric, GLU_SMOOTH);

	gluSphere(quadric, radius * planetSizeScale, 30, 30);

	glPopMatrix();
}

// 渲染轨道
void Moon::renderOrbit(void)
{
	//line strip
	glBegin(GL_LINE_STRIP);

	// 画圆
	for (float angle = 0.0f; angle < 6.283185307f; angle += 0.1f)
	{
		glVertex3f(sin(angle) * distanceFromPlanet * distanceScale, cos(angle) * distanceFromPlanet * distanceScale, 0.0f);
	}
	glVertex3f(0.0f, distanceFromPlanet * distanceScale, 0.0f);

	glEnd();
}