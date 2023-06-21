#define _USE_MATH_DEFINES
#include "Globals.h"
#include <cmath>
#include <freeglut.h>

Point Point::zero = { 0, 0, 0 };

Point Point::operator + (const Point& rhs)
{
	Point result;
	result.x = this->x + rhs.x;
	result.y = this->y + rhs.y;
	result.z = this->z + rhs.z;
	return result;
}

Point Point::operator - (const Point& rhs)
{
	Point result;
	result.x = this->x - rhs.x;
	result.y = this->y - rhs.y;
	result.z = this->z - rhs.z;
	return result;
}

Point Point::operator += (const Point& rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
	this->z += rhs.z;
	return *this;
}

Point operator * (const Point& lhs, const float rhs)
{
	Point result;
	result.x = lhs.x * rhs;
	result.y = lhs.y * rhs;
	result.z = lhs.z * rhs;
	return result;
}

Point operator * (const float lhs, const Point& rhs)
{
	Point result;
	result.x = rhs.x * lhs;
	result.y = rhs.y * lhs;
	result.z = rhs.z * lhs;
	return result;
}

Point operator / (const Point& lhs, const float rhs)
{
	Point result;
	result.x = lhs.x / rhs;
	result.y = lhs.y / rhs;
	result.z = lhs.z / rhs;
	return result;
}

Point getPointFromCoords(unsigned int letter, unsigned int number)
{
	return Point{ -17.5f + (letter) * 5.0f, 0, -17.5f + (number) * 5.0f };
}

Point getPointFromCoords(const Posicion& pos)
{
	Point result;
	result.x = -(-17.5f + (pos.x) * 5.0f);
	result.y = 0.0f;
	result.z = -17.5f + (pos.y) * 5.0f;
	return result;
}

bool operator == (const Point& lhs, const Point& rhs)
{
	if (lhs.x == rhs.x &&
		lhs.y == rhs.y &&
		lhs.z == rhs.z)
		return true;
	else
		return false;
}

bool operator != (const Point& lhs, const Point& rhs)
{
	return !(lhs == rhs);
}

void Point::rotate2D(const float angle)
{
	Point temp = { x, y };
	float ang = angle * M_PI / 180;

	this->x = temp.x * cos(ang) - temp.y * sin(ang);
	this->y = temp.x * sin(ang) + temp.y * cos(ang);
}

std::ostream& operator << (std::ostream& out, const Point& obj)
{
	out << "[" << obj.x << ", " << obj.y << ", " << obj.z << "]";
	return out;
}

void drawLine(const Point& p1, const Point& p2)
{
	glBegin(GL_LINES);
	glVertex3f(p1.x, p1.y, p1.z);
	glVertex3f(p2.x, p2.y, p2.z);
	glEnd();
}

float distanciaPuntos(const Point& p1, const Point& p2)
{
	float dist_x = p1.x - p2.x;
	float dist_y = p1.y - p2.y;
	float dist_z = p1.z - p2.z;
	return sqrtf(dist_x * dist_x + dist_y * dist_y + dist_z * dist_z);
}