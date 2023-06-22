#ifndef _INFOTABLAS__H_
#define _INFOTABLAS__H_

#include <vector>

class Tablero;

class InfoTablas
{
	std::vector<Tablero> posiciones;
	std::vector<unsigned char> repeticiones;
	bool boolRepeticion;
	int contadorJugadas;

public:
	InfoTablas() { clearAll(); }

	inline void clearRepeticion() { posiciones.clear(); repeticiones.clear(); boolRepeticion = false; }
	inline void clearPasividad() { contadorJugadas = 0; }
	inline void clearAll() { clearRepeticion(); clearPasividad(); }

	void add(const Tablero& tablero);
	
	inline bool tablasPorRepeticion() const{ return boolRepeticion; }
	inline bool tablasPorPasividad() const{ return contadorJugadas > 50; }

	InfoTablas(const InfoTablas& rhs) : posiciones(rhs.posiciones), repeticiones(rhs.repeticiones), boolRepeticion(rhs.boolRepeticion), contadorJugadas(rhs.contadorJugadas) {}
};

#endif