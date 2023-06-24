#include "MotorDeJuego.h"
#include "Callbacks.h"
#include "Ranking.h"
#include "Partida.h"

#include "Sonidos.h"

#include <stdlib.h>

#define WINDOWS

int main(int argc, char** argv)
{
	srand(time(NULL)); // Inicializar la semilla aleatoria con el tiempo del sistema
	
	motorGrafico(&argc, argv);
	
	return 0;
}

#ifdef WINDOWS
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, int nCmdShow)
{
	return main(__argc, __argv);
}
#endif // WINDOWS