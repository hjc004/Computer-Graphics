#pragma warning(disable : 4996)

#include "planet.h"
#include <cmath>

#ifdef _WIN32
#include <Windows.h>
#endif
#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\glut.h>
#include "globals.h"

float planetSizeScale = 0.000005f;

Planet::Planet(float distanceFromSun, float orbitTime, float rotationTime, float radius, GLuint textureHandle)
{
	this->distanceFromSun = distanceFromSun;
	this->orbitTime = orbitTime;
	this->rotationTime = rotationTime;
	this->radius = radius;
	this->textureHandle = textureHandle;
}

void Planet::calculatePosition(float time)
{
	//找到绕太阳轨道的angle
	float angle = time * 3.1419f / orbitTime;

	//三角函数
	position[0] = sin(angle) * distanceFromSun;
	position[1] = cos(angle) * distanceFromSun;
	position[2] = 0;

	rotation = time * 360 / rotationTime;

	//卫星位置计算
	for (int i = 0; i < moons.size(); i++)
	{
		moons[i].calculatePosition(time);
	}
}

//渲染
void Planet::render(void)
{
	glPushMatrix();

	//缩放移动
	glTranslatef(position[0] * distanceScale, position[1] * distanceScale, position[2] * distanceScale);

	//渲染卫星
	for (int i = 0; i < moons.size(); i++)
	{
		moons[i].render();
	}

	// 绕行星旋转
	glRotatef(rotation, 0.0f, 0.0f, 1.0f);

	//绑定纹理
	glBindTexture(GL_TEXTURE_2D, textureHandle);

	GLUquadricObj *quadric = gluNewQuadric();
	gluQuadricTexture(quadric, true);
	gluQuadricNormals(quadric, GLU_SMOOTH);

	if (distanceFromSun < 0.001f)
	{
		float radiusScaled = radius * planetSizeScale;
		if (radiusScaled > 0.5f)
			radiusScaled = 0.5f;

		glDisable(GL_LIGHTING);
		gluSphere(quadric, radiusScaled, 30, 30);
		glEnable(GL_LIGHTING);
	}
	else
	{
		gluSphere(quadric, radius * planetSizeScale, 30, 30);
	}

	glPopMatrix();
}

//渲染轨道
void Planet::renderOrbit(void)
{
	//line strip
	glBegin(GL_LINE_STRIP);

	//画圆
	for (float angle = 0.0f; angle < 6.283185307f; angle += 0.05f)
	{
		glVertex3f(sin(angle) * distanceFromSun * distanceScale, cos(angle) * distanceFromSun * distanceScale, 0.0f);
	}
	glVertex3f(0.0f, distanceFromSun * distanceScale, 0.0f);

	glEnd();

	glPushMatrix();
	//缩放移动
	glTranslatef(position[0] * distanceScale, position[1] * distanceScale, position[2] * distanceScale);
	// 绘制所有卫星轨道
	for (int i = 0; i < moons.size(); i++)
	{
		moons[i].renderOrbit();
	}
	glPopMatrix();
}

void Planet::getPosition(float *vec)
{
	vec[0] = position[0] * distanceScale;
	vec[1] = position[1] * distanceScale;
	vec[2] = position[2] * distanceScale;
}

//获取半径
float Planet::getRadius(void)
{
	return radius;
}

//添加卫星到队列中
void Planet::addMoon(float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle)
{
	moons.push_back(Moon(distanceFromPlanet, orbitTime, rotationTime, radius, textureHandle));
}