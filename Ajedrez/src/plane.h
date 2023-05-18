#pragma once

#ifndef BACKGROUNDS_H
#define BACKGROUNDS_H

#include "structs.h"
//#include "freeglut.h"

class Plane
{
private:
	float xDim, yDim;
	Point positionSpace;
	Point ur, ul, lr, ll;
	Color upperRight, upperLeft, lowerRight, lowerLeft;

public:
	/* CONSTRUCTOR */
	Plane(float xDim, float yDim);

	/* GETTERS */
	// Returns the position of the center of the plane.
	Point getPosition(void);
	// Returns the area of the plane.
	float getArea(void);
	// Returns a selected corner.
	void getCornerPosition(Point* ll, Point* lr, Point* ul, Point* ur);
	// Accepts "ur" and "upperRight" conventions.
	Point getCornerPosition(const std::string& which_corner);
	// Gets RGB color for each corner and assign it to the pointers it is passed to it.
	void getCornerColor(Color* upperRight, Color* upperLeft, Color* lowerRight, Color* lowerLeft);
	// Accepts "ur" and "upperRight" conventions.
	Color getCornerColor(const std::string& which_corner);

	/* SETTERS */
	// Sets values to the plane color parameters to be used in the drawing function.
	// @param upperRight sets the upper right corner to that color.
	// @param upperLeft sets the upper left corner to that color.
	// @param lowerRight sets the lower right corner to that color.
	// @param lowerLeft sets the lower left corner to that color.
	void setColor(const Color& upperRight, const Color& upperLeft, const Color& lowerRight, const Color& lowerLeft);
	// Sets a position to the center of the plane. Admits Point type and independent x, y and z values.
	void setPosition(const Point& pos);
	void setPosition(const float x, const float y, const float z);
	void setDims(const float x, const float y);
	void setCorners(const Point& ll, const Point& lr, const Point& ul, const Point& ur);

	void draw(void);
};

#endif
