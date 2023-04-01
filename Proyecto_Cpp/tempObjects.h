#ifndef TEMPOBJECTS_H
#define TEMPOBJECTS_H

using byte = unsigned char;

struct Point
{
	float x, y, z;
};

struct Color
{
	byte r, g, b;
};

struct Cell
{
	Point pos_space;
	Color color;
};

class Tablero
{
private:
	Point pos_space;
	Point cell_centers[8][8];
	float square_length;
public:
	/* CONSTRUCTOR */
	Tablero(const Point& pos_space, const float square_length);
	Tablero(const float x, const float y, const float z, const float square_length);


	void calcCellDimensions(void);
	void draw(void);
};

#endif