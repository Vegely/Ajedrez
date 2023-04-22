#include "Partida.h"

Partida::Partida(std::string nombre_partida, int id, std::string modo, int blancas, int negras,
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
	this->movimientos_blancas = { "" };
	this->movimientos_negras = { "" };
}

bool Partida::crearPartida() {
	std::fstream fs(nombre_partida.c_str(), std::ios_base::in);

	if (!fs.is_open()) {
		fs.close();
		fs.open(nombre_partida.c_str(), std::ios_base::out);
		fs << *this;
		fs.close();
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
		fs.close();
		return 1;
	}
	
}

bool Partida::cargarPartida() {

}


void operator<<(std::ostream& o, const Partida& p) {
	o << (Campo::nombre_partida + ": ") << p.nombre_partida << std::endl;
	o << (Campo::id + ": ") << p.id << std::endl;
	o << (Campo::modo + ": ") << p.modo << std::endl;
	o << (Campo::blancas + ": ") << p.blancas << std::endl;
	o << (Campo::negras + ": ") << p.negras << std::endl;
	o << (Campo::finalizada + ": ") << p.finalizada << std::endl;
	o << (Campo::ganada + ": ") << p.ganada << std::endl;
	o << (Campo::tablas + ": ") << p.tablas << std::endl;
	o << (Campo::tiempo_inicial + ": ") << p.tiempo_inicial << std::endl;
	o << (Campo::tiempo_restante + ": ") << p.tiempo_restante << std::endl;
	o << (Campo::ventaja_material + ": ") << p.ventaja_material << std::endl;
	o << Campo::delimitador << std::endl;
	o << Campo::desarrollo << std::endl;
	o << Campo::movimientos << std::endl;

	for (int i = 0; i < p.movimientos_blancas.size(); i++) {
		o << p.movimientos_blancas[i] << "\t" << p.movimientos_negras[i] << std::endl;
	}
}
void operator>>(std::istream& is, Partida& p) {
	std::string str = "";
	while (std::getline(is,str)) {
		if (str == Campo::delimitador)
			break;
			
		int pos = str.find(":", 0);
		pos += 1;

		std::stringstream ss;
		std::string nombre_campo = str.substr(0, pos - 1);
		ss << str.substr(pos+1);
		
		if (nombre_campo == Campo::nombre_partida)
			ss >> p.nombre_partida;
		if(nombre_campo==Campo::id)
			ss >> p.id;
		if (nombre_campo == Campo::modo) 
			ss >> p.modo;
		if (nombre_campo == Campo::blancas) 
			ss >> p.blancas;
		if(nombre_campo== Campo::negras)
			ss >> p.negras;
		if(nombre_campo== Campo::finalizada)
			ss >> p.finalizada;
		if(nombre_campo== Campo::ganada)
			ss >> p.ganada;
		if(nombre_campo== Campo::tablas)
			ss >> p.tablas;
		if(nombre_campo== Campo::tiempo_inicial)
			ss >> p.tiempo_inicial;
		if(nombre_campo== Campo::tiempo_restante)
			ss >> p.tiempo_restante;
		if(nombre_campo== Campo::ventaja_material)
			ss >> p.ventaja_material;
	}

	//Fallos en los flujos?
	std::getline(is, str);
	std::getline(is, str);
	while (std::getline(is, str)) {
		std::stringstream ss;
		std::string mov_blancas = "", mov_negras = "";
		ss << str;
		ss >> mov_blancas >> mov_negras;
		p.movimientos_blancas.push_back(mov_blancas);
		p.movimientos_negras.push_back(mov_negras);
	}

}

