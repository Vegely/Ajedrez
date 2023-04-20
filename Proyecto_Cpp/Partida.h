#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

constexpr const char* PARTIDA_TEMPORAL = "partida_temp.txt";
constexpr const char* INICIALIZACION_POR_DEFECTO_STRING = "defecto";

class Partida
{
private:
	//Definir ganador y perdedor?
	std::string nombre_partida;
	int id;
	bool finalizada;
	std::string ganada;
	std::string tablas;
	std::string modo;
	std::string blancas; //Id jugador blancas
	std::string negras; //Id jugador negras
	float tiempo_inicial;
	float tiempo_restante;
	int ventaja_material; //material_blancas - material_negras
	std::vector<std::string> movimientos_blancas;
	std::vector<std::string> movimientos_negras;

	friend void operator<<(std::ostream& o, const Partida& p);
	friend void operator>>(std::ostream& o, Partida& p);

public:
	//Constructor de partidas nuevas
	Partida(std::string nombre_partida, int id, std::string modo, std::string blancas, std::string negras,
		float tiempo_inicial);

	bool crearPartida();
	bool guardarPartida();
};

void operator<<(std::ostream& o, const Partida& p);
void operator>>(std::ostream& o, Partida& p);
