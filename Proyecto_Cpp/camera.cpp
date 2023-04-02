#include "camera.h"
#include "freeglut.h"
#include <cmath>
#include <iostream>

#define PI 3.141592654f

// Constructor.
Camera::Camera(void) :
	position{ -5, 10, -5 },
	lookAt{ 0, 0, 0 },
	rotation{ 0, 0, 1 } {}

Point Camera::getPosition(void)
{
	return this->position;
}

Point Camera::getLookAt(void)
{
	return this->lookAt;
}

Rotation Camera::getRotation(void)
{
	return this->rotation;
}

void Camera::setPosition(Point* pos)
{
	this->position.x = pos->x;
	this->position.y = pos->y;
	this->position.z = pos->z;
}

void Camera::setRotation(Rotation* rot)
{
	this->rotation.x = rot->x;
	this->rotation.y = rot->y;
	this->rotation.angle = rot->angle;
}

void Camera::update(void)
{
	Point position = getPosition();
	Point lookAt = getLookAt();

	// Clears screen.	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Defines a point of view.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt
	(
		position.x, position.y, position.z,	// Camera position.
		lookAt.x, lookAt.y, lookAt.z,		// Point to look at.
		0.0, 1.0, 0.0						// Define Y axis direction to up.
	);

	glRotatef(rotation.x, 1.0, 0.0, 0.0);				 // rotate our camera on the x-axis (left and right)
	glRotatef(rotation.y, 0.0, 1.0, 0.0);				 // rotate our camera on the y-axis (up and down)
	glTranslated(-position.x, -position.y, -position.z); // translate the screen to the position of our camera
}

void Camera::animationRotate(float radius, float z, Point lookAt)
{
	static float ang = atan(position.y / position.x);
	std::cout << ang << std::endl;

	ang += 0.01;
	if (ang > 2 * PI - 0.01)
		ang = 0;

	this->lookAt = lookAt;

	position = { radius * cos(ang), z, radius * sin(ang) };
}

void Camera::keyboardMove(keypress key, float sensitivity)
{
	switch (key)
	{
	case 'w':
		position.z += sensitivity;
		break;
	case 'a':
		position.x -= sensitivity;
		break;
	case 's':
		position.z -= sensitivity;
		break;
	case 'd':
		position.x += sensitivity;
		break;
	default:
		break;
	}
}