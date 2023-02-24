#ifndef _AsciiGraph_
#define _AsciiGraph_


#include <vector>


using namespace std;


#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define GRAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_CYAN 11
#define LIGHT_RED 12
#define LIGHT_PURPLE 13
#define LIGHT_YELLOW 14
#define BRIGHT_WHITE 15


class Character
{
public:
	char chr, foregroundColor, backgroundColor;

	void fill(char ch, unsigned int fC = 7, unsigned int bC = 0);
};
	
class Screen
{
private:
	unsigned int screenHeight, xForeground = 0, yForeground = 0, xSpaceing = 1, ySpaceing = 1, xPrint = 0, yPrint = 0;

	vector<vector<Character>> canvas, bg;

public:
	Screen(unsigned int scrHeight);

	void setBackground(vector<vector<Character>> background);

	void foregroundSettings(unsigned int xCoord = 0, unsigned int yCoord = 0, unsigned int horizontalSpaceBetweenCharactersInForeground = 1, unsigned int verticalSpaceBetweenCharactersInForeground = 1);

	void setForeground(vector<vector<Character>> foreground);
	
	void printSettings(int xCoord = 0, int yCoord = 0); 

	void print();
};


#endif
