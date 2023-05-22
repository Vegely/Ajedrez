#include "InfoTablas.h"

void InfoTablas::add(const Tablero tablero)
{
	auto iterator = std::find(posiciones.begin(), posiciones.end(), tablero);
	if (iterator != posiciones.end())
	{
		if(repeticiones.at(iterator-posiciones.begin())++ == 3) boolRepeticion = true;
	}
	else
	{
		posiciones.push_back(tablero);
		repeticiones.push_back(1);
	}
	contadorJugadas++;
}