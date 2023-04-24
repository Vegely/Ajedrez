#include "Ranking.h"

//Estado de flujos de forma mas compacta?

Ranking::Ranking() {
	inicializa();
}

bool Ranking::inicializa() {
	std::fstream fs(nombre_fichero, std::ios_base::in);

	//Si no se ha abierto no existía
	if (!fs.is_open()) {
		fs.close();
		fs.open(nombre_fichero, std::ios_base::out);
		fs << titulo << std::endl;
		fs << campos << std::endl;
		fs.close();
		return 1;
	}
	else if (fs.fail() || fs.eof() || fs.bad()) {
		std::cerr << "Error al abrir el ranking. Saliendo..." << std::endl;
		fs.close();
		return 0;
	}
	else {
		while (!fs.eof()) {
			static std::string str = "";
			std::getline(fs, str);
			ultima_posicion++;
		}
		ultima_posicion -= 3;
		fs.close();
		return 1;
	}
}

bool Ranking::aniadirJugador(const std::string& nombre, int id) {
	std::ofstream ofs(nombre_fichero, std::ios_base::app);

	if (!ofs.is_open()) {
		std::cerr << "Jugador no aniadido" << std::endl;
		ofs.close();
		return 0;
	}
	else if (ofs.fail() || ofs.bad() || ofs.eof()) {
		std::cerr << "Error al aniadir al jugador.Saliendo..." << std::endl;
		ofs.close();
		return 0;
	}
	else {
		std::stringstream ss;
		std::string str = "";
		ss << (ultima_posicion + 1) << " \t 0.0f \t " << nombre << " \t " << id;
		str = ss.str();
		ofs << str << std::endl;
		ofs.close();
		ultima_posicion++;
		return 1;
	}
}

bool Ranking::actualizar(const std::string& nombre, float puntos) {
	return 0;
}

/*
bool Ranking::actualizar(const std::string& nombre, float puntos) {
	//Registra la fila correspondiente al nombre del jugador en la variable "fila"
	datosJugador(nombre);
	
	int posicion = this->posicion();
	int id = this->id();
	float puntuacion = this->puntuacion() + puntos;
	//std::string fila_actualizada =


	std::ofstream temp("temp.txt");
	std::ifstream rank(nombre_fichero);

	if (!temp.is_open() || !rank.is_open()) {
		std::cerr << "Error al actualizar ranking. Saliendo..." << std::endl;
		temp.close();
		rank.close();
		return 0;
	}
	else if (temp.fail() || temp.bad() || temp.eof() ||
		rank.fail() || rank.bad() || rank.eof()) {
		std::cerr << "Error al abrir ranking. Saliendo..." << std::endl;
		temp.close();
		rank.close();
		return 0;
	}
	else {
		//Lee los encabezados
		std::string str = "";
		std::getline(rank, str);
		temp << str << std::endl;
		std::getline(rank, str);
		temp << str << std::endl;

		for (int pos = 1; pos <= ultima_posicion; pos++) {
			std::getline(rank, fila);
			if (this->nombre() == nombre)
				continue;
			else if ()

		}

		temp.close();
		rank.close();
		return 1;
	}
}

void Ranking::datosJugador(const std::string& nombre) {
	std::ifstream ifs(nombre_fichero);
	std::string str = "";

	std::getline(ifs, str);
	std::getline(ifs, str);

	while (!ifs.eof()) {
		std::getline(ifs, fila);

		if (nombre == this->nombre()) {
			ifs.close();
			break;
		}
	}
	ifs.close();
}
int Ranking::posicion() const {
	std::stringstream ss;
	int pos = 0;
	ss << fila;
	ss >> pos;
	return pos;
}

int Ranking::id() const {
	std::stringstream ss;
	std::string token = "";
	int id;
	ss << fila;
	ss >> token >> token >> token >> id;
	return id;
}

float Ranking::puntuacion() const {
	std::stringstream ss;
	std::string str = "";
	float res = 0.0f;
	ss << fila;
	ss >> str >> res;
	return res;
}

std::string Ranking::nombre() const {
	std::stringstream ss;
	std::string token = "";
	std::string nombre = "";
	ss << fila;
	ss >> token >> token >> nombre;
	return nombre;
}*/

std::ostream& Ranking::print(int nposiciones, std::ostream& o) const {
	std::ifstream ifs(nombre_fichero);
	std::string str = "";
	
	std::getline(ifs, str);
	std::getline(ifs, str);

	if (!ifs.is_open()) {
		std::cerr << "Error al cargar ranking. Saliendo..." << std::endl;
		return o;
	}
	else if (ifs.eof() || ifs.fail() || ifs.bad()) {
		std::cerr << "Error en la lectura. Saliendo..." << std::endl;
		return o;
	}

	for (int i = 0; i < nposiciones && !ifs.eof(); i++) {
		std::getline(ifs, str);
		o << str << std::endl;
	}

	ifs.close();
	return o;
}
