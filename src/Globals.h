#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>
#include <string>
#include <cmath>
#include "Posicion.h"

constexpr double PI = 3.141592654f;

using byte = unsigned char;

struct CRGB
{
	byte r, g, b;
};

class Colors
{
public:
	static CRGB White;
	static CRGB Black;
	static CRGB Red;
	static CRGB Green;
	static CRGB Blue;
	static CRGB Yellow;
	static CRGB Cyan;
	static CRGB Magenta;
};

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

struct Segmento
{
	Point p1, p2;
};

struct Rotation
{
	float x, y, angle;
};

class CasillasTablero
{
private:
	Posicion casillas_tablero[64];

public:
	CasillasTablero(void)
	{
		for (int i = 0; i < 64; i++)
		{
			casillas_tablero[i].x = i / 8;
			casillas_tablero[i].y = i % 8;
		}
	}

	Posicion operator[](int i) const { return casillas_tablero[i]; }
};

/* OVERLOADED OPERATORS */
std::ostream& operator << (std::ostream& out, const Point& obj);
std::ostream& operator << (std::ostream& out, const CRGB& obj);

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
