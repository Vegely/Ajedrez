#ifndef BACKGROUNDS_H
#define BACKGROUNDS_H

#include "Globals.h"
#include "Entity.h"

template<typename Type>
struct Corners
{
	Type ll, lr, ul, ur;
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
	virtual ~Plane(void);
	void updateCorners(void);

	/* GETTERS */
	float getArea(void) const;

	void getCornersPosition(Point* ll, Point* lr, Point* ul, Point* ur);
	Corners<Point> getCornersPosition(void) const;
	Point getCornersPosition(const std::string& which_corner) const;

	/* SETTERS */
	void setColor(const CRGB& ur, const CRGB& ul, const CRGB& lr, const CRGB& ll);
	void setDims(const float x, const float y);
	void rotate(const char axis, const float angle);

	/* OVERLOADED SETTERS */
	void setPosition(const Point& pt);
	void move(const Point& incr);

	/* PRINTERS */
	std::ostream& printCorners(std::ostream& out = std::cout) const;

	/* DRAWING */
	void render(void) override;
};

#endif