#include "UI.h"
#include <filesystem>
#include <vector>
#include "Ranking.h"

void PantallaGuardar::escrituraGlut()
{
	ETSIDI::setFont(RUTA_FUENTES, 30);

	if (existe) {
		ETSIDI::setTextColor(255, 0, 0);
		ETSIDI::printxy("La partida ya existe!",-10,8,1);
	}
	else
	{
		ETSIDI::setTextColor(0, 0, 0);
		ETSIDI::printxy(snombre_partida.c_str(), -5, 8, 1);
	}

	ETSIDI::setTextColor(0, 0, 0);
	if (sblancas == JIA)
		ETSIDI::setTextColor(255, 0, 0);
	ETSIDI::printxy(sblancas.c_str(), -20, -1, 1);
	
	ETSIDI::setTextColor(0, 0, 0);
	if (snegras == JIA)
		ETSIDI::setTextColor(255, 0, 0);
	ETSIDI::printxy(snegras.c_str(), 7, -1, 1);
	ETSIDI::setTextColor(0, 0, 0);
}
void PantallaCargarPartida::escrituraGlut() {
	std::vector<std::string> str_vec{};

	ETSIDI::setFont(RUTA_FUENTES, 30);
	ETSIDI::setTextColor(0, 0, 0);

	for (const auto& fichero : std::filesystem::directory_iterator(CARPETA_NOFINALIZADAS))
		str_vec.push_back(fichero.path().generic_string());

	npaginas = str_vec.size() / JUGADORES_POR_HOJA;

	if (npaginas == 0) {
		for (int i = 0; i < str_vec.size(); i++) 
		{
			ETSIDI::printxy(str_vec[i].substr(14).c_str(), -5, floor(ALTO_GL - ALTO_GL / 2) - 3 * i - 10);
			rellenaNombre(i, str_vec[i].substr(14).c_str());
		}
	}
	else {
		int i = pagina_actual * PARTIDAS_POR_HOJA, j = 0;

		for (i; i < pagina_actual * PARTIDAS_POR_HOJA + JUGADORES_POR_HOJA; i++) {
			if(i<str_vec.size())
			{
				ETSIDI::printxy(str_vec[i].substr(14).c_str(), -5, floor(ALTO_GL - ALTO_GL / 2) - 3 * j - 10);
				rellenaNombre(j, str_vec[i].substr(14).c_str());
				j++;
			}
		}
	}
}

void PantallaCargarPartida::rellenaNombre(int i, std::string str) {
	switch (i) {
	case 0:
		p1_nombre = CARPETA_NOFINALIZADAS + str;
		break;
	case 1:
		p2_nombre = CARPETA_NOFINALIZADAS + str;
		break;
	case 2:
		p3_nombre = CARPETA_NOFINALIZADAS + str;
		break;
	case 3:
		p4_nombre = CARPETA_NOFINALIZADAS + str;
		break;
	case 5:
		p5_nombre = CARPETA_NOFINALIZADAS + str;
		break;
	}
}
