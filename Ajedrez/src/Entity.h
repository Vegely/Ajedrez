#ifndef ENTITY_H
#define ENTITY_H

#include "Globals.h"
#include <string>
#include <iostream>
#include "freeglut.h"

class Entity // interface
{
protected:
	Point		position;
	Point		velocity;
	Point		acceleration;
	CRGB		color;
	std::string name;

public:
	/* CONSTRUCTOR */
	Entity(void);
	Entity(const std::string& name);
	Entity(const Point& position, const CRGB& color, const std::string& name);
	Entity(const Entity& e);

	/* DESTRUCTOR */
	virtual ~Entity(void);

	/* GETTERS */
	Point getPosition(void) const;
	void getPosition(Point* pos);
	Point getVelocity(void) const;
	void getVelocity(Point* pos);
	Point getAcceleration(void) const;
	void getAcceleration(Point* pos);

	CRGB getColor(void) const;
	void getColor(CRGB* color);

	std::string getName(void) const;

	/* SETTERS */
	void setPosition(const Point& pt);
	void move(const Point& incr);
	void endMove(int key);
	void warp(const Point& pt);
	void setPosition(const float x, const float y, const float z);
	void setVelocity(const Point& pt);
	void setVelocity(const float x, const float y, const float z);
	void setAcceleration(const Point& pt);
	void setAcceleration(const float x, const float y, const float z);
	void setColor(const CRGB& color);
	void setColor(const byte r, const byte g, const byte b);
	void setName(const std::string& new_name);

	/* MOVEMENT */
	virtual void movement(const float time);

	/* PRINTERS */
	std::ostream& printParameters(std::ostream& str = std::cout) const;
	std::ostream& printParameters(const Entity& e, std::ostream& str = std::cout);
	std::ostream& printPosition(std::ostream& str = std::cout) const;
	std::ostream& printPosition(const Entity& e, std::ostream& str = std::cout);
	std::ostream& printColor(std::ostream& str = std::cout) const;
	std::ostream& printColor(const Entity& e, std::ostream& str = std::cout);
	std::ostream& printVelocity(std::ostream& str = std::cout) const;
	std::ostream& printVelocity(const Entity& e, std::ostream& str = std::cout);
	std::ostream& printAcceleration(std::ostream& str = std::cout) const;
	std::ostream& printAcceleration(const Entity& e, std::ostream& str = std::cout);

	/* RENDERING (Pure virtual) */
	virtual void render(void) = 0;
};

#endif