#include "UI.h"

void PantallaGuardar::escrituraGlut()
{
	ETSIDI::setFont(RUTA_FUENTES, 30);

	if (existe) {
		ETSIDI::setTextColor(255, 0, 0);
		ETSIDI::printxy("La partida ya existe!",-10,8,1);
	}
	else
	{
		ETSIDI::setTextColor(0, 0, 0);
		ETSIDI::printxy(snombre_partida.c_str(), -5, 8, 1);
	}

	ETSIDI::setTextColor(0, 0, 0);
	if (sblancas == JIA)
		ETSIDI::setTextColor(255, 0, 0);
	ETSIDI::printxy(sblancas.c_str(), -20, -1, 1);
	
	ETSIDI::setTextColor(0, 0, 0);
	if (snegras == JIA)
		ETSIDI::setTextColor(255, 0, 0);
	ETSIDI::printxy(snegras.c_str(), 7, -1, 1);
	ETSIDI::setTextColor(0, 0, 0);
}
