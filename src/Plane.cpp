#define _USE_MATH_DEFINES

#include "Plane.h"
#include <freeglut.h>
#include <cmath>

Plane::Plane(void) :
	x_dim(0), y_dim(0),
	position_corners(),
	Entity()
{
	updateCorners();
}

Plane::Plane(const std::string& name) :
	x_dim(0), y_dim(0),
	position_corners(),
	Entity(name)
{
	updateCorners();
}

Plane::Plane(const float x_dim, const float y_dim) :
	Entity("Plane"),
	x_dim(x_dim), y_dim(y_dim)
{
	updateCorners();
}

Plane::Plane(const float x_dim, const float y_dim, const Point& position, const std::string& name) :
	Entity(position, name),
	x_dim(x_dim), y_dim(y_dim)
{
	updateCorners();
}

Plane::Plane(const Plane& p) :
	Entity(p.name),
	x_dim(p.x_dim),
	y_dim(p.y_dim),
	position_corners(p.position_corners)
{
	// No corner update to preserve rotation.
}

void Plane::updateCorners(void)
{
	position_corners.ll.x = position.x - x_dim / 2;
	position_corners.ll.z = position.z - y_dim / 2;
	position_corners.ll.y = position.y;

	position_corners.lr.x = position.x + x_dim / 2;
	position_corners.lr.z = position.z - y_dim / 2;
	position_corners.lr.y = position.y;

	position_corners.ul.x = position.x - x_dim / 2;
	position_corners.ul.z = position.z + y_dim / 2;
	position_corners.ul.y = position.y;

	position_corners.ur.x = position.x + x_dim / 2;
	position_corners.ur.z = position.z + y_dim / 2;
	position_corners.ur.y = position.y;
}

float Plane::getArea(void) const
{
	return this->x_dim * this->y_dim;
}

void Plane::getCornersPosition(Point* ll, Point* lr, Point* ul, Point* ur)
{
	*ll = this->position_corners.ll;
	*ul = this->position_corners.ul;
	*lr = this->position_corners.lr;
	*ur = this->position_corners.ur;
}

Corners<Point> Plane::getCornersPosition(void) const
{
	return this->position_corners;
}

Point Plane::getCornersPosition(const std::string& which_corner) const
{
	if (which_corner == "ll")
	{
		return this->position_corners.ll;
	}
	else if (which_corner == "ul")
	{
		return this->position_corners.ul;
	}
	else if (which_corner == "lr")
	{
		return this->position_corners.lr;
	}
	else if (which_corner == "ur")
	{
		return this->position_corners.ur;
	}
}

void Plane::setDims(const float x, const float y)
{
	this->x_dim = x;
	this->y_dim = y;

	updateCorners();
}

void Plane::setPosition(const Point& pos)
{
	Entity::setPosition(pos);
	this->position_corners.ll += pos;
	this->position_corners.lr += pos;
	this->position_corners.ul += pos;
	this->position_corners.ur += pos;
}

