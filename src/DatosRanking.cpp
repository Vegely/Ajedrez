#pragma once
#include "DatosRanking.h"
#include <iostream>
#include <fstream>

DatosRanking* asignaEspacio(int nfilas) {
	DatosRanking* ptdranking = new DatosRanking[nfilas];
	ptdranking->tamanio = nfilas;
	return ptdranking;
}

void liberaEspacio(DatosRanking* ptdranking) {
	delete[] ptdranking;
}

int posicionJugador(DatosRanking* ptdranking, const std::string& nombre) {
	for (int i = 0; i < ptdranking->tamanio; i++)
		if (ptdranking[i].nombre == nombre)
			return ptdranking[i].posicion;

	return 0;
}

void actualizaRanking(DatosRanking* ptdranking, const std::string& nombre, int puntos, const std::string& nombre_fichero) {
	int pos = posicionJugador(ptdranking, nombre);
	std::fstream fs(nombre_fichero, std::ios_base::app);
	ptdranking[pos - 1].puntuacion += puntos;

	int puesto = 1;

	for (int i = 0; i < ptdranking->tamanio; i++) {
		if (ptdranking[i].puntuacion > ptdranking[pos - 1].puntuacion) {
			fs << puesto << " " << ptdranking[i].puntuacion << " " << ptdranking[i].nombre
				<< " " << ptdranking[i].id << std::endl;
			puesto++;
		}
	}

	fs << puesto << " " << ptdranking[pos - 1].puntuacion << " " << ptdranking[pos - 1].nombre
		<< " " << ptdranking[pos - 1].id << std::endl;
	puesto++;

	for (int i = 0; i < ptdranking->tamanio; i++) {
		if (ptdranking[i].puntuacion < ptdranking[pos - 1].puntuacion) {
			fs << puesto << " " << ptdranking[i].puntuacion << " " << ptdranking[i].nombre
				<< " " << ptdranking[i].id << std::endl;
			puesto++;
		}
	}
}

void rellenaRanking(DatosRanking* ptdranking, std::string nombre_fichero) {
	std::ifstream ifs(nombre_fichero);
	std::string str = "";

	std::getline(ifs, str);
	std::getline(ifs, str);

	int i = 0;
	while (!ifs.eof() && str != "") {
		std::stringstream ss;
		std::getline(ifs, str);
		ss << str;
		ss >> ptdranking[i].posicion >> ptdranking[i].puntuacion >> ptdranking[i].nombre >> ptdranking[i].id;
		i++;
	}

	ifs.close();
}