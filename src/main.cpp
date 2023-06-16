#include "MotorDeJuego.h"
#include "SalidasConsola.h"
#include "Callbacks.h"

int main(int argc, char** argv)
{
	srand(2); // Inicializar la semilla aleatoria con el tiempo del sistema

	bool exit = false;
	while (!exit)
	{
		//MotorDeJuego motorDeJuego(SalidasConsola::seleccionarModoDeJuego());

		//SalidasConsola::mostrarResultado(motorDeJuego.motor());

		//exit = SalidasConsola::salir();

		// TEST GRAFICOS //
		motorGrafico(&argc, argv);
	}

	return 0;
}