#include "NoFinalizadas.h"

Registro::Registro() {
	inicializaRegistro();
}

void Registro::inicializaRegistro() {
	std::fstream fs(nombre_registro, std::ios_base::in);

	//Si no existe el registro de partidas, se crea uno nuevo
	if (!fs.is_open()) {
		fs.close();
		fs.open(nombre_registro, std::ios_base::out);
		fs << "REGISTRO DE PARTIDAS" << std::endl;
		fs << "Numero de partidas: " << NPOS << std::endl;
		fs << "ID ultima partida: " << NPOS << std::endl;
		fs << "Partidas no finalizadas: " << NPOS << std::endl;
		fs << "- - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
	}
	//Si el registro existe, se inicializan los valores del registro
	else if (fs) {
		std::string str = "";
		size_t pos = 0;

		//Salta la primera línea (REGISTRO DE PARTIDAS)
		std::getline(fs, str);

		//Número de partidas (i = 1), ID última partida ( i = 2), partida no finalizada (i = 3)
		for (int i = 1; i < 4; i++) {
			std::getline(fs, str);
			//Ignora todos los caracteres hasta encontrar ":"
			pos = str.find(":", 0);

			if (pos != std::string::npos) {
				std::stringstream ss;

				//Manda al flujo todo lo que haya a partir de pos + 1
				ss << str.substr(pos + 1);

				switch (i) {
				//En la primera iteración lee el número de partidas
				case 1:
					ss >> numero_partidas;
					break;
				//En la segunda iteración lee el id de la última partida
				case 2:
					ss >> id_ultima_partida;
					break;
				//En la tercera iteración lee los ids de las partidas no finalizadas
				case 3:
					int val;
					//Puede haber varias partidas no finalizadas --> Se almacenan en un vector
					while (ss >> val)
						no_finalizadas.push_back(val);
					break;
				default:
					std::cerr << "Error en la lectura";
				}
			}
		}
	}
	//En cualquier otro caso se ha producido un error abriendo el registro
	else
		std::cerr << "Error al abrir registro" << std::endl;
}

void Registro::actualizaRegistro() const {
	//std::fstream fs(nombre_registro, std)
}

