 #include <iostream>
#include <windows.h>

#include "AsciiGraphics.h"


using namespace std;


void Character::fill(char ch, unsigned int fC, unsigned int bC)
{
	chr = ch;
	foregroundColor = fC;
	backgroundColor = bC;
}


Screen::Screen(unsigned int scrHeight)
{
	screenHeight = scrHeight;
}


void Screen::setBackground(vector<vector<Character>> background)
{
	bg = background;
}


void Screen::foregroundSettings(unsigned int xCoord, unsigned int yCoord, unsigned int horizontalSpaceBetweenCharactersInForeground, unsigned int verticalSpaceBetweenCharactersInForeground)
{
	xForeground = xCoord;
	yForeground = yCoord;
	xSpaceing = horizontalSpaceBetweenCharactersInForeground;
	ySpaceing = verticalSpaceBetweenCharactersInForeground;
}


void Screen::setForeground(vector<vector<Character>> foreground)
{
	canvas = bg;

	for (int i = 0; i < foreground.size(); i++)
	{
		for (int j = 0; j < foreground[0].size(); j++)
		{
			canvas[xSpaceing * i + xForeground][ySpaceing * j + yForeground] = foreground[i][j];
		}
	}
}


void Screen::printSettings(int xCoord, int yCoord)
{
	xPrint = xCoord;
	yPrint = yCoord;
}
void Screen::print()
{
	unsigned int backgroundColor = 0, foregroundColor = 7;
	
	for (int j = 0; j < yPrint; j++)
	{
		cout << endl;
	}

	for (int j = 0; j < canvas[0].size(); j++)
	{
		for (int i = 0; i < xPrint; i++)
		{
			cout << ' ';
		}

		for (int i = 0; i < canvas.size(); i++)
		{
			if (canvas[i][j].backgroundColor != backgroundColor || canvas[i][j].foregroundColor != foregroundColor)
			{
				HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

				if (canvas[i][j].backgroundColor != backgroundColor) backgroundColor = canvas[i][j].backgroundColor;
				if (canvas[i][j].foregroundColor != foregroundColor) foregroundColor = canvas[i][j].foregroundColor;
				
				SetConsoleTextAttribute(hStdout, backgroundColor*16+foregroundColor);
			}
			cout << canvas[i][j].chr;
		}

		cout << endl;
	}

	for (int i = 4; i < screenHeight - canvas[0].size(); i++)
	{
		cout << endl;
	}
}