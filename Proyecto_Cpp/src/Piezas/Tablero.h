#ifndef _TABLERO__H_
#define	_TABLERO__H_


#include "Pieza.h"

constexpr auto ANCHO_TABLERO = 8;

class Tablero
{
	//Un tablero contiene todas las piezas
	Pieza* tablero[ANCHO_TABLERO * ANCHO_TABLERO];

	void escribir(const Posicion& posicion, Pieza* pieza);											//Escribe una pieza en una posición	
	void borrar(const Posicion& posicion);															//Borra la pieza en una posición
	void clearVariablesDePiezas() { for (Pieza* p_pieza : tablero) p_pieza->clearVariables(); }		//Limpia todas las variables de las piezas del tablero
	void actualizarTablero();																		//Actualiza las variables de todas las piezas del tablero

public:
	explicit Tablero();																									//Constructor
	inline Pieza* leer(const Posicion& posicion) const { return tablero[posicion.x + posicion.y * ANCHO_TABLERO];}		//Devuelve el puntero a pieza de una posición leóda
	bool mover(const Posicion &, const Posicion&);																		//Dadas dos posiciones mueve la pieza de la primera posicion a la segunda
																														//No implementada distinción por turnos

	//Funcion temporal para imprimir tablero por consola
	void imprimeTablero();
};


#endif