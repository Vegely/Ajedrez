#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Movimiento.h"

const std::string PARTIDA_TEMPORAL = "partida_temp.txt";

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
	bool finalizada;
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

	std::string& getNombre() { return nombre_partida; };
	std::string& getModo() { return modo; };
	std::string& getBlancas() { return blancas; };
	std::string& getNegras() { return negras; };

	friend void operator<<(std::ostream& o, const Partida& p);
	friend void operator>>(std::istream& is, Partida& p);
};

void operator<<(std::ostream& o, const Partida& p);
void operator>>(std::istream& is, Partida& p);
