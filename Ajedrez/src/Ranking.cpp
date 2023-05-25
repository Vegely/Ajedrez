#include "Ranking.h"
#include "ETSIDI.h"
#include "CajaTexto.h"

//Estado de flujos de forma mas compacta?

Ranking::Ranking() {
	inicializa();
}

bool Ranking::inicializa() {
	std::fstream fs(nombre_fichero, std::ios_base::in);

	//Si no se ha abierto no existía
	if (!fs.is_open()) {
		fs.close();
		encabezado();
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
		npaginas = ultima_posicion / JUGADORES_POR_HOJA;
		fs.close();
		return 1;
	}
}

void Ranking::encabezado() const {
	std::fstream fs(nombre_fichero, std::ios_base::out);
	fs << titulo << std::endl;
	fs << campos << std::endl;
	fs.close();
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
		if (!jugadorExiste(nombre)) {
			std::stringstream ss;
			std::string str = "";
			ss << (ultima_posicion + 1) << " \t 0.0 \t " << nombre << " \t " << id;
			str = ss.str();
			ofs << str << std::endl;
			ofs.close();
			ultima_posicion++;
			return 1;
		}
	}
}

void Ranking::print() const {
	std::ifstream ifs(nombre_fichero);
	std::string str = "";

	std::getline(ifs, str);
	std::getline(ifs, str);

	if (!ifs.is_open()) {
		std::cerr << "Error al cargar ranking. Saliendo..." << std::endl;
		return;
	}
	else if (ifs.eof() || ifs.fail() || ifs.bad()) {
		std::cerr << "Error en la lectura. Saliendo..." << std::endl;
		return;
	}

	if (npaginas == 0) {
		for (int i = 0; i < ultima_posicion; i++) {
			std::getline(ifs, str);
			ETSIDI::printxy(str.c_str(), -5, (ALTO_GL-ALTO_GL/2) - 2 * i);
		}
	}
	else {
		for (int i = 0; i < pagina_actual * JUGADORES_POR_HOJA; i++) {
			std::getline(ifs, str);
		}
		for (int i = 0; i <  JUGADORES_POR_HOJA; i++) {
			std::getline(ifs, str);
			ETSIDI::printxy(str.c_str(), -5, (ALTO_GL - ALTO_GL / 2) - 2 * i);
		}
	}

	/*/for (int i = 0; i < nposiciones && !ifs.eof(); i++) {
		std::getline(ifs, str);
		//ETSIDI::printxy(ranking.print(5).c_str(), -5, 8);
	}*/
	ifs.close();
}

void Ranking::actualizar(const std::string& nombre, float puntos) {
	aEstructura();
	rellenaRanking(ptdranking, nombre_fichero);
	encabezado();
	actualizaRanking(ptdranking, nombre, puntos, nombre_fichero);
	liberaEstructura();
}

bool Ranking::jugadorExiste(std::string nombre_jugador) const{
	std::ifstream ifs(nombre_fichero);
	std::string str = "";
	float token = 0;
	std::string nombre = "";

	std::getline(ifs, str);
	std::getline(ifs, str);

	while (std::getline(ifs, str)) {
		std::stringstream ss;
		ss << str;
		ss >> token >> token >> nombre;

		if (nombre == nombre_jugador)
			return 1;
	}

	ifs.close();

	return 0;
}