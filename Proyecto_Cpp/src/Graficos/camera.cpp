#include "camera.h"
#include "freeglut.h"

#define PI 3.141592654f

// Constructor.
Camera::Camera(void) 
	: position{ -5, 10, -5 }, looking_at{ 0, 0, 0 }, rotation{ 0, 0, 1 } { }

Camera::Camera(const Point& pos, const Point& lookAt) 
	: position(pos), looking_at(lookAt), rotation{ 0, 0, 1 } { }

Camera::Camera(const Point& pos, const Point& lookAt, const Rotation& rot)
	: position(pos), looking_at(lookAt), rotation(rot) { }

Point Camera::getPosition(void) const
{
	return this->position;
}

Point Camera::getLookAt(void) const
{
	return this->looking_at;
}

Rotation Camera::getRotation(void) const
{
	return this->rotation;
}

void Camera::setPosition(const Point& pos)
{
	this->position = pos;
}

void Camera::setRotation(const Rotation& rot)
{
	this->rotation = rot;
}

void Camera::lookAt(const Point& pt)
{
	this->looking_at = pt;
}

void Camera::lookAtTest(void)
{
	glColor3ub(CRGB::Green.r, CRGB::Green.g, CRGB::Green.b);
	glTranslatef(looking_at.x, looking_at.y, looking_at.z);
	//glTranslatef(0,0,0);
	glutSolidSphere(1.0, 50, 50);
	glTranslatef(-looking_at.x, -looking_at.y, -looking_at.z);
}

void Camera::update(void)
{
	// Clears screen.	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Defines a point of view.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt
	(
		position.x, position.y, position.z,	   // Camera position.
		looking_at.x, looking_at.y, looking_at.z, // Point to look at.
		0.0, 1.0, 0.0						   // Define Y axis direction to up.
	);

	glRotatef(rotation.x, 1.0, 0.0, 0.0);				 // rotate our camera on the x-axis (left and right)
	glRotatef(rotation.y, 0.0, 1.0, 0.0);				 // rotate our camera on the y-axis (up and down)
	//glTranslated(-position.x, -position.y, -position.z); // translate the screen to the position of our camera
}

void Camera::animationRotate(float radius, float z, Point lookAt)
{
	static float ang = atan(position.y / position.x);
	std::cout << ang << std::endl;

	ang += 0.01;
	if (ang > 2 * PI - 0.01)
		ang = 0;

	this->looking_at = lookAt;

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