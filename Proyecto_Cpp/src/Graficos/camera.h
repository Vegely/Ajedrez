#ifndef CAMERA_H
#define CAMERA_H

#include "structs.h"

class Camera
{
private:
	Point position;
	Point looking_at;
	Rotation rotation;

public:
	Camera(void);

	Camera(const Point& pos, const Point& lookAt);
	Camera(const Point& pos, const Point& lookAt, const Rotation& rot);

	Point getPosition(void) const;
	Point getLookAt(void) const;
	Rotation getRotation(void) const;

	void lookAtTest(void);

	void setPosition(const Point& pos);
	void setRotation(const Rotation& rot);
	void lookAt(const Point& pt);

	void keyboardMove(keypress key, float sensitivity);

	void update(void);

	void animationRotate(float radius, float z, Point lookAt);
};

#endif // !CAMERA_H