void Plane::rotate(const char axis, const float angle, const Point& pos)
{
	float ang = angle * M_PI / 180;
	Corners<Point> temp_corners = position_corners;

	switch (axis)
	{
	case 'x':
		position_corners.ll.y = pos.y - (temp_corners.ll.z - pos.z) * sin(ang) + (temp_corners.ll.y - pos.y) * cos(ang);
		position_corners.lr.y = pos.y - (temp_corners.lr.z - pos.z) * sin(ang) + (temp_corners.lr.y - pos.y) * cos(ang);
		position_corners.ul.y = pos.y - (temp_corners.ul.z - pos.z) * sin(ang) + (temp_corners.ul.y - pos.y) * cos(ang);
		position_corners.ur.y = pos.y - (temp_corners.ur.z - pos.z) * sin(ang) + (temp_corners.ur.y - pos.y) * cos(ang);

		position_corners.ll.z = pos.z + (temp_corners.ll.z - pos.z) * cos(ang) + (temp_corners.ll.y - pos.y) * sin(ang);
		position_corners.lr.z = pos.z + (temp_corners.lr.z - pos.z) * cos(ang) + (temp_corners.lr.y - pos.y) * sin(ang);
		position_corners.ul.z = pos.z + (temp_corners.ul.z - pos.z) * cos(ang) + (temp_corners.ul.y - pos.y) * sin(ang);
		position_corners.ur.z = pos.z + (temp_corners.ur.z - pos.z) * cos(ang) + (temp_corners.ur.y - pos.y) * sin(ang);

		break;

	case 'y':
		position_corners.ll.x = pos.x + (temp_corners.ll.x - pos.x) * cos(ang) + (temp_corners.ll.z - pos.z) * sin(ang);
		position_corners.lr.x = pos.x + (temp_corners.lr.x - pos.x) * cos(ang) + (temp_corners.lr.z - pos.z) * sin(ang);
		position_corners.ul.x = pos.x + (temp_corners.ul.x - pos.x) * cos(ang) + (temp_corners.ul.z - pos.z) * sin(ang);
		position_corners.ur.x = pos.x + (temp_corners.ur.x - pos.x) * cos(ang) + (temp_corners.ur.z - pos.z) * sin(ang);

		position_corners.ll.z = pos.z + (temp_corners.ll.z - pos.z) * cos(ang) - (temp_corners.ll.x - pos.x) * sin(ang);
		position_corners.lr.z = pos.z + (temp_corners.lr.z - pos.z) * cos(ang) - (temp_corners.lr.x - pos.x) * sin(ang);
		position_corners.ul.z = pos.z + (temp_corners.ul.z - pos.z) * cos(ang) - (temp_corners.ul.x - pos.x) * sin(ang);
		position_corners.ur.z = pos.z + (temp_corners.ur.z - pos.z) * cos(ang) - (temp_corners.ur.x - pos.x) * sin(ang);

		break;

	case 'z':
		position_corners.ll.x = pos.x + (temp_corners.ll.x - pos.x) * cos(ang) - (temp_corners.ll.y - pos.y) * sin(ang);
		position_corners.lr.x = pos.x + (temp_corners.lr.x - pos.x) * cos(ang) - (temp_corners.lr.y - pos.y) * sin(ang);
		position_corners.ul.x = pos.x + (temp_corners.ul.x - pos.x) * cos(ang) - (temp_corners.ul.y - pos.y) * sin(ang);
		position_corners.ur.x = pos.x + (temp_corners.ur.x - pos.x) * cos(ang) - (temp_corners.ur.y - pos.y) * sin(ang);

		position_corners.ll.y = pos.y + (temp_corners.ll.x - pos.x) * sin(ang) + (temp_corners.ll.y - pos.y) * cos(ang);
		position_corners.lr.y = pos.y + (temp_corners.lr.x - pos.x) * sin(ang) + (temp_corners.lr.y - pos.y) * cos(ang);
		position_corners.ul.y = pos.y + (temp_corners.ul.x - pos.x) * sin(ang) + (temp_corners.ul.y - pos.y) * cos(ang);
		position_corners.ur.y = pos.y + (temp_corners.ur.x - pos.x) * sin(ang) + (temp_corners.ur.y - pos.y) * cos(ang);

		break;

	default:
		std::cout << "No rotation defined for the selected axis." << std::endl << std::endl;
		break;
	}
}

std::ostream& Plane::printCorners(std::ostream& out) const
{
	out << "Corners for plane " << this->name << ":" << std::endl;
	out << "Lower left:  " << this->position_corners.ll << std::endl;
	out << "Lower right: " << this->position_corners.lr << std::endl;
	out << "Upper left:  " << this->position_corners.ul << std::endl;
	out << "Upper right: " << this->position_corners.ur << std::endl << std::endl;

	return out;
}

void Plane::render(void)
{
	drawLine(position_corners.ll, position_corners.lr);
	drawLine(position_corners.lr, position_corners.ur);
	drawLine(position_corners.ur, position_corners.ul);
	drawLine(position_corners.ul, position_corners.ll);
}