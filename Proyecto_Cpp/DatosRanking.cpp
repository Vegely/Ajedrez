#pragma once
#include "DatosRanking.h"

DatosRanking* asignaEspacio(int nfilas) {
	DatosRanking* ptdranking = new DatosRanking[nfilas];
	ptdranking->tamanio = nfilas;
	return ptdranking;
}

void liberaEspacio(DatosRanking* ptdranking) {
	delete[] ptdranking;
}

void modificarPosicion(DatosRanking* ptdranking, int puntuacion) {
	for (int i = 0; i < ptdranking->tamanio; i++)
		if (ptdranking[i].puntuacion < puntuacion)
			ptdranking[i].posicion += 1;
}

int posicionJugador(DatosRanking* ptdranking, const std::string& nombre) {
	for (int i = 0; i < ptdranking->tamanio; i++) 
		if (ptdranking[i].nombre == nombre)
			return ptdranking[i].posicion;

	return 0;
}

void actualizaRanking(DatosRanking* ptdranking, const std::string& nombre, int puntos) {
	int pos = posicionJugador(ptdranking, nombre);
	ptdranking[pos - 1].puntuacion += puntos;
	
	int puesto = 1;

	for (int i = 0; i < ptdranking->tamanio; i++) {
		if (ptdranking[i].puntuacion > ptdranking[pos - 1].puntuacion) {
			std::cout << puesto << " " << ptdranking[i].puntuacion << " " << ptdranking[i].nombre
				<< " " << ptdranking[i].id << std::endl;
			puesto++;
		}
	}
	
	std::cout << puesto  << " " << ptdranking[pos - 1].puntuacion << " " << ptdranking[pos - 1].nombre
		<< " " << ptdranking[pos - 1].id << std::endl;
	puesto++;
	
	for (int i = 0; i < ptdranking->tamanio; i++) {
		if (ptdranking[i].puntuacion < ptdranking[pos - 1].puntuacion) {
			std::cout << puesto << " " << ptdranking[i].puntuacion << " " << ptdranking[i].nombre
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

	while (!ifs.eof() && str != "") {
		static int i = 0;
		std::stringstream ss;
		std::getline(ifs, str);
		ss << str;
		ss >> ptdranking[i].posicion >> ptdranking[i].puntuacion >> ptdranking[i].nombre >> ptdranking[i].id;
		i++;
	}

	ifs.close();
}