#ifndef CAMERA_H
#define CAMERA_H

#include "Globals.h"

struct LightPos
{
	float x, y, z, positional;
};

struct LightCol
{
	float r, g, b, alpha;
};

struct Light
{
	LightPos position;
	LightCol ambient;
	LightCol diffuse;
	LightCol specular;
};

class Camara
{
private:
	Point position;
	Point speed;
	Point look_at;
	Light light;
	float fov_y;
	Rotation rotation;
	bool girado;

public:
	static Point white_pov;
	static Point black_pov;

	/* CONSTRUCTOR */
	Camara(void) = delete;
	Camara(const Point& position);
	Camara(const Point& position, const Point& look_at, const float fov_y);

	/* DESTRUCTOR */
	virtual ~Camara(void);

	/* GETTERS */
	Point  getPosition(void) const { return this->position; }
	Point  getSpeed   (void) const { return this->speed; }
	Point  getLookAt  (void) const { return this->look_at; }
	Light  getLightRaw(void) const { return this->light; }
	float  getFovY	  (void) const { return this->fov_y; }
	float* getLightPos(void) const;
	float* getLightAmb(void) const;
	float* getLightDif(void) const;
	float* getLightSpe(void) const;
	bool   getGirado(void) const { return this->girado; }

	/* SETTERS */
	void setPosition(const Point& pos);
	void setSpeed   (const Point& sp);
	void setLookAt  (const Point& pt);
	void setLight   (const Light& lt) { this->light = lt; }
	void cambiarGirado(void) { this->girado = !this->girado; }

	/* MOVEMENT (OnTimer) */
	void movement(const float time);

	/* PRINTERS */
	std::ostream& printPosition(std::ostream& str) const;
	std::ostream& printLookAt  (std::ostream& str) const;

	/* CAMERA UPDATE (for resetting and adjusting camera position and/or rotation) */
	void update(void);
};

#endif // !CAMERA_H