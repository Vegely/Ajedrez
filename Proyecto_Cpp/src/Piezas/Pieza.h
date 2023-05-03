#ifndef _PIEZA__H_
#define	_PIEZA__H_

#include <vector>
#include <string>

#include "Posicion.h"

//Valores de las piezas para su uso en la IA
constexpr auto VALOR_PEON = 1;
constexpr auto VALOR_CABALLO = 3;
constexpr auto VALOR_ALFIL = 3;
constexpr auto VALOR_TORRE = 5;
constexpr auto VALOR_DAMA = 9; 
constexpr auto VALOR_REY = 10;

//Clase tablero vacía para tener una referencia al tablero dentro de las piezas
class Tablero;

class Pieza
{
protected:
	const std::string nombre;				//Nombre para identificar a la pieza
	const Tablero& tablero;					//Referencia al tablero para que las piezas sepan en que tablero estan
	const bool color;						//True == Blancas <-> False == Negras
	const unsigned char value;				//Valor de la pieza

	Posicion posicion;						//Casilla del tablero donde esta la pieza (0-7)x(0-7)
	std::vector<Posicion> puede_mover;		//Lugares disponibles para mover
	std::vector<Pieza*> puede_comer;		//Piezas que puede comer
	std::vector<Pieza*> esta_protegiendo;	//Piezas de su propio equipo con las que colisiona en el movimiento
	std::vector<Pieza*> amenazas;			//Piezas enemigas que amenazan la posicion actual

	void clearVariables();					//Funcion para limpiar los elementos de la clase vector
	virtual void actualizarVariables() {}	//Funcion para actualizar todos los elementos de vector
	inline void addAmenazas(Pieza* p_pieza) { amenazas.push_back(p_pieza); }	 //Función general de gestión de las amenazas desde el gestor

public:
	//Para que el tablero pueda modificar las piezas
	friend class Tablero;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Se necesita para que las piezas se asignen a si mismas a las amenazas de las piezas que tienen en puede_comer
	friend class Peon;
	friend class Caballo;
	friend class Alfil;
	friend class Torre;
	friend class Dama;
	friend class Rey;

	//Operadores básicos
	explicit Pieza(const Tablero& p_tablero, const bool color, const unsigned char value, const  std::string nombre) : tablero(p_tablero), color(color), value(value), nombre(nombre){}
	explicit Pieza(const Pieza& p) :nombre(p.nombre), value(p.value), tablero(p.tablero), color(p.color) { posicion = p.posicion; puede_mover = p.puede_mover; puede_comer = p.puede_comer; esta_protegiendo = p.esta_protegiendo; amenazas = p.amenazas; }
	virtual ~Pieza() {}

	//Poder mover desde el main
	void mover();

	//Funciones para obtener las variables (deben poder usarse en un espacio de constness)
	inline Posicion getPosicion() const { return posicion; }
	inline bool getColor() const { return color; }
	inline std::string getNombre() const { return nombre; }
	inline const std::vector<Posicion> getPuedeMover() const { return puede_mover; }
	inline const std::vector<Pieza*> getPuedeComer() const { return puede_comer; }
	inline const std::vector<Pieza*> getestaProtegiendo() const { return esta_protegiendo; }
	inline const std::vector<Pieza*> getAmenazas() const { return amenazas; }
	
	
	
};

#endif // !_Pieza__H_ //