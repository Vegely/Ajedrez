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
	
	inline bool tablasPorRepeticion() const{ return boolRepeticion; }
	inline bool tablasPorPasividad() const{ return contadorJugadas > 50; }

	InfoTablas(const InfoTablas& rhs) : posiciones(rhs.posiciones), repeticiones(rhs.repeticiones), boolRepeticion(rhs.boolRepeticion), contadorJugadas(rhs.contadorJugadas) {}
};

