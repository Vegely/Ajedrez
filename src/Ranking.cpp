#include "Ranking.h"
#include "ETSIDI.h"
#include <algorithm>

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
			ss << (ultima_posicion + 1) << " " << nombre << "\t 0.0";
			str = ss.str();
			ofs << str << std::endl;
			ofs.close();
			ultima_posicion++;
			npaginas = (ultima_posicion-1) / JUGADORES_POR_HOJA;
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
			ETSIDI::printxy(str.substr(0, str.find(".")).c_str(), -5, floor(ALTO_GL - ALTO_GL / 2) - 3 * i - 10);
		}
	}
	else {
		for (int i = 0; i < pagina_actual * JUGADORES_POR_HOJA; i++) {
			std::getline(ifs, str);
		}
		for (int i = 0; i < JUGADORES_POR_HOJA; i++) {
			std::getline(ifs, str);
			ETSIDI::printxy(str.substr(0,str.find(".")).c_str(), -5, floor(ALTO_GL - ALTO_GL / 2) - 3 * i - 10);
		}
	}
	ifs.close();
}

void Ranking::actualizar(const std::string& nombre, float puntos) {
	ptdranking = new DatosRanking[ultima_posicion];

	std::ifstream ifs(nombre_fichero);
	std::string str = "";
	int ind = 0;
	int pos = 1;

	std::getline(ifs, str);
	std::getline(ifs, str);

	for (int i = 0; i < ultima_posicion; i++) {
		std::stringstream ss;
		std::getline(ifs, str);
		ss << str;
		ss >> ptdranking[i].posicion >> ptdranking[i].nombre >> ptdranking[i].puntuacion;
	}
	ifs.close();

	ind = posicionJugador(nombre);
	if (ind != -1) {
		ptdranking[ind].puntuacion = std::to_string(std::stof(ptdranking[ind].puntuacion) + puntos);
		encabezado();

		std::ofstream ofs(nombre_fichero, std::ios_base::app);

		for (int i = 0; i < ultima_posicion; i++) 
		{
			if (std::stof(ptdranking[i].puntuacion) > std::stof(ptdranking[ind].puntuacion))
			{
				ofs << pos << " " << ptdranking[i].nombre << "\t " << ptdranking[i].puntuacion   << std::endl;
				pos++;
			}
		}
		
		ofs<< pos << " " << ptdranking[ind].nombre << "\t " << ptdranking[ind].puntuacion << std::endl;
		pos++;

		for (int i = 0; i < ultima_posicion; i++)
		{
			if ((std::stof(ptdranking[i].puntuacion) <= std::stof(ptdranking[ind].puntuacion)) && i !=ind)
			{
				ofs << pos << " " << ptdranking[i].nombre << "\t " << ptdranking[i].puntuacion << std::endl;
				pos++;
			}
		}

		ofs.close();
	}

	delete[] ptdranking;
	ptdranking = nullptr;
}

int Ranking::posicionJugador(const std::string& nombre) {
	for (int i = 0; i < ultima_posicion; i++)
		if (ptdranking[i].nombre == nombre)
			return i;

	return -1;
}

bool Ranking::jugadorExiste(std::string nombre_jugador) const {
	std::ifstream ifs(nombre_fichero);
	std::string str = "";
	std::string token = "";
	std::string nombre = "";

	std::getline(ifs, str);
	std::getline(ifs, str);

	while (std::getline(ifs, str)) {
		std::stringstream ss;
		ss << str;
		ss >> token >> nombre;

		if (nombre == nombre_jugador)
			return 1;
	}

	ifs.close();

	return 0;
}