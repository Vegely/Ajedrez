#ifndef _PARTIDA__H_
#define _PARTIDA__H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>

#include "Movimiento.h"

const std::string CARPETA_FINALIZADAS = "finalizadas/";
const std::string CARPETA_NOFINALIZADAS = "nofinalizadas/";
const std::string PARTIDA_TEMPORAL = "partidas/partida_temp.txt";

const std::string partida_nombre_partida = "Nombre de la partida";
const std::string partida_modo = "Modo";
const std::string partida_finalizada = "Finalizada";
const std::string partida_blancas = "Blancas"; //Nombre jugador blancas
const std::string partida_negras = "Negras"; //Nombre jugador negras
const std::string partida_movimientos = "Movimientos";
const std::string partida_coronacion = "Coronacion";


class Partida
{
private:
	std::string nombre_partida;
	std::string nombre_partida_cargar;
	bool finalizada = 0;
	std::string modo;
	std::string blancas;
	std::string negras;
	std::deque<Movimiento> movimientosEntrada;
	std::vector<Movimiento> movimientosSalida;
	std::deque<int> coronacionEntrada;
	std::vector<int> coronacionSalida;

public:
	Partida() { reset(); }

	bool existe();
	bool crearPartida();
	bool guardarPartida();
	bool cargarPartida();
	bool partidaFinalizada() { return finalizada; };
	void reset();

	void setNombre(std::string nombre) { nombre_partida = nombre; };
	void setNombreCargar(std::string nombre) { nombre_partida_cargar = nombre; }
	void setModo(std::string modo) { this->modo = modo; };
	void setBlancas(std::string blancas) { this->blancas = blancas; };
	void setNegras(std::string negras) { this->negras = negras; };
	void setFin(bool fin) { finalizada = fin; }

	std::string getNombre() { return nombre_partida; }
	std::string getNombreCargar() { return nombre_partida_cargar; }
	std::string getModo() { return modo; }
	std::string getBlancas() { return blancas; }
	std::string getNegras() { return negras; }
	bool getFin() { return finalizada; }

	friend void operator<<(std::ostream& o, const Partida& p);
	friend void operator>>(std::istream& is, Partida& p);
	friend class MotorDeJuego;
};

void operator<<(std::ostream& o, const Partida& p);
void operator>>(std::istream& is, Partida& p);

#endif // !_PARTIDA__H_