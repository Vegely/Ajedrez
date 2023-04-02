#pragma once

using byte = unsigned char;
using keypress = unsigned char;

struct Point
{
	float x, y, z;
};

struct Color
{
	byte r, g, b;
};

struct Rotation
{
	float x, y, angle;
};

class CRGB
{
public:
	static Color White;
	static Color Black;
	static Color Red;
	static Color Green;
	static Color Blue;
	static Color Yellow;
	static Color Cyan;
	static Color Magenta;

	CRGB() = delete;
};