#ifndef _TABLERO__H_
#define	_TABLERO__H_

#include "Pieza.h"
#include "Movimiento.h"
#include "DatosBloqueoJaque.h"
#include "InfoTablas.h"

constexpr auto ANCHO_TABLERO = 8;

class Tablero
{
	//Un tablero contiene todas las piezas
	Pieza* tablero[ANCHO_TABLERO * ANCHO_TABLERO];
	bool colorDelTurno;

	bool haMovido[6] = {};

	Posicion reyPos[2];

	int numeroPiezas;
	bool tableroIlegalesRey[2][8][8] = { false };
	std::vector<DatosClavada> datosClavada;

	Movimiento ultimaJugada; //Se guardan los datos de la posicion tras la ultima jugada para implementar comer al paso

	InfoTablas infoTablas;

	void escribir(const Posicion& posicion, Pieza* pieza);											//Escribe una pieza en una posición	
	void clearVariablesDePiezas() { for (Pieza* p_pieza : tablero) p_pieza->clearVariables(); }		//Limpia todas las variables de las piezas del tablero
	void actualizarTablero();																		//Actualiza las variables de todas las piezas del tablero
	

public:
	friend class InfoTablas;
	friend class MotorDeJuego;
	friend class IA;
	
	explicit Tablero(bool alocar = false);																									//Constructor

	static Tablero copiar(const Tablero& tablero);

	void liberar() { for (Pieza* p_pieza : tablero) delete p_pieza; }

	inline Posicion posicion(int i) const { return Posicion(i % ANCHO_TABLERO, i / ANCHO_TABLERO); }
	inline Pieza* leer(const Posicion& posicion) const { return tablero[posicion.x + posicion.y * ANCHO_TABLERO];}		//Devuelve el puntero a pieza de una posición leóda
	void mover(const Movimiento& movimiento);																		//Dadas dos posiciones mueve la pieza de la primera posicion a la segunda

	Movimiento getUltimaJugada() { return ultimaJugada; }

	void coronar(Posicion posicion, Pieza::tipo_t tipo);

	void cambiarTurno() { colorDelTurno = !colorDelTurno; }
	bool jaqueMate() const;
	bool reyAhogado() const;
	bool tablasMaterialInsuficiente() const;

	void actualizarHaMovido(Movimiento movimiento);
	void actualizarEnroque();
	void actualizarJaque();
	void actualizarAlPaso();

	std::vector<DatosBloqueoJaque> bloqueoJaque() const;
};

#endif