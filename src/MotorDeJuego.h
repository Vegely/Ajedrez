#pragma once

#include "Tablero.h"
#include "Mundo.h"
#include "IA.h";
#include "ConfiguracionDeJuego.h"

enum class CodigoFinal { JAQUE_MATE, REY_AHOGADO, TABLAS_POR_MATERIAL_INSUFICIENTE, TABLAS_POR_REPETICION, TABLAS_POR_PASIVIDAD };	

struct DatosFinal
{
	CodigoFinal codigoFinal;
	bool ganaBlanco;
};

class MotorDeJuego
{
	const ConfiguracionDeJuego config;
	
	Tablero tablero;

	void pintar(Posicion piezaSelec = Posicion(-1, -1)) const;

	Movimiento seleccionarEntrada(bool pos1Selec) const;
	Movimiento ensamblarMovimiento(Posicion posicion, bool pos1Selec) const;
	
public:
	MotorDeJuego(const ConfiguracionDeJuego& config) : config(config), tablero(Tablero(true)) { pintar(); }


	void liberar() { tablero.liberar(); }

	DatosFinal motor();
};

