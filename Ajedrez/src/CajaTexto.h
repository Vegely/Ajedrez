#pragma once
#include "Caja.h"
#include <string>


class CajaTexto : public Caja
{
	std::string texto;
public:
	CajaTexto(Vector2D ur, Vector2D ul, Vector2D dr, Vector2D dl, std::string texto) : Caja(ur, ul, dr, dl), texto(texto) {}

	bool click(float x, float y);
	void dibuja() override;
};

