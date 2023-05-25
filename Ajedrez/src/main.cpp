#include "MotorDeJuego.h"
#include "graphics.h"

//////////////////////////
#include <iostream>

using namespace std;
///////////////////////

int main(int argc, char* argv[])
{
	/////Mode selection/////
	ConfiguracionDeJuego config{ ConfiguracionDeJuego::FormasDeInteraccion::IA, ConfiguracionDeJuego::FormasDeInteraccion::IA };
	//////////Setup/////////
	MotorDeJuego juego(config);
	////////////////////////

	DatosFinal datosFinal = juego.motor();

	////////////Tratamiento de la salida////////////
	switch (datosFinal.codigoFinal)
	{
	case CodigoFinal::JAQUE_MATE:
		
		if (datosFinal.codigoFinal == CodigoFinal::JAQUE_MATE)
			if (datosFinal.ganador) cout << "Gana blanco";
			else cout << "Gana negro";

		break;
	case CodigoFinal::REY_AHOGADO:

		cout << "Tablas por rey ahogado";

		break;
	case CodigoFinal::TABLAS_POR_MATERIAL_INSUFICIENTE:

		cout << "Tablas por material insuficiente";

		break;
	case CodigoFinal::TABLAS_POR_REPETICION:

		cout << "Tablas por repeticion";

		break;
	case CodigoFinal::TABLAS_POR_PASIVIDAD:

		cout << "Tablas por pasividad";

		break;
	}
	//////////////////////////////////////////////////

	return 0;
}