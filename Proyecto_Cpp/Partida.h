#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

constexpr const char* PARTIDA_TEMPORAL = "partida_temp.txt";

class Partida
{
private:
	std::string nombre_partida;
	int id;
	bool finalizada;
	std::string ganada;
	std::string tablas;
	std::string modo;
	std::string blancas; //Id jugador blancas
	std::string negras; //Id jugador negras
	float tiempo_restante;
	float tiempo_inicial;
	std::string ventaja_material; //material_blancas - material_negras
	std::vector<std::string> movimientos_blancas;
	std::vector<std::string> movimientos_negras;

	friend void operator<<(std::ostream& o, const Partida& p);
	friend void operator>>(std::ostream& o, Partida& p);

public:
	bool crearPartida();
	bool guardarPartida();
};

void operator<<(std::ostream& o, const Partida& p);
void operator>>(std::ostream& o, Partida& p);
