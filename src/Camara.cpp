#define _USE_MATH_DEFINES
#include "Camara.h"
#include <freeglut.h>

#include <cmath>

constexpr int SPEED = 500;

Camara::Camara(const Point& position) :
	position(position),
	speed({0}),
	acceleration({0}),
	look_at{ 0, 0, 0 },
	angle(-M_PI_2),
	ang_speed(0.0f),
	ang_acc(0.0f),
	rotation{0, 0, 1},
	girado(false)
{

}

void Camara::movement(float time)
{
	if (!girado)
	{
		if (this->angle + (SPEED * time) < (M_PI_2))
			this->setAngSpeed(SPEED);
		else
		{
			this->setAngSpeed(0.0f);
			this->setAngle(M_PI_2);
		}
	}
	if (girado)
	{
		if (this->angle + (-SPEED * time) > (-M_PI_2))
			this->setAngSpeed(-SPEED);
		else
		{
			this->setAngSpeed(0.0f);
			this->setAngle(-M_PI_2);
		}
	}
}

void Camara::motion(float time)
{
	this->speed = this->speed + this->acceleration * time;
	this->angle = this->angle + this->ang_speed * time + 0.5f * this->ang_acc * time * time;
	this->position = Point{ Camara::radius * cos(this->angle), Camara::height, Camara::radius * sin(this->angle) };
}

std::ostream& Camara::printPosition(std::ostream& str) const
{
	str << "Camera position:" << this->getPosition() << std::endl;
	return str;
}

std::ostream& Camara::printLookAt(std::ostream& str) const
{
	str << "Looking at point " << this->getLookAt() << std::endl;
	return str;
}

void Camara::update(void)
{ 
	// Clears screen.	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Defines a point of view.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt
	(
		position.x, position.y, position.z,	// Camera position.
		look_at.x, look_at.y, look_at.z,		// Point to look at.
		0.0, 1.0, 0.0						// Define Y axis direction to up.
	);

	glRotatef(rotation.x, 1.0, 0.0, 0.0);				 // rotate our camera on the x-axis (left and right)
	glRotatef(rotation.y, 0.0, 1.0, 0.0);				 // rotate our camera on the y-axis (up and down)
	glTranslated(-position.x, -position.y, -position.z); // translate the screen to the position of our camera
}

float Camara::radius = 15.6f;
float Camara::height = 20.5f;
Point Camara::white_pov = Point{ 0.0f, Camara::height, -Camara::radius };
Point Camara::black_pov = Point{ 0.0f, Camara::height,  Camara::radius };