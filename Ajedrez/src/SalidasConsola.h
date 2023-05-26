#pragma once

#include "MotorDeJuego.h"

class SalidasConsola
{
	static int enRango(int nElem);

public:
	static ConfiguracionDeJuego seleccionarModoDeJuego();

	static void mostrarResultado(const DatosFinal& datosFinal);

	static bool salir();
};