#ifndef TEMPOBJECTS_H
#define TEMPOBJECTS_H

#include "freeglut.h"
#include "structs.h"

struct Cell
{
	Point pos_space;
	Color color;
	float length;
};

class Board
{
private:
	Point pos_global;
	Cell cells[64];
public:
	/* CONSTRUCTOR */
	Board(const Point& pos_global, const float square_length);

	/* GETTERS */
	Point getPosition(void);
	float getCellLength(void);

	/* DRAWING FUNCTIONS */
	void draw(void);
};

#endif