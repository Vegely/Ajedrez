#ifndef BACKGROUNDS_H
#define BACKGROUNDS_H

#include "Globals.h"
#include "Entity.h"

struct Factor
{
	float x, y;
	Factor(float x, float y) : x(x), y(y) {}
};

template<typename Type>
struct Corners
{
	Type ll, lr, ul, ur;

	Corners(void) : ll(), lr(), ul(), ur() { }

	Corners<Point> operator *= (const Factor& rhs)
	{
		this->ll.x *= rhs.x;
		this->ll.y *= rhs.y;

		this->lr.x *= rhs.x;
		this->lr.y *= rhs.y;

		this->ul.x *= rhs.x;
		this->ul.y *= rhs.y;

		this->ur.x *= rhs.x;
		this->ur.y *= rhs.y;

		return *this;
	}
};

class Plane : public Entity
{
private:
	float x_dim, y_dim;
	Corners<Point> position_corners;

public:
	/* CONSTRUCTOR */
	Plane(void);
	Plane(const std::string& name);
	Plane(const float x_dim, const float y_dim);
	Plane(const float x_dim, const float y_dim, const Point& position, const std::string& name);
	Plane(const Plane& p);
	void updateCorners(void);

	/* GETTERS */
	float getArea(void) const;

	void getCornersPosition(Point* ll, Point* lr, Point* ul, Point* ur);
	Corners<Point> getCornersPosition(void) const;
	Point getCornersPosition(const std::string& which_corner) const;

	/* SETTERS */
	void setDims(const float x, const float y);
	void setPosition(const Point& pos) override;
	void rotate(const char axis, const float angle, const Point& pos);

	/* DRAWING */
	void render(void) override;
};

#endif