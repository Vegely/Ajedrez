#pragma once

#include <vector>

class Tablero;

class InfoTablas
{
	std::vector<Tablero> posiciones;
	std::vector<unsigned char> repeticiones;
	bool boolRepeticion;
	int contadorJugadas;

public:
	InfoTablas() { clear(); }

	inline void clear() { posiciones.clear(); repeticiones.clear(); boolRepeticion = false; contadorJugadas = 0; }
	void add(const Tablero& tablero);
	
	inline bool tablasPorRepeticion() { return boolRepeticion; }
	inline bool tablasPorPasividad() { return contadorJugadas > 50; }
};

