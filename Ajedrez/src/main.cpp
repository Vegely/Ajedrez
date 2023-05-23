

#include "MotorDeJuego.h"
#include <iostream>
#include "graphics.h"


//////////////////ihiu
#include <string>
#include <cctype>
using namespace std;

Posicion getInput()
{
	string input;

	cin >> input;

	int letra = toupper(input[0]) - 65;
	int numero = toupper(input[1]) - 49;
	if (letra >= 0 && letra < 8 && numero >= 0 && numero < 8) return Posicion(letra, numero);

	return Posicion(-1, -1);
}
//////////////////

int main(int argc, char* argv[])
{
	MotorDeJuego juego;

	bool exit = false;
	bool pos1Selec = false;
	while(!exit)
	{
		Movimiento movimiento = juego.ensamblarMovimiento(getInput(), pos1Selec);
		
		if (movimiento != Movimiento(Posicion(), Posicion(-1, -1)))
		{
			pos1Selec = !juego.hacerJugada(movimiento);
			// se cambia el timer si se hace la jugada.
		}
	}
	


	return 0;
}