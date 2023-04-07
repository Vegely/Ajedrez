#include "board.h"
#include <iostream>
#include "camera.h"

Board::Board(const Point& pos_global, const float square_length) 
	: pos_global(pos_global)
{
	for (int i = 0; i < 64; i++)
	{
		cells[i].length = square_length;
	}

	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			std::cout << j * 8 + i << std::endl;
			cells[j * 8 + i].pos_space = { square_length * i, pos_global.y, square_length * j };

			if (j % 2 == 0)
			{
				if (i % 2 == 0)
					cells[j * 8 + i].color = CRGB::White;
				else
					cells[j * 8 + i].color = CRGB::Red;
			}
			else
			{
				if (i % 2 == 0)
					cells[j * 8 + i].color = CRGB::Red;
				else
					cells[j * 8 + i].color = CRGB::White;
			}
		}
	}
}

void Board::draw(void)
{
	// Draw the object according to its parameters.
	for (int i = 0; i < 64; i++)
	{
		glColor3ub(cells[i].color.r, cells[i].color.g, cells[i].color.b);
		glTranslatef(cells[i].pos_space.x, cells[i].pos_space.y, cells[i].pos_space.z);
		glutSolidCube(cells[i].length);
		glTranslatef(-cells[i].pos_space.x, -cells[i].pos_space.y, -cells[i].pos_space.z);
	}
}

Point Board::getPosition(void)
{
	return this->pos_global;
}

float Board::getCellLength(void)
{
	return this->cells[0].length;
}


