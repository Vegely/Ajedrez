#pragma once
#include "Caja.h"
#include <string>

#define ANCHO_GL 35.0 //25 hasta -10
#define ALTO_GL 63.2 //-31.6 hasta 31.6
#define MAX_IZQD_GL -31.6
#define MAX_ARRIBA_GL 25

class CajaTexto : public Caja
{
	std::string texto;
public:
	CajaTexto(Vector2D ur, Vector2D ul, Vector2D dr, Vector2D dl, std::string texto) : Caja(ur, ul, dr, dl), texto(texto) {}

	bool click(float x, float y);
	void dibuja() override;
};

