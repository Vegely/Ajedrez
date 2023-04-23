#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class Ranking
{
private:
	const char* nombre_fichero = "ranking.txt";
	const std::string titulo = "RANKING";
	const std::string campos = "Pos  Punt \t Jug \t\t Id";
	int ultima_posicion;
	std::vector<std::string> fila; //Cada entrada representa una fila

	bool inicializa();
public:
	//Constructor
	Ranking();

	//Solo hay 1 ranking --> No se puede copiar ni asignar
	Ranking(const Ranking&) = delete;
	Ranking& operator=(const Ranking&) = delete;

	bool aniadirJugador(const std::string& nombre, int id);
	std::ostream& print(int nposiciones, std::ostream& o = std::cout) const;
};


