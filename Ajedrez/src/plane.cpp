#include "plane.h"

Plane::Plane(float xDim, float yDim) :
	xDim(xDim), yDim(yDim),
	positionSpace{ 0, 0, 0 },
	upperRight{ 255, 255, 255 },
	upperLeft{ 255, 255, 255 },
	lowerRight{ 255, 255, 255 },
	lowerLeft{ 255, 255, 255 }
{
	ll.x = -this->xDim / 2 + this->positionSpace.x;
	ll.y = this->yDim / 2 + this->positionSpace.y;
	lr.x = this->xDim / 2 + this->positionSpace.x;
	lr.y = this->yDim / 2 + this->positionSpace.y;
	ul.x = -this->xDim / 2 + this->positionSpace.x;
	ul.y = -this->yDim / 2 + this->positionSpace.y;
	ur.x = this->xDim / 2 + this->positionSpace.x;
	ur.y = -this->yDim / 2 + this->positionSpace.y;
	ll.z = positionSpace.z;
	lr.z = positionSpace.z;
	ul.z = positionSpace.z;
	ur.z = positionSpace.z;
}

Point Plane::getPosition(void)
{
	return this->positionSpace;
}

float Plane::getArea(void)
{
	return this->xDim * this->yDim;
}

void Plane::getCornerPosition(Point* ll, Point* lr, Point* ul, Point* ur)
{
	*ll = this->ll;
	*lr = this->lr;
	*ul = this->ul;
	*ur = this->ur;
}

Point Plane::getCornerPosition(const std::string& which_corner)
{
	if (which_corner == "ll" || which_corner == "lowerLeft")
		return this->ll;
	if (which_corner == "lr" || which_corner == "lowerRight")
		return this->lr;
	if (which_corner == "ul" || which_corner == "upperLeft")
		return this->ul;
	if (which_corner == "ur" || which_corner == "upperRight")
		return this->ur;
}

void Plane::getCornerColor(Color* upperRight, Color* upperLeft, Color* lowerRight, Color* lowerLeft)
{
	*upperRight = this->upperRight;
	*upperLeft = this->upperLeft;
	*lowerRight = this->lowerRight;
	*lowerLeft = this->lowerLeft;
}

Color Plane::getCornerColor(const std::string& which_corner)
{
	if (which_corner == "ll" || which_corner == "lowerLeft")
		return this->lowerLeft;
	if (which_corner == "lr" || which_corner == "lowerRight")
		return this->lowerRight;
	if (which_corner == "ul" || which_corner == "upperLeft")
		return this->upperLeft;
	if (which_corner == "ur" || which_corner == "upperRight")
		return this->upperRight;
}

void Plane::setColor(const Color& upperRight, const Color& upperLeft, const Color& lowerRight, const Color& lowerLeft)
{
	this->upperRight = upperRight;
	this->upperLeft = upperLeft;
	this->lowerRight = lowerRight;
	this->lowerLeft = lowerLeft;
}

void Plane::setPosition(const Point& pos)
{
	this->positionSpace = pos;
}

void Plane::setPosition(const float x, const float y, const float z)
{
	this->positionSpace.x = x;
	this->positionSpace.y = y;
	this->positionSpace.z = z;
}

void Plane::setDims(const float x, const float y)
{
	this->xDim = x;
	this->yDim = y;
}

void Plane::setCorners(const Point& ll, const Point& lr, const Point& ul, const Point& ur)
{
	this->ll = ll;
	this->lr = lr;
	this->ul = ul;
	this->ur = ur;
}

void Plane::draw(void)
{
	glRotatef(90, 1, 0, 0);
	Point ll = { 0, 0, 0 };
	Point lr = { 0, 0, 0 };
	Point ul = { 0, 0, 0 };
	Point ur = { 0, 0, 0 };
	getCornerPosition(&ll, &lr, &ul, &ur);

	glBegin(GL_POLYGON);
	glColor3ub(lowerLeft.r, lowerLeft.g, lowerLeft.b);
	glVertex3f(ll.x, ll.y, ll.z);
	glColor3ub(upperLeft.r, upperLeft.g, upperLeft.b);
	glVertex3f(ul.x, ul.y, ul.z);
	glColor3ub(upperRight.r, upperRight.g, upperRight.b);
	glVertex3f(ur.x, ur.y, ur.z);
	glColor3ub(lowerRight.r, lowerRight.g, lowerRight.b);
	glVertex3f(lr.x, lr.y, lr.z);
	glEnd();
	glRotatef(-90, 1, 0, 0);
}