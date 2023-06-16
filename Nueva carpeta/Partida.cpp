#include "Partida.h"

Partida::Partida() { 
	this->nombre_partida = "";
	this->id = 0;
	this->finalizada = 0;
	this->ganada = INICIALIZACION_POR_DEFECTO_STRING;
	this->tablas = INICIALIZACION_POR_DEFECTO_STRING;
	this->modo = "";
	j1 = "";
	j2 = "";
	this->tiempo_inicial = 0;
	this->tiempo_restante = 0; //El tiempo restante es el mismo que el inicial al inicio de la partida
	this->ventaja_material = 0;
	this->movimientos_blancas = {  };
	this->movimientos_negras = {  };
}

bool Partida::crearPartida() {
	std::ifstream fs(nombre_partida.c_str());

	if (!fs.is_open()) { //Si no está abierta no existía
		fs.close();
		std::ofstream ofs(nombre_partida.c_str());
		ofs << *this;
		ofs.close();
		return true;
	}
	return false;
}

bool Partida::existe() {
	std::ifstream fs(nombre_partida.c_str());

	if (!fs.is_open()) {
		fs.close();
		return false;
	}
	fs.close();
	return true;
}

bool Partida::guardarPartida() {
	std::ofstream ofs(nombre_partida.c_str(), std::ios_base::in);

	if (!ofs.is_open()) {
		std::cerr << "Error al guardar la partida. Saliendo..." << std::endl;
		ofs.close();
		return 0;
	}
	else {
		ofs << *this;
		ofs.close();
		return 1;
	}
}

bool Partida::cargarPartida() {
	std::ifstream ifs(nombre_partida.c_str(), std::ios_base::out);

	if (!ifs.is_open()) {
		std::cerr << "Error al cargar la partida. Saliendo..." << std::endl;
		ifs.close();
		return 0;
	}
	else {
		ifs >> *this;
		ifs.close();
		return 1;
	}

}

void operator<<(std::ostream& o, const Partida& p) {
	o << (Campo::partida_nombre_partida + ": ") << p.nombre_partida << std::endl;
	o << (Campo::partida_id + ": ") << p.id << std::endl;
	o << (Campo::partida_modo + ": ") << p.modo << std::endl;
	o << (Campo::partida_blancas + ": ") << p.j1 << std::endl;
	o << (Campo::partida_negras + ": ") << p.j2 << std::endl;
	o << (Campo::partida_finalizada + ": ") << p.finalizada << std::endl;
	o << (Campo::partida_ganada + ": ") << p.ganada << std::endl;
	o << (Campo::partida_tablas + ": ") << p.tablas << std::endl;
	o << (Campo::partida_tiempo_inicial + ": ") << p.tiempo_inicial << std::endl;
	o << (Campo::partida_tiempo_restante + ": ") << p.tiempo_restante << std::endl;
	o << (Campo::partida_ventaja_material + ": ") << p.ventaja_material << std::endl;
	o << Campo::delimitador << std::endl;
	o << Campo::desarrollo << std::endl;
	o << Campo::partida_movimientos << std::endl;

	for (int i = 0; i < p.movimientos_blancas.size(); i++) {
		o << p.movimientos_blancas[i] << "\t\t" << p.movimientos_negras[i] << std::endl;
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
		
		if (nombre_campo == Campo::partida_nombre_partida)
			ss >> p.nombre_partida;
		if(nombre_campo==Campo::partida_id)
			ss >> p.id;
		if (nombre_campo == Campo::partida_modo) 
			ss >> p.modo;
		if (nombre_campo == Campo::partida_blancas) 
			ss >> p.j1;
		if(nombre_campo== Campo::partida_negras)
			ss >> p.j2;
		if(nombre_campo== Campo::partida_finalizada)
			ss >> p.finalizada;
		if(nombre_campo== Campo::partida_ganada)
			ss >> p.ganada;
		if(nombre_campo== Campo::partida_tablas)
			ss >> p.tablas;
		if(nombre_campo== Campo::partida_tiempo_inicial)
			ss >> p.tiempo_inicial;
		if(nombre_campo== Campo::partida_tiempo_restante)
			ss >> p.tiempo_restante;
		if(nombre_campo== Campo::partida_ventaja_material)
			ss >> p.ventaja_material;
	}

	//Comprobación de errores en el flujo
	if (is.bad()) { std::cerr << "Error I/O. Saliendo..."; return; }
	else if (is.fail()) { std::cerr << "Error en lectura. Saliendo..."; return; }
	else if (is.eof()) { std::cerr << "EOF inesperado. Saliendo..."; return; }

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

