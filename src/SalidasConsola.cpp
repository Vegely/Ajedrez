#include "SalidasConsola.h"

#include <iostream>

using namespace std;

int SalidasConsola::enRango(int nElem)
{
	while(true)
	{
		string str;
		cin >> str;

		int aux = str.at(0) - 49;
		if (str.size() == 1 && aux >= 0 && aux < nElem) { cout << "\n\n"; return aux; }
	}
}

ConfiguracionDeJuego SalidasConsola::seleccionarModoDeJuego()
{
	cout << "\tSeleccione el modo de juego:\n\t\t1. Dos Jugadores\n\t\t2. Un jugador contra la IA\n\t\t3. Dos IAs enfrentadas\n";

	ConfiguracionDeJuego config;
	switch (enRango(3))
	{
	case 0:
		config[0] = ConfiguracionDeJuego::FormasDeInteraccion::LOCAL;
		config[1] = ConfiguracionDeJuego::FormasDeInteraccion::LOCAL;
		break;
	case 1:
		cout << "\tEl jugador es blancas?\n\t\t1. Si\n\t\t2. No\n";
		switch (enRango(2))
		{
		case 0:
			config[0] = ConfiguracionDeJuego::FormasDeInteraccion::IA;
			config[1] = ConfiguracionDeJuego::FormasDeInteraccion::LOCAL;
			break;
		case 1:
			config[0] = ConfiguracionDeJuego::FormasDeInteraccion::LOCAL;
			config[1] = ConfiguracionDeJuego::FormasDeInteraccion::IA;
			break;
		}
		
		break;
	case 2:
		config[0] = ConfiguracionDeJuego::FormasDeInteraccion::IA;
		config[1] = ConfiguracionDeJuego::FormasDeInteraccion::IA;
		break;
	}

	return config;
}

void SalidasConsola::mostrarResultado(const DatosFinal& datosFinal)
{
	switch (datosFinal.codigoFinal)
	{
	case CodigoFinal::JAQUE_MATE:
		cout << "\tJaque Mate\n";
		if (datosFinal.ganaBlanco) cout << "\tGana blanco";
		else cout << "\tGana negro";
		break;
	case CodigoFinal::REY_AHOGADO:
		cout << "\tTablas por rey ahogado";
		break;
	case CodigoFinal::TABLAS_POR_MATERIAL_INSUFICIENTE:
		cout << "\tTablas por material insuficiente";
		break;
	case CodigoFinal::TABLAS_POR_REPETICION:
		cout << "\tTablas por repeticion";
		break;
	case CodigoFinal::TABLAS_POR_PASIVIDAD:
		cout << "\tTablas por hacer 50 movimientos sin mover peones ni comer";
		break;
	}
	cout << "\n\n";
}

bool SalidasConsola::salir()
{
	cout << "\tQuiere jugar otra partida?\n\t\t1. Si\n\t\t2. No\n";

	return enRango(2);
}