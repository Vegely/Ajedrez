#include "MotorDeJuego.h"
#include "SalidasConsola.h"
#include "Callbacks.h"
#include "Partida.h"



int main(int argc, char* argv[])
{
	//motorGrafico(&argc, argv);
	Partida p;
	p.getNombre() = "mi_partida.txt";
	p.cargarPartida();
	std::cout << std::endl << p;
	
	/*srand(2); // Inicializar la semilla aleatoria con el tiempo del sistema

	bool exit = false;
	while (!exit)
	{
		// Config
		MotorDeJuego motorDeJuego(SalidasConsola::seleccionarModoDeJuego());

		// Juego
		SalidasConsola::mostrarResultado(motorDeJuego.motor());


		// Final
		exit = SalidasConsola::salir();
	}*/

	return 0;
}