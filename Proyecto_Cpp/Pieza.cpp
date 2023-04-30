#include "Pieza.h"
#include "Tablero.h"

void Pieza::clearVariables()
{
	puede_mover.clear();
	puede_comer.clear();
	esta_protegiendo.clear();
	amenazas.clear();
}

////////////////////////////////////////////////////////////////////////
	//Pruebas unitarias funcion mover sin argumentos
	// 
	// Poner en pieza.h
	//inline const std::vector<Posicion> getPuedeMover() { return puede_mover; }
	//inline const Posicion getPosicion() const{ return posicion; }
	//inline const std::vector<Pieza*> getPuedeComer() { return puede_comer; }
	// 
	// Poner en tabkero.cpp
	// for (int i = 0; i < ANCHO_TABLERO * ANCHO_TABLERO; i++) { tablero[i] = nullptr; }
	//
	//Se añaden dos torres abitrarias
	//escribir(Posicion(3, 6), new Peon(*this, false));
	//escribir(Posicion(3, 5), new Caballo(*this, true));
	// 
	// Poner en main.cpp
	// Tablero tablero;
	//Posicion p{ 3, 6 };
	//tablero.leer(p)->mover();
	//for (const Posicion puedeMover : tablero.leer(p)->getPuedeMover())
	//{
		//cout << (int)puedeMover.x << " " << (int)puedeMover.y << endl;
	//}
	//for (const Pieza* puedeComer : tablero.leer(p)->getPuedeComer())
	//{
		//cout << (int)puedeComer->getPosicion().x << " " << (int)puedeComer->getPosicion().y << endl;
	//}
	////////////////////////////////////////////////////////////////////////

void Pieza::mover()
{
	actualizarVariables();
}

