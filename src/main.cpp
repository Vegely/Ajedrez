#include "MotorDeJuego.h"
#include "SalidasConsola.h"

int main(int argc, char* argv[])
{
	bool exit = false;
	while (!exit)
	{
		MotorDeJuego motorDeJuego(SalidasConsola::seleccionarModoDeJuego());

		SalidasConsola::mostrarResultado(motorDeJuego.motor());

		exit = SalidasConsola::salir();
	}

	return 0;
}