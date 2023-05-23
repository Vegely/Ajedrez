#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Campo.h"

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
	std::string j1;
	std::string j2;
	float tiempo_inicial;
	float tiempo_restante;
	int ventaja_material; //material_blancas - material_negras
	std::vector<std::string> movimientos_blancas;
	std::vector<std::string> movimientos_negras;

public:
	Partida();

	bool existe();
	bool crearPartida();
	bool guardarPartida();
	bool cargarPartida();
	void movBlancas(std::string mov_blancas) { movimientos_blancas.push_back(mov_blancas); };
	void movNegras(std::string mov_negras) { movimientos_negras.push_back(mov_negras); };
	bool partidaFinalizada() { return finalizada; };

	std::string& getNombre() { return nombre_partida; };
	std::string& getModo() { return modo; };
	std::string& getJ1() { return j1; };
	std::string& getJ2() { return j2; };

	friend void operator<<(std::ostream& o, const Partida& p);
	friend void operator>>(std::istream& is, Partida& p);
};

void operator<<(std::ostream& o, const Partida& p);
void operator>>(std::istream& is, Partida& p);