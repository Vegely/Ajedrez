#include <iostream>

#include "AsciiGraphics.h"

using namespace std;


#define X_BOARD 8
#define Y_BOARD 8
#define X_SPACING 4
#define Y_SPACING 2
#define X_BACKGROUND 10
#define Y_BACKGROUND 10
#define X "Una mierda"


int main()
{
	//Inicializacion de la pantalla

	Screen scr(30);

	//Carga del tablero en el fondo

	vector<vector<Character>> bg;

	for (int i = 0; i <= X_BACKGROUND * X_SPACING; i++)
	{
		vector<Character> aux;
		for (int j = 0; j <= Y_BACKGROUND * Y_SPACING; j++)
		{
			Character chr;
			if (i >= X_SPACING && i <= (X_BACKGROUND - 1) * X_SPACING && j >= Y_SPACING && j <= (Y_BACKGROUND - 1) * Y_SPACING)
			{
				if (i == X_SPACING)
				{
					if (j == Y_SPACING || j == (Y_BACKGROUND - 1) * Y_SPACING) chr.fill(206);
					else if (j % Y_SPACING == 0) chr.fill(185);
					else chr.fill(186);
				}
				else if (i == (X_BACKGROUND - 1) * X_SPACING)
				{
					if (j == Y_SPACING || j == (Y_BACKGROUND - 1) * Y_SPACING) chr.fill(206);
					else if (j % Y_SPACING == 0) chr.fill(204);
					else chr.fill(186);
				}
				else if (j == Y_SPACING)
				{
					if (i % X_SPACING == 0) chr.fill(202);
					else chr.fill(205);
				}
				else if (j == (Y_BACKGROUND - 1) * Y_SPACING)
				{
					if (i % X_SPACING == 0) chr.fill(203);
					else chr.fill(205);
				}
				else if (i % X_SPACING == 0 && j % Y_SPACING == 0) chr.fill(197);
				else if (i % X_SPACING == 0) chr.fill(179);
				else if (j % Y_SPACING == 0) chr.fill(196);
				else chr.fill(' ');
			}
			else if (i == 0)
			{
				if (j == 0) chr.fill(201);
				else if (j == Y_BACKGROUND * Y_SPACING) chr.fill(200);
				else if (j % Y_SPACING == 0) chr.fill(204);
				else chr.fill(186);
			}
			else if (i == X_BACKGROUND * X_SPACING)
			{
				if (j == 0) chr.fill(187);
				else if (j == Y_BACKGROUND * Y_SPACING) chr.fill(188);
				else if (j % Y_SPACING == 0) chr.fill(185);
				else chr.fill(186);
			}
			else if (j == 0)
			{
				if (i % X_SPACING == 0) chr.fill(203);
				else chr.fill(205);
			}
			else if (j == Y_BACKGROUND * Y_SPACING)
			{
				if (i % X_SPACING == 0) chr.fill(202);
				else chr.fill(205);
			}
			else if (i % X_SPACING != 0 && j % Y_SPACING == 0) chr.fill(205);
			else if (i % X_SPACING == 0 && j % Y_SPACING != 0) chr.fill(186);
			else if ((i == X_SPACING / 2 || i == (X_BACKGROUND - 0.5) * X_SPACING) && j > Y_SPACING && j < (Y_BACKGROUND - 1) * Y_SPACING) chr.fill(49 + X_BACKGROUND - 1 - j / Y_SPACING - 0.5);
			else if (i >= X_SPACING && i <= (X_BACKGROUND - 1) * X_SPACING && i % X_SPACING == 2 && (j == Y_SPACING / 2 || j == (Y_BACKGROUND - 0.5) * Y_SPACING)) chr.fill(65 + i / X_SPACING - 0.5);
			else chr.fill(' ');

			aux.push_back(chr);
		}
		bg.push_back(aux);
	}

	scr.setBackground(bg);

	//Experimentos con el frente

	vector<vector<Character>> fg;

	for (int i = 0; i < 2; i++)
	{
		vector<Character> aux;
		for (int j = 0; j < 3; j++)
		{
			Character chr;
			chr.fill('*');
			aux.push_back(chr);
		}
		fg.push_back(aux);
	}

	scr.foregroundSettings(X_SPACING * 1.5, Y_SPACING * 1.5, X_SPACING, Y_SPACING);

	scr.setForeground(fg);

	scr.printSettings(2, 1);

	scr.print();

	return 0;
}