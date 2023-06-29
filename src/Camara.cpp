#define _USE_MATH_DEFINES
#include "Camara.h"
#include <cmath>

constexpr int SPEED = 1;

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
	if (activar_movimiento)
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
}

void Camara::motion(float time)
{
	this->speed = this->speed + this->acceleration * time;
	this->angle = this->angle + this->ang_speed * time + 0.5f * this->ang_acc * time * time;
	this->position = Point{ Camara::radius * cos(this->angle), Camara::height, Camara::radius * sin(this->angle) };
}

void Camara::update(void)
{ 
	// Limpia los buffers.	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Define un punto de vista.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt
	(
		position.x, position.y, position.z,	// Camera position.
		 look_at.x,  look_at.y,  look_at.z,	// Point to look at.
		       0.0,        1.0,        0.0	// Define Y axis direction to up.
	);

	// Aplica propiedades a la iluminacion (puntual).
	glLightfv(GL_LIGHT0, GL_POSITION, Camara::light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT,  Camara::light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  Camara::light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Camara::light_specular);

	// Activa la iluminacion en caso de estar desactivada.
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glRotatef(rotation.x, 1.0, 0.0, 0.0);				 // rotate our camera on the x-axis (left and right)
	glRotatef(rotation.y, 0.0, 1.0, 0.0);				 // rotate our camera on the y-axis (up and down)
	glTranslated(-position.x, -position.y, -position.z); // translate the screen to the position of our camera
}

float Camara::radius = 15.6f;
float Camara::height = 20.5f;
float Camara::phi = atanf(Camara::height / Camara::radius) * 180.0f / M_PI;
Point Camara::white_pov = Point{ 0.0f, Camara::height, -Camara::radius };
Point Camara::black_pov = Point{ 0.0f, Camara::height,  Camara::radius };

GLfloat Camara::light_position[] = { 0.0f, 1.0f, 0.0f, 1.0f };
GLfloat Camara::light_ambient [] = { 2.0f, 2.0f, 2.0f, 1.0f };
GLfloat Camara::light_diffuse [] = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat Camara::light_specular[] = { 0.7f, 0.7f, 0.7f, 1.0f };