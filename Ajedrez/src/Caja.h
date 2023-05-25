#pragma once
#include "Vector2D.h"

class Caja
{
protected:
	Vector2D ur;
	Vector2D ul;
	Vector2D dr;
	Vector2D dl;
public:
	Caja(Vector2D ur, Vector2D ul, Vector2D dr, Vector2D dl); //u = up, d = down, r = right, l = left
	virtual void dibuja();
};