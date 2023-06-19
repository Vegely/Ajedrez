#include "MotorDeJuego.h"
//#include "SalidasConsola.h"
#include "Callbacks.h"

int main(int argc, char** argv)
{
	srand(2); // Inicializar la semilla aleatoria con el tiempo del sistema
	
	motorGrafico(&argc, argv);

	return 0;
}