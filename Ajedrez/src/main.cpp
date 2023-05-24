

#include "MotorDeJuego.h"
#include <iostream>
#include "graphics.h"


//////////////////
#include <string>
#include <cctype>
using namespace std;

Posicion getInput()
{
	string input;

	cin >> input;

	int letra = toupper(input[0]) - 65;
	int numero = input[1] - 49;
	if (letra >= 0 && letra < 8 && numero >= 0 && numero < 8) return Posicion(letra, numero);

	return Posicion(-1, -1);
}
//////////////////

int main(int argc, char* argv[])
{
	//////////Setup/////////
	MotorDeJuego juego;
	////////////////////////

	DatosFinal datosFinal;
	bool exit = false;
	bool pos1Selec = false;
	while(!exit)
	{
		Movimiento movimiento = juego.ensamblarMovimiento(getInput(), pos1Selec);
		
		if (movimiento != Movimiento(Posicion(), Posicion(-1, -1)))
		{
			pos1Selec = !juego.hacerJugada(movimiento);

			if (!pos1Selec) // Se hace la jugada
			{
				// se cambia el timer

				if (juego.jaqueMate())
				{
					datosFinal = { juego.colorDelTurno(), CodigoFinal::JAQUE_MATE };
					exit = true;
				}
				else if (juego.tablasPorMaterialInsuficiente())
				{
					datosFinal.codigoFinal = CodigoFinal::TABLAS_POR_MATERIAL_INSUFICIENTE;
					cout << "Tablas por material insuficiente";
					exit = true;
				}
				else if (juego.tablasPorRepeticion())
				{
					datosFinal.codigoFinal = CodigoFinal::TABLAS_POR_REPETICION;
					cout << "Tablas por repeticion";
					exit = true;
				}
				else if (juego.tablasPorPasividad())
				{
					datosFinal.codigoFinal = CodigoFinal::TABLAS_POR_PASIVIDAD;
					cout << "Tablas por pasividad";
					exit = true;
				}
			}
		}
	}

	if (datosFinal.codigoFinal == CodigoFinal::JAQUE_MATE)
		if (datosFinal.ganador) cout << "Gana blanco";
		else cout << "Gana negro";

	return 0;
}