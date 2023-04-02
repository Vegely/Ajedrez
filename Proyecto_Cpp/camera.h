#ifndef CAMERA_H
#define CAMERA_H

#include "structs.h"

class Camera
{
private:
	Point position;
	Point lookAt;
	Rotation rotation;

public:
	Camera(void);

	Point getPosition(void);
	Point getLookAt(void);
	Rotation getRotation(void);

	void setPosition(Point* pos);
	void setRotation(Rotation* rot);

	void keyboardMove(keypress key, float sensitivity);

	void update(void);

	void animationRotate(float radius, float z, Point lookAt);
};

#endif // !CAMERA_H
