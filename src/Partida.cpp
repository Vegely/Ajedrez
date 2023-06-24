#include "Partida.h"

bool Partida::crearPartida() {
	std::ifstream fs(nombre_partida.c_str());

	if (!fs.is_open()) { //Si no está abierta no existía
		fs.close();
		std::ofstream ofs(nombre_partida.c_str());
		ofs << *this;
		ofs.close();
		return true;
	}
	fs.close();
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
		return false;
	}
	else {
		ofs << *this;
		ofs.close();
		return true;
	}
}

bool Partida::cargarPartida() {
	std::ifstream ifs(nombre_partida.c_str(), std::ios_base::out);

	if (!ifs.is_open()) {
		std::cerr << "Error al cargar la partida. Saliendo..." << std::endl;
		ifs.close();
		return false;
	}
	else {
		ifs >> *this;
		ifs.close();
		return true;
	}

}

void Partida::reset()
{
	nombre_partida = "";
	finalizada = 0;
	modo = "";
	blancas = "";
	negras = "";
	movimientosEntrada.clear();
	movimientosSalida.clear();
	coronacionEntrada.clear();
	coronacionSalida.clear();
}

void operator<<(std::ostream& o, const Partida& p) {
	o << (partida_nombre_partida + ": ") << p.nombre_partida << std::endl;
	o << (partida_modo + ": ") << p.modo << std::endl;
	o << (partida_finalizada + ": ") << p.finalizada << std::endl;
	o << (partida_blancas + ": ") << p.blancas << std::endl;
	o << (partida_negras + ": ") << p.negras << std::endl;
	o << partida_movimientos << std::endl;

	for (int i = 0; i < p.movimientosSalida.size(); i++)
		o << p.movimientosSalida[i].inicio.x << " " << p.movimientosSalida[i].inicio.y << " " << p.movimientosSalida[i].fin.x << " " << p.movimientosSalida[i].fin.y << std::endl;

	o << partida_coronacion << std::endl;

	for (int i = 0; i < p.coronacionSalida.size(); i++)
		o << p.coronacionSalida[i] << std::endl;
}
void operator>>(std::istream& is, Partida& p) {
	std::string str = "";

	while (std::getline(is, str)) {
		if (str == partida_movimientos)break;

		int pos = str.find(":", 0);
		pos += 1;

		std::stringstream ss;
		std::string nombre_campo = str.substr(0, pos - 1);
		ss << str.substr(pos + 1);

		if (nombre_campo == partida_nombre_partida)
			ss >> p.nombre_partida;
		if (nombre_campo == partida_modo)
			ss >> p.modo;
		if (nombre_campo == partida_blancas)
			ss >> p.blancas;
		if (nombre_campo == partida_negras)
			ss >> p.negras;
		if (nombre_campo == partida_finalizada)
			ss >> p.finalizada;
	}

	//Comprobación de errores en el flujo
	if (is.bad()) { std::cerr << "Error I/O. Saliendo..."; return; }
	else if (is.fail()) { std::cerr << "Error en lectura. Saliendo..."; return; }
	else if (is.eof()) { std::cerr << "EOF inesperado. Saliendo..."; return; }

	while (std::getline(is, str)) {
		if (str == partida_coronacion)break;
		std::stringstream ss;
		std::string s = "";
		Movimiento mov;
		ss << str;
		ss >> mov.inicio.x >> mov.inicio.y >> mov.fin.x >> mov.fin.y;
		p.movimientosEntrada.push_back(mov);
	}
	while (std::getline(is, str)) {
		std::stringstream ss;
		int cor = 0;
		ss << str;
		ss >> cor;
		p.coronacionEntrada.push_back(cor);
	}
}
