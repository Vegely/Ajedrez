#include "tempObjects.h"

Tablero::Tablero(const Point& pos_space, const float square_length) 
	: pos_space(pos_space), square_length(square_length) 
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cell_centers[i][j] = { i * square_length, j * square_length, pos_space.z };
		}
	}
}

Tablero::Tablero(const float x, const float y, const float z, const float square_length)
	: pos_space({x, y, z}), square_length(square_length)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cell_centers[i][j] = { i * square_length, j * square_length, pos_space.z };
		}
	}
}


