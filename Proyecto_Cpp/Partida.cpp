#include "Partida.h"

Partida::Partida(std::string nombre_partida, int id, std::string modo, std::string blancas, std::string negras,
	float tiempo_inicial) {
	this->nombre_partida = nombre_partida;
	this->id = id;
	this->finalizada = 0;
	this->ganada = INICIALIZACION_POR_DEFECTO_STRING;
	this->tablas = INICIALIZACION_POR_DEFECTO_STRING;
	this->modo = modo;
	this->blancas = blancas;
	this->negras = negras;
	this->tiempo_inicial = tiempo_inicial;
	this->tiempo_restante = tiempo_inicial; //El tiempo restante es el mismo que el inicial al inicio de la partida
	this->ventaja_material = 0; 
	this->movimientos_blancas = { INICIALIZACION_POR_DEFECTO_STRING };
	this->movimientos_negras = { INICIALIZACION_POR_DEFECTO_STRING };
}

bool Partida::crearPartida() {
	std::fstream fs(nombre_partida.c_str(), std::ios_base::in);

	if (!fs.is_open()) {
		fs.close();
		fs.open(nombre_partida.c_str(), std::ios_base::out);
		fs << *this;
		return 1;
	}
	else {
		fs.close();
		std::cout << "La partida ya existe. Saliendo..." << std::endl;
		return 0;
	}
}

bool Partida::guardarPartida() {
	std::fstream fs(nombre_partida.c_str(), std::ios_base::in);

	if (!fs.is_open()) {
		std::cerr << "Error al guardar la partida. Saliendo..." << std::endl;
		return 0;
	}
	else {
		fs << *this;

	}
	
}


void operator<<(std::ostream& o, const Partida& p) {
	o << p.nombre_partida << std::endl;
	o << "Id partida: " << p.id << std::endl;
	o << "Modo: " << p.modo << std::endl;
	o << "Blancas: " << p.blancas << std::endl;
	o << "Negras: " << p.negras << std::endl;
	o << "Finalizada: " << p.finalizada << std::endl;
	o << "Ganada: " << p.ganada << std::endl;
	o << "Tablas: " << p.tablas << std::endl;
	o << "Tiempo inicial: " << p.tiempo_inicial << std::endl;
	o << "Tiempo restante: " << p.tiempo_restante << std::endl;
	o << "Material (blancas - negras): " << p.ventaja_material << std::endl;
	o << "- - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
	o << "Desarrollo: " << std::endl;
	o << "Blancas:\t" << "Negras:" << std::endl;

	for (int i = 0; i < p.movimientos_blancas.size(); i++) {
		o << p.movimientos_blancas[i] << "\t" << p.movimientos_negras[i] << std::endl;
	}
}
void operator>>(std::ostream& o, Partida& p) {
}