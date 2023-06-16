#include "Camara.h"
#include <freeglut.h>

/* CONSTRUCTOR */
Camara::Camara(const Point& position) :
	position(position),
	speed({0}),
	look_at{ 0, 0, 0 },
	fov_y(60.0f),
	rotation{0, 0, 1},
	girado(false)
{
	light.position = { 0, 50.0f, 0, 1.0f };
	light.ambient = { 255.0f, 255.0f, 255.0f, 0.1f };
	light.diffuse = { 128.0f ,128.0f ,128.0f ,1.0f };
	light.specular = { 128.0f ,128.0f ,128.0f ,1.0f };

	std::cout << "Initial camera position set to " << this->position << std::endl;
	std::cout << "Initial camera look-at point set to " << this->look_at << std::endl;
}

Camara::Camara(const Point& position, const Point& look_at, float fov_y) :
	position(position),
	speed({0}),
	look_at(look_at),
	fov_y(fov_y),
	rotation{ 0, 0, 1 },
	girado(false)
{
	light.position = { 0.0f, 10.0f, 0.0f, 1.0f };
	light.ambient = { 1.5f, 1.5f, 1.5f, 0.1f };
	light.diffuse = { 1.0f ,1.0f ,1.0f ,1.0f };
	light.specular = { 1.0f ,1.0f ,1.0f ,1.0f };

	std::cout << "Initial camera position set to " << this->position << std::endl;
	std::cout << "Initial camera look-at point set to " << this->look_at << std::endl;
}

/* DESTRUCTOR */
Camara::~Camara(void)
{

}

float* Camara::getLightPos(void) const
{
	float result[4];
	result[0] = this->light.position.x;
	result[1] = this->light.position.y;
	result[2] = this->light.position.z;
	result[3] = this->light.position.positional;

	return result;
}
float* Camara::getLightAmb(void) const
{
	float result[4];
	result[0] = this->light.ambient.r;
	result[1] = this->light.ambient.g;
	result[2] = this->light.ambient.b;
	result[3] = this->light.ambient.alpha;

	return result;
}
float* Camara::getLightDif(void) const
{
	float result[4];
	result[0] = this->light.diffuse.r;
	result[1] = this->light.diffuse.g;
	result[2] = this->light.diffuse.b;
	result[3] = this->light.diffuse.alpha;

	return result;
}
float* Camara::getLightSpe(void) const
{
	float result[4];
	result[0] = this->light.specular.r;
	result[1] = this->light.specular.g;
	result[2] = this->light.specular.b;
	result[3] = this->light.specular.alpha;

	return result;
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

	this->light.position = { this->position.x, this->position.y, this->position.z, 1.0f };

	glRotatef(rotation.x, 1.0, 0.0, 0.0);				 // rotate our camera on the x-axis (left and right)
	glRotatef(rotation.y, 0.0, 1.0, 0.0);				 // rotate our camera on the y-axis (up and down)
	glTranslated(-position.x, -position.y, -position.z); // translate the screen to the position of our camera
}

Point Camara::white_pov = Point{ 0.0f, 20.5f, -15.6f };
Point Camara::black_pov = Point{ 0.0f, 20.5f,  15.6f };