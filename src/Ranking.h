#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "DatosRanking.h"

#define JUGADORES_POR_HOJA 5
#define ALTO_GL 35.0 //25 hasta -10
#define ANCHO_GL 63.2 //-31.6 hasta 31.6

class Ranking
{
private:
	int pagina_actual = 0;
	int npaginas = 0;
	const char* nombre_fichero = "ranking.txt";
	const std::string titulo = "RANKING";
	const std::string campos = "Pos  Punt \t Jug \t\t Id";
	int ultima_posicion;
	DatosRanking* ptdranking = nullptr;


	bool inicializa();
	void aEstructura() { ptdranking = asignaEspacio(ultima_posicion); };
	void liberaEstructura() { liberaEspacio(ptdranking); };
	void encabezado() const;
	bool jugadorExiste(std::string nombre_jugador) const;

public:

	//Constructor
	Ranking();

	//Solo hay 1 ranking --> No se puede copiar ni asignar
	Ranking(const Ranking&) = delete;
	Ranking& operator=(const Ranking&) = delete;

	bool aniadirJugador(const std::string& nombre, int id);
	void actualizar(const std::string& nombre, float puntos);
	std::string nombre() const;
	void print() const;
	void paginaSiguiente() { if (pagina_actual >= npaginas)return; pagina_actual++; }
	void paginaAnterior() { if (pagina_actual <= 0)return; pagina_actual--; }
	void iniPag() { pagina_actual = 0; }
};
