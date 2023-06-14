#include "MotorDeJuego.h"
#include "SalidasConsola.h"

int main(int argc, char* argv[])
{
	srand(2); // Inicializar la semilla aleatoria con el tiempo del sistema

	bool exit = false;
	while (!exit)
	{
		// Config
		MotorDeJuego motorDeJuego(SalidasConsola::seleccionarModoDeJuego());

		// Juego
		SalidasConsola::mostrarResultado(motorDeJuego.motor());


		// Final
		exit = SalidasConsola::salir();
	}

	return 0;
}