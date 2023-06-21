#ifndef _DATOSRANKING__H_
#define _DATOSRANKING__H_

#include <string>
#include <sstream>

struct DatosRanking {
	int posicion;
	float puntuacion;
	std::string nombre;
	std::string id;
	int tamanio;
};

DatosRanking* asignaEspacio(int nfilas);
void liberaEspacio(DatosRanking* ptdranking);
int posicionJugador(DatosRanking* ptdranking, const std::string& nombre);
void rellenaRanking(DatosRanking* ptdranking, std::string nombre_fichero);
void actualizaRanking(DatosRanking* ptdranking, const std::string& nombre, int puntuacion, const std::string& nombre_fichero);

#endif // !_DATOSRANKING__H_