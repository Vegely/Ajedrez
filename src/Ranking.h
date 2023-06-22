#ifndef _RANKING__H_
#define _RANKING__H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "DatosRanking.h"

#define JUGADORES_POR_HOJA 5
#define ALTO_GL 35.0 //25 hasta -10
#define ANCHO_GL 63.2 //-31.6 hasta 31.6

struct DatosRanking {
	int posicion;
	std::string puntuacion;
	std::string nombre;
	std::string id;
};

class Ranking
{
private:
	int pagina_actual = 0;
	int npaginas = 0;
	const char* nombre_fichero = "ranking/ranking.txt";
	const std::string titulo = "RANKING";
	const std::string campos = "Pos  Punt \t Jug";
	int ultima_posicion = 0;
	
	DatosRanking* ptdranking = nullptr;


	bool inicializa();
	void encabezado() const;
	bool jugadorExiste(std::string nombre_jugador) const;
	int posicionJugador(const std::string& nombre);

public:

	//Constructor
	Ranking();

	//Solo hay 1 ranking --> No se puede copiar ni asignar
	Ranking(const Ranking&) = delete;
	Ranking& operator=(const Ranking&) = delete;

	bool aniadirJugador(const std::string& nombre, int id=0);
	void actualizar(const std::string& nombre, float puntos);
	std::string nombre() const;
	void print() const;
	void paginaSiguiente() { if (pagina_actual >= npaginas)return; pagina_actual++; }
	void paginaAnterior() { if (pagina_actual <= 0)return; pagina_actual--; }
	void iniPag() { pagina_actual = 0; }
};

#endif // !_RANKING__H_