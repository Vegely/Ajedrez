#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>
#include <string>
#include <cmath>

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

struct Rotation
{
	float x, y, angle;
};

/* OVERLOADED OPERATORS */
std::ostream& operator << (std::ostream& out, const Point& obj);
std::ostream& operator << (std::ostream& out, const CRGB& obj);

Point operator * (const Point& lhs, const float rhs);
Point operator * (const float lhs, const Point& rhs);
Point operator / (const Point& lhs, const float rhs);
bool operator == (const Point& lhs, const Point& rhs);
bool operator != (const Point& lhs, const Point& rhs);

class Delay
{
public:
	Delay(void) = delete;

	static bool delay(const float milliseconds);
};

Point getPointFromCoords(char letter, unsigned int number);

void drawLine(const Point& p1, const Point& p2);

#endif
