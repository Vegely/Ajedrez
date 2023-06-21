#ifndef ENTITY_H
#define ENTITY_H

#include "Globals.h"
#include <string>

class Entity
{
protected:
	Point		position;
	Point		velocity;
	Point		acceleration;
	std::string name;

public:
	/* CONSTRUCTOR */
	Entity(void);
	Entity(const std::string& name);
	Entity(const Point& position, const std::string& name);
	Entity(const Entity& e);

	/* GETTERS */
	Point getPosition(void) const { return this->position; }

	/* SETTERS */
	void setPosition(const Point& pos) { this->position = pos; }

	/* DESTRUCTOR */
	virtual ~Entity(void) { }

	/* MOVIMIENTO */
	virtual void movement(const float time);

	/* RENDERIZACION */
	virtual void render(void) = 0;
};

#endif