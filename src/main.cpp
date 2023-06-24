#include "MotorDeJuego.h"
#include "Callbacks.h"
#include "Ranking.h"
#include "Partida.h"

#include "Sonidos.h"
int main(int argc, char** argv)
{
	srand(time(NULL)); // Inicializar la semilla aleatoria con el tiempo del sistema
	
	motorGrafico(&argc, argv);
	
	return 0;
}