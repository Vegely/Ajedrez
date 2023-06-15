#include "UI.h"


void PantallaInicio::dibuja()
{
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(ruta.c_str()).id);
	nuevaPartida.dibuja();
	cargarPartida.dibuja();
	mostrarRankings.dibuja();
	salir.dibuja();
}


