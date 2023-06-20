#ifndef CAMERA_H
#define CAMERA_H

#include "Globals.h"

class Camara
{
private:
	Point position;
	Point speed;
	Point acceleration;
	Point look_at;
	float angle;
	float ang_speed;
	float ang_acc;
	Rotation rotation;
	bool girado;

public:
	static Point white_pov;
	static Point black_pov;
	static float radius;
	static float height;

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
	void setPosition(const Point& pos) { this->position = pos; }
	void setSpeed   (const Point& sp) { this->speed = sp; }
	void setAngle(const float f) { this->angle = f; }
	void setAngSpeed(const float sp) { this->ang_speed = sp; }
	void setAcceleration(const Point& ac) { this->acceleration = ac; }
	void setLookAt  (const Point& pt) { this->look_at = pt; }
	void cambiarGirado(void) { this->girado = !this->girado; }

	/* MOVEMENT (OnTimer) */
	void movement(const Point& p1, const Point& p2, float time);
	void motion(float time)
	{
		this->speed = this->speed + this->acceleration * time;
		this->angle = this->angle + this->ang_speed * time + 0.5f * this->ang_acc * time * time;
		this->position = Point{ Camara::radius * cos(this->angle), Camara::height, Camara::radius * sin(this->angle) };
		//std::cout << "Angle: " << angle << std::endl;
	}

	/* PRINTERS */
	std::ostream& printPosition(std::ostream& str) const;
	std::ostream& printLookAt  (std::ostream& str) const;

	/* CAMERA UPDATE (for resetting and adjusting camera position and/or rotation) */
	void update(void);
};

#endif // !CAMERA_H