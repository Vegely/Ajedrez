#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
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
	bool finalizada = 0;
	std::string modo;
	std::string blancas;
	std::string negras;
	std::vector<Movimiento> movimientos;
	std::vector<int> coronacion;

public:
	Partida();

	bool existe();
	bool crearPartida();
	bool guardarPartida();
	bool cargarPartida();
	bool partidaFinalizada() { return finalizada; };
	void reset() { nombre_partida = ""; finalizada = 0; modo = ""; blancas = ""; negras = ""; movimientos.clear(); coronacion.clear(); }

	void setNombre(std::string nombre) { nombre_partida = nombre; };
	void setModo(std::string modo) { this->modo = modo; };
	void setBlancas(std::string blancas) { this->blancas = blancas; };
	void setNegras(std::string negras) { this->negras = negras; };
	void setFin(bool fin) { finalizada = fin; }
	
	friend void operator<<(std::ostream& o, const Partida& p);
	friend void operator>>(std::istream& is, Partida& p);
	friend class MotorDeJuego;
};

void operator<<(std::ostream& o, const Partida& p);
void operator>>(std::istream& is, Partida& p);
