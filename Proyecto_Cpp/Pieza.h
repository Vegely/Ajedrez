#ifndef _PIEZA__H_
#define	_PIEZA__H_

#include <vector>

#include "Posicion.h"

#define VALOR_PEON 1
#define VALOR_CABALLO 3
#define VALOR_ALFIL 3
#define VALOR_TORRE 5
#define VALOR_REINA 9
#define VALOR_REY 10	// A lo mejor hay que ponerle un valor -> inf para que la IA no suicide el rey

class Tablero;

class Pieza
{
protected:
	const Tablero& tablero;
	const bool color;						//True == Blancas <-> False == Negras
	const unsigned char value;

	Posicion posicion;
	std::vector<Posicion> puede_mover;		//Lugares disponibles para mover
	std::vector<Pieza*> puede_comer;		//Piezas que puede comer
	std::vector<Pieza*> esta_protegiendo;	//Piezas de su propio equipo con las que colisiona en el movimiento
	std::vector<Pieza*> amenazas;			//Piezas enemigas que amenazan la posicion actual

	void clearVariables();
	inline void addAmenazas(Pieza* p_pieza) { amenazas.push_back(p_pieza); }
	virtual void actualizarVariables() {}

public:
	friend class Tablero;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Se necesita para que las piezas se asignen a si mismas a las amenazas de las piezas que tienen en puede_comer
	friend class Peon;
	friend class Caballo;
	friend class Alfil;
	friend class Torre;
	friend class Reina;
	friend class Rey;

	explicit Pieza(const Tablero& p_tablero, const bool color, const unsigned char value) : tablero(p_tablero), color(color), value(value) {}

	////////////////////////////////////////////////////////////////////////
	//Temporal para pruebas
	inline const std::vector<Posicion> getPuedeMover() { return puede_mover; }
	//inline const Tablero& getTablero() { return tablero; }
	////////////////////////////////////////////////////////////////////////

	void mover();
};

#endif // !_Pieza__H_ //