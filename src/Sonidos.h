#pragma once
#include "ETSIDI.h"
#define SONIDO_JM "sonidos/son_jaquemate.wav"
#define SONIDO_J "sonidos/son_jaque.wav"
#define SONIDO_MOV "sonidos/son_mover.wav"
#define SONIDO_T "sonidos/son_tablas.wav"
#define SONIDO_SM "sonidos/son_menu.wav"
#define SONIDO_SP "sonidos/son_pieza.wav"
#define SONIDO_COM "sonidos/son_comer.wav"
#define SONIDO_COR "sonidos/son_coronar.wav"
#define SONIDO_CAP "sonidos/son_cap.wav"
class Sonidos
{
public:
	static void son_jaquemate();
	static void son_jaque();
	static void son_mover();
	static void son_tablas();
	static void son_seleccionMenu();
	static void son_seleccionPieza();
	static void son_comer();
	static void son_coronar();
	static void con_comerAlPaso();
};

