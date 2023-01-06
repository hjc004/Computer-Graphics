#ifndef RYAN_CAMERA_H
#define RYAN_CAMERA_H

class Camera
{
private:
	// 前进方向向量
	float forwardVec[3];

	// 正右方向向量
	float rightVec[3];

	// 正上方向向量
	float upVec[3];

	// 相机位置坐标
	float position[3];

	// 相机速度
	float cameraSpeed;
	float cameraTurnSpeed;

public:
	Camera(void);
	void transformOrientation(void);
	void transformTranslation(void);
	void pointAt(float *targetVec);
	void forward(void);
	void backward(void);
	void left(void);
	void right(void);
	void rollLeft(void);
	void rollRight(void);
	void pitchUp(void);
	void pitchDown(void);
	void yawLeft(void);
	void yawRight(void);
};

#endif