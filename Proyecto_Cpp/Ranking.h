#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "DatosRanking.h"



class Ranking
{
private:
	const char* nombre_fichero = "ranking.txt";
	const std::string titulo = "RANKING";
	const std::string campos = "Pos  Punt \t Jug \t\t Id";
	int ultima_posicion;
	DatosRanking* ptdranking = nullptr;
	//std::string fila; 

	bool inicializa();
	void aEstructura();
public:
	//Constructor
	Ranking();

	//Solo hay 1 ranking --> No se puede copiar ni asignar
	Ranking(const Ranking&) = delete;
	Ranking& operator=(const Ranking&) = delete;

	bool aniadirJugador(const std::string& nombre, int id);
	bool actualizar(const std::string& nombre, float puntos);
	void datosJugador(const std::string& nombre);
	int posicion() const;
	int id() const;
	float puntuacion() const;
	std::string nombre() const;
	std::ostream& print(int nposiciones, std::ostream& o = std::cout) const;
};


