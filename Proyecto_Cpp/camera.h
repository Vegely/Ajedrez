#ifndef CAMERA_H
#define CAMERA_H

#include "objects.h"

class Camera
{
private:
	Point position;
	Point lookAt;
public:
	Point lastPosition;
	Point currentPosition;
	Rotation rotation;

public:
	Camera(void);

	Point getPosition(void);
	Point getLookAt(void);
	Rotation getRotation(void);

	void setPosition(Point* pos);
	void setRotation(Rotation* rot);

	void update(void);

	void animationRotate(float radius, float z, Point lookAt);
};

#endif // !CAMERA_H
