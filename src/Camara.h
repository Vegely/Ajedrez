#ifndef CAMERA_H
#define CAMERA_H

#include "Globals.h"

class Camara
{
private:
	Point    position;
	Point    speed;
	Point    acceleration;
	Point    look_at;
	float    angle;
	float    ang_speed;
	float    ang_acc;
	bool     girado;
	Rotation rotation;

public:
	/* CONSTRUCTOR */
	Camara(void) = delete;
	Camara(const Point& position);

	/* DESTRUCTOR */
	virtual ~Camara(void) {}

	/* GETTERS */
	Point  getPosition(void) const { return this->position; }
	Point  getSpeed   (void) const { return this->speed; }
	Point  getLookAt  (void) const { return this->look_at; }
	float  getAngle	  (void) const { return this->angle; }
	bool   getGirado  (void) const { return this->girado; }

	/* SETTERS */
	void setPosition    (const Point pt)  { this->position = pt;}
	void setAngle		(const float f)   { this->angle = f; }
	void setAngSpeed	(const float sp)  { this->ang_speed = sp; }
	void setAcceleration(const Point& ac) { this->acceleration = ac; }
	void setLookAt		(const Point& pt) { this->look_at = pt; }
	void cambiarGirado	(void)			  { this->girado = !this->girado; }

	/* MOVIMIENTO */
	void movement(float time);
	void motion  (float time);

	/* PRINTERS */
	std::ostream& printPosition(std::ostream& str) const;
	std::ostream& printLookAt  (std::ostream& str) const;

	/* FUNCIONES */
	void update(void);

	/* VARIABLES ESTATICAS */
	static Point white_pov;
	static Point black_pov;
	static float radius;
	static float height;
};

#endif // !CAMERA_H