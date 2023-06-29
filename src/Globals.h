#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>
#include <cmath>
#include "Posicion.h"

class Point
{
public:
	float x, y, z;
	Point operator + (const Point& rhs);
	Point operator += (const Point& rhs);
	Point operator - (const Point& rhs);
	void rotate2D(const float angle);
	static Point zero;
};

struct Rotation
{
	float x, y, angle;
};

/* OVERLOADED OPERATORS */
Point operator * (const Point& lhs, const float rhs);
Point operator * (const float lhs, const Point& rhs);
Point operator / (const Point& lhs, const float rhs);
bool operator == (const Point& lhs, const Point& rhs);
bool operator != (const Point& lhs, const Point& rhs);

Point getPointFromCoords(unsigned int letter, unsigned int number);
Point getPointFromCoords(const Posicion& pos);

void drawLine(const Point& p1, const Point& p2);

float distanciaPuntos(const Point& p1, const Point& p2);

#endif
