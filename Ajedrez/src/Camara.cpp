#include "Camara.h"

/* CONSTRUCTOR */
Camara::Camara(const Point& position) :
	position(position),
	look_at{ 0, 0, 0 },
	rotation{0, 0, 1}
{
	std::cout << "Initial camera position set to " << this->position << std::endl;
	std::cout << "Initial camera look-at point set to " << this->look_at << std::endl;
}

Camara::Camara(const Point& position, const Point& look_at) :
	position(position),
	look_at(look_at),
	rotation{ 0, 0, 1 }
{
	std::cout << "Initial camera position set to " << this->position << std::endl;
	std::cout << "Initial camera look-at point set to " << this->look_at << std::endl;
}

/* DESTRUCTOR */
Camara::~Camara(void)
{

}

/* GETTERS */
Point Camara::getPosition(void) const
{
	//std::cout << "Got position " << this->position << "." << std::endl;
	return this->position;
}

Point Camara::getSpeed(void) const
{
	return this->speed;
}

Point Camara::getLookAt(void) const
{
	//std::cout << "Got Look At point " << this->look_at << "." << std::endl;
	return this->look_at;
}

/* SETTERS */
void Camara::setPosition(const Point& pos)
{
	//std::cout << "Position set to " << pos << "." << std::endl;
	this->position = pos;
}

void Camara::setSpeed(const Point& sp)
{
	this->speed = sp;
	std::cout << "Camera speed set to " << this->speed << std::endl;
}

void Camara::setLookAt(const Point& pt)
{
	//std::cout << "Looking at point " << pt << "." << std::endl;
	this->look_at = pt;
}

/* MOVEMENT (OnTimer) */
void Camara::movement(const float time)
{
	this->position = this->position + this->speed * time;
}

/* PRINTERS */
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

/* CAMERA UPDATE */
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