#include "Sonidos.h"

void Sonidos::son_jaquemate()
{
	ETSIDI::play(SONIDO_JM);
}

void Sonidos::son_jaque()
{
	ETSIDI::play(SONIDO_J);
}

void Sonidos::son_mover()
{
	ETSIDI::play(SONIDO_MOV);
}

void Sonidos::son_tablas()
{
	ETSIDI::play(SONIDO_T);
}

void Sonidos::son_seleccionMenu()
{
	ETSIDI::play(SONIDO_SM);
}

void Sonidos::son_seleccionPieza()
{
	ETSIDI::play(SONIDO_SP);
}

void Sonidos::son_comer()
{
	ETSIDI::play(SONIDO_COM);
}

void Sonidos::son_coronar()
{
	ETSIDI::play(SONIDO_COR);
}

void Sonidos::son_comerAlPaso()
{
	ETSIDI::play(SONIDO_CAP);
}

void Sonidos::mus_menu()
{
	ETSIDI::playMusica(MUSICA_MENU,true);
}

void Sonidos::mus_fin()
{
	ETSIDI::stopMusica();
}

void Sonidos::mus_juego()
{
	ETSIDI::playMusica(MUSICA_JUEGO, true);
}
