#include "Ranking.h"

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
		std::cout << ultima_posicion;
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
		ss << (ultima_posicion + 1) << " \t 0 \t " << nombre << " \t " << id;
		str = ss.str();
		ofs << str << std::endl;
		ofs.close();
		ultima_posicion++;
		return 1;
	}
}

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