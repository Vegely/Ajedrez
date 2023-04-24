#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>


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
void modificarPosicion(DatosRanking* ptdranking, int npos = 0);
void rellenaRanking(DatosRanking* ptdranking, std::string nombre_fichero);
void actualizaRanking(DatosRanking* ptdranking, const std::string& nombre, int puntuacion);