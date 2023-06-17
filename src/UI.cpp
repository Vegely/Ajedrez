#include "UI.h"


void PantallaInicio::dibuja()
{
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(ruta.c_str()).id);
}

void PantallaGuardar::escrituraGlut()
{
	ETSIDI::setFont(RUTA_FUENTES, 30);
	ETSIDI::setTextColor(0, 0, 0);

	ETSIDI::printxy(snombre_partida.c_str(), -5, 8, 1);
	ETSIDI::printxy(sblancas.c_str(), -20, -1, 1);
	ETSIDI::printxy(snegras.c_str(), 7, -1, 1);


}

