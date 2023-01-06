#pragma warning(disable : 4996)

#ifdef _WIN32
#include <Windows.h>
#endif
#include <gl\GL.h>
#include <gl\GLU.h>
#include <cmath>
#include "camera.h"

// set
void vectorSet(float *vec, float x, float y, float z)
{
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
}

// 移动
void vectorAdd(float *v1, float *v2)
{
	v1[0] += v2[0];
	v1[1] += v2[1];
	v1[2] += v2[2];
}

// 拷贝
void vectorCopy(float *v1, float *v2)
{
	v1[0] = v2[0];
	v1[1] = v2[1];
	v1[2] = v2[2];
}

//放大缩小
void vectorMul(float *vec, float scalar)
{
	vec[0] *= scalar;
	vec[1] *= scalar;
	vec[2] *= scalar;
}

// 矢量长度
float lengthOfVec(float *vec)
{
	return sqrtf(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
}

// 法向量
void normaliseVec(float *vec)
{
	vectorMul(vec, 1 / lengthOfVec(vec));
}

//从给定的角度和轴生成3x3旋转矩阵，并将指针指向3x3矩阵
void rotationMatrix(float *matrix, float *axis, float angle)
{
	float cos1 = cos(angle);
	float cos2 = 1 - cos1;
	float sin1 = sin(angle);

	matrix[0] = cos1 + axis[0] * axis[0] * cos2;
	matrix[1] = axis[0] * axis[1] * cos2 - axis[2] * sin1;
	matrix[2] = axis[0] * axis[2] * cos2 + axis[1] * sin1;

	matrix[3] = axis[1] * axis[0] * cos2 + axis[2] * sin1;
	matrix[4] = cos1 + axis[1] * axis[1] * cos2;
	matrix[5] = axis[1] * axis[2] * cos2 - axis[0] * sin1;

	matrix[6] = axis[2] * axis[0] * cos2 - axis[1] * sin1;
	matrix[7] = axis[2] * axis[1] * cos2 + axis[0] * sin1;
	matrix[8] = cos1 + axis[2] * axis[2] * cos2;
}

// 将向量v1乘以矩阵，并将结果放入向量v2
void mulVecBy(float *v1, float *matrix, float *v2)
{
	v2[0] = v1[0] * matrix[0] + v1[1] * matrix[1] + v1[2] * matrix[2];
	v2[1] = v1[0] * matrix[3] + v1[1] * matrix[4] + v1[2] * matrix[5];
	v2[2] = v1[0] * matrix[6] + v1[1] * matrix[7] + v1[2] * matrix[8];
}

// 将矢量v1绕轴v2旋转一定角度，并将结果放入v3
void rotateAroundVec(float *v1, float *v2, float angle, float *v3)
{
	float matrix[16];
	rotationMatrix(matrix, v2, angle);

	mulVecBy(v1, matrix, v3);
}

Camera::Camera(void)
{
	cameraSpeed = 0.005f;
	cameraTurnSpeed = 0.01f;
	//设置默认矢量值-获得行星的良好视角
	vectorSet(position, 0.764331460f, -1.66760659f, 0.642456770);
	vectorSet(forwardVec, -0.398769796f, 0.763009906f, -0.508720219f);
	vectorSet(rightVec, 0.886262059f, 0.463184059f, 0.000000000f);
	vectorSet(upVec, -0.235630989f, 0.450859368f, 0.860931039f);
}

//视角设置
void Camera::transformOrientation(void)
{
	gluLookAt(0, 0, 0, forwardVec[0], forwardVec[1], forwardVec[2], upVec[0], upVec[1], upVec[2]);
}

//移动
void Camera::transformTranslation(void)
{
	glTranslatef(-position[0], -position[1], -position[2]);
}

void Camera::pointAt(float *targetVec)
{
	float tempVec[3];
	float up[3] = {0.0f, 0.0f, 1.0f};

	//首先从摄像机位置减去目标位置，得到新的前向矢量
	forwardVec[0] = targetVec[0] - position[0];
	forwardVec[1] = targetVec[1] - position[1];
	forwardVec[2] = targetVec[2] - position[2];

	//归一化
	normaliseVec(forwardVec);

	//为找到正确的向量，绕z轴旋转向量-pi/2
	rotateAroundVec(forwardVec, up, -1.57079632679f, tempVec);

	tempVec[2] = 0;
	normaliseVec(tempVec);
	//拷贝到rightVec
	vectorCopy(rightVec, tempVec);

	//绕rightVec向量旋转向量pi/2
	rotateAroundVec(forwardVec, rightVec, 1.57079632679f, tempVec);
	vectorCopy(upVec, tempVec);
}

//相机前进
void Camera::forward(void)
{
	float vec[3];
	vectorCopy(vec, forwardVec);
	vectorMul(vec, cameraSpeed);

	vectorAdd(position, vec);
}

//相机后退
void Camera::backward(void)
{
	float vec[3];
	vectorCopy(vec, forwardVec);
	vectorMul(vec, -cameraSpeed);

	vectorAdd(position, vec);
}

//相机左移
void Camera::left(void)
{
	float vec[3];
	vectorCopy(vec, rightVec);
	vectorMul(vec, -cameraSpeed);

	vectorAdd(position, vec);
}

//相机右移
void Camera::right(void)
{
	float vec[3];
	vectorCopy(vec, rightVec);
	vectorMul(vec, cameraSpeed);

	vectorAdd(position, vec);
}

// 视角左旋转
void Camera::rollLeft(void)
{
	float tempVec[3];
	rotateAroundVec(upVec, forwardVec, -cameraTurnSpeed, tempVec);
	vectorCopy(upVec, tempVec);

	rotateAroundVec(rightVec, forwardVec, -cameraTurnSpeed, tempVec);
	vectorCopy(rightVec, tempVec);
}

// 视角右旋转
void Camera::rollRight(void)
{
	float tempVec[3];
	rotateAroundVec(upVec, forwardVec, cameraTurnSpeed, tempVec);
	vectorCopy(upVec, tempVec);

	rotateAroundVec(rightVec, forwardVec, cameraTurnSpeed, tempVec);
	vectorCopy(rightVec, tempVec);
}

// 调高
void Camera::pitchUp(void)
{
	float tempVec[3];
	rotateAroundVec(forwardVec, rightVec, cameraTurnSpeed, tempVec);
	vectorCopy(forwardVec, tempVec);

	rotateAroundVec(upVec, rightVec, cameraTurnSpeed, tempVec);
	vectorCopy(upVec, tempVec);
}

// 调低
void Camera::pitchDown(void)
{
	float tempVec[3];
	rotateAroundVec(forwardVec, rightVec, -cameraTurnSpeed, tempVec);
	vectorCopy(forwardVec, tempVec);

	rotateAroundVec(upVec, rightVec, -cameraTurnSpeed, tempVec);
	vectorCopy(upVec, tempVec);
}

// 向左偏航
void Camera::yawLeft(void)
{
	float tempVec[3];
	rotateAroundVec(forwardVec, upVec, cameraTurnSpeed, tempVec);
	vectorCopy(forwardVec, tempVec);

	rotateAroundVec(rightVec, upVec, cameraTurnSpeed, tempVec);
	vectorCopy(rightVec, tempVec);
}

// 向右偏航
void Camera::yawRight(void)
{
	float tempVec[3];
	rotateAroundVec(forwardVec, upVec, -cameraTurnSpeed, tempVec);
	vectorCopy(forwardVec, tempVec);

	rotateAroundVec(rightVec, upVec, -cameraTurnSpeed, tempVec);
	vectorCopy(rightVec, tempVec);
}