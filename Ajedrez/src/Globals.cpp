#include "Globals.h"
#include <ctime>

CRGB Colors::White = { 255, 255, 255 };
CRGB Colors::Black = { 0, 0, 0 };
CRGB Colors::Red = { 255, 0, 0 };
CRGB Colors::Green = { 0, 255, 0 };
CRGB Colors::Blue = { 0, 0, 255 };
CRGB Colors::Yellow = { 255, 255, 0 };
CRGB Colors::Cyan = { 0, 255, 255 };
CRGB Colors::Magenta = { 255, 0, 255 };

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

Point getPointFromCoords(char letter, unsigned int number)
{
	int first, second;
	switch (letter)
	{
	case 'a':
		first = 0;
		break;
	case 'b':
		first = 1;
		break;
	case 'c':
		first = 2;
		break;
	case 'd':
		first = 3;
		break;
	case 'e':
		first = 4;
		break;
	case 'f':
		first = 5;
		break;
	case 'g':
		first = 6;
		break;
	case 'h':
		first = 7;
		break;
	default:
		std::cerr << "Not a valid coordinate." << std::endl;
		break;
	}
	second = number - 1;

	return Point{ -210.0f + first * 60.0f, 0, -210.0f + second * 60.0f };
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
	float ang = angle * PI / 180;

	this->x = temp.x * cos(ang) - temp.y * sin(ang);
	this->y = temp.x * sin(ang) + temp.y * cos(ang);
}

std::ostream& operator << (std::ostream& out, const Point& obj)
{
	out << "[" << obj.x << ", " << obj.y << ", " << obj.z << "]";
	return out;
}

std::ostream& operator << (std::ostream& out, const CRGB& obj)
{
	out << "[" << static_cast<int>(obj.r) << ", " << static_cast<int>(obj.g) << ", " << static_cast<int>(obj.b) << "]";
	return out;
}

bool Delay::delay(const float milliseconds)
{
	clock_t start_time = clock();

	while (clock() - start_time < 200)
	{
		std::cout << "Clock running for " << milliseconds << " milliseconds." << std::endl;
		return false;
	}
	return true;
}