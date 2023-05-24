#pragma once

#include "Tablero.h"

enum class CodigoFinal { JAQUE_MATE, TABLAS_POR_MATERIAL_INSUFICIENTE, TABLAS_POR_REPETICION, TABLAS_POR_PASIVIDAD };	

struct DatosFinal
{
	bool ganador;
	CodigoFinal codigoFinal;
};

class MotorDeJuego
{
	Tablero tablero;

	void pintar(Posicion piezaSelec = Posicion(-1, -1)) const;
	void coronar(Posicion posicion);

public:
	MotorDeJuego() { pintar(); }

	//void inicializar();
	bool hacerJugada(Movimiento movimiento);

	Movimiento ensamblarMovimiento(Posicion posicion, bool pos1Selec) const;
	
	bool colorDelTurno() { return tablero.colorDelTurno; }

	bool jaqueMate() { return tablero.jaqueMate(); }
	bool tablasPorMaterialInsuficiente() { return tablero.tablasMaterialInsuficiente(); }
	bool tablasPorRepeticion() { return tablero.infoTablas.tablasPorRepeticion(); }
	bool tablasPorPasividad() { return tablero.infoTablas.tablasPorPasividad(); }
};

