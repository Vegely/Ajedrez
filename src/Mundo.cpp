#define _USE_MATH_DEFINES

#include "Mundo.h"
#include "Tablero.h"

#include <ETSIDI.h>
#include <string>
#include <cmath>

Mundo::Mundo(void) :
	rey_blanco(1),
	rey_negro(1),
	damas_blancas(9),
	damas_negras(9),
	alfiles_blancos(10),
	alfiles_negros(10),
	caballos_blancos(10),
	caballos_negros(10),
	torres_blancas(10),
	torres_negras(10),
	peones_blancos(8),
	peones_negros(8),
	coronacion_blancos(4),
	coronacion_negros(4),
	posicion_leida(),
	casillas_px(),
	casillas_blancas(),
	casillas_negras(),
	casillas_seleccionadas(20),
	casillas_comibles(20),
	casillas_puede_mover(20),
	casillas_coronacion(20),
	casillas_ultimo_mov(2),
	casillas_jaque(10),
	marcos(4),
	letras(),
	fondoA(),
	fondoB(),
	camara(Camara::white_pov),
	peon(),
	alfil(),
	dama(),
	rey(),
	torre(),
	caballo(),
	casilla(),
	marco(),
	modelo_peon_blanco(ruta_textura_blanco),
	modelo_alfil_blanco(ruta_textura_blanco),
	modelo_dama_blanca(ruta_textura_blanco),
	modelo_rey_blanco(ruta_textura_blanco),
	modelo_torre_blanca(ruta_textura_blanco),
	modelo_caballo_blanco(ruta_textura_blanco),
	modelo_peon_negro(ruta_textura_negro),
	modelo_alfil_negro(ruta_textura_negro),
	modelo_dama_negra(ruta_textura_negro),
	modelo_rey_negro(ruta_textura_negro),
	modelo_torre_negra(ruta_textura_negro),
	modelo_caballo_negro(ruta_textura_negro),
	modelo_casilla_seleccionada(ruta_textura_casilla_seleccionada),
	modelo_casilla_comible(ruta_textura_casilla_comible),
	modelo_casilla_puede_mover(ruta_textura_casilla_puede_mover),
	modelo_casilla_coronacion(ruta_textura_casilla_coronacion),
	modelo_casilla_ultimo_mov(ruta_textura_casilla_ultimo_mov),
	modelo_casilla_jaque(ruta_textura_casilla_jaque),
	modelo_marco(ruta_textura_marco)
{

}

void Mundo::init(void)
{
	asignarModelosBase();
	cargarTexturasBase();
	asignarModelos();
	cargarTexturas();
}

void Mundo::asignarModelosBase(void)
{
	peon   .cargarModelo(ruta_modelo_peon);
	alfil  .cargarModelo(ruta_modelo_alfil);
	dama   .cargarModelo(ruta_modelo_dama);
	rey    .cargarModelo(ruta_modelo_rey);
	torre  .cargarModelo(ruta_modelo_torre);
	caballo.cargarModelo(ruta_modelo_caballo);
	casilla.cargarModelo(ruta_modelo_casilla);
	marco  .cargarModelo(ruta_modelo_marco);
}

void Mundo::cargarTexturasBase(void)
{
	modelo_peon_blanco         .cargarTextura(&peon);
	modelo_alfil_blanco        .cargarTextura(&alfil);
	modelo_dama_blanca         .cargarTextura(&dama);
	modelo_rey_blanco          .cargarTextura(&rey);
	modelo_torre_blanca        .cargarTextura(&torre);
	modelo_caballo_blanco      .cargarTextura(&caballo);
	modelo_peon_negro          .cargarTextura(&peon);
	modelo_alfil_negro         .cargarTextura(&alfil);
	modelo_dama_negra          .cargarTextura(&dama);
	modelo_rey_negro           .cargarTextura(&rey);
	modelo_torre_negra         .cargarTextura(&torre);
	modelo_caballo_negro       .cargarTextura(&caballo);
	modelo_casilla_seleccionada.cargarTextura(&casilla);
	modelo_casilla_comible     .cargarTextura(&casilla);
	modelo_casilla_puede_mover .cargarTextura(&casilla);
	modelo_casilla_coronacion  .cargarTextura(&casilla);
	modelo_casilla_ultimo_mov  .cargarTextura(&casilla);
	modelo_casilla_jaque       .cargarTextura(&casilla);
	modelo_marco			   .cargarTextura(&marco);
}

void Mundo::asignarModelos(void)
{
	for (int i = 0; i < 20; i++)
	{
		casillas_seleccionadas.addElem(new Modelo(OBJETO, Posicion(), &modelo_casilla_seleccionada));
		casillas_comibles     .addElem(new Modelo(OBJETO, Posicion(), &modelo_casilla_comible));
		casillas_puede_mover  .addElem(new Modelo(OBJETO, Posicion(), &modelo_casilla_puede_mover));
		casillas_coronacion   .addElem(new Modelo(OBJETO, Posicion(), &modelo_casilla_coronacion));
		casillas_ultimo_mov   .addElem(new Modelo(OBJETO, Posicion(), &modelo_casilla_ultimo_mov));
		casillas_jaque		  .addElem(new Modelo(OBJETO, Posicion(), &modelo_casilla_jaque));
	}

	casillas_blancas = new Modelo(NONE, Point::zero, ruta_modelo_casillas_blancas, ruta_textura_blanco_oscuro);
	casillas_negras  = new Modelo(NONE, Point::zero, ruta_modelo_casillas_negras,  ruta_textura_negro_claro);
	letras			 = new Modelo(NONE, Point::zero, ruta_modelo_letras,		   ruta_textura_letras);
	fondoA			 = new Modelo(NONE, Point::zero, ruta_modelo_fondo,			   ruta_textura_fondo);	
	fondoB			 = new Modelo(NONE, Point::zero, ruta_modelo_fondo,			   ruta_textura_fondo);	

	rey_blanco.addElem(new Modelo(REY, Posicion(), &modelo_rey_blanco, true));
	rey_negro .addElem(new Modelo(REY, Posicion(), &modelo_rey_negro,  false));

	coronacion_blancos.addElem(new Modelo(ALFIL,   Posicion(2, 3), &modelo_alfil_blanco,   true));
	coronacion_blancos.addElem(new Modelo(TORRE,   Posicion(3, 3), &modelo_torre_blanca,   true));
	coronacion_blancos.addElem(new Modelo(DAMA,    Posicion(4, 3), &modelo_dama_blanca,    true));
	coronacion_blancos.addElem(new Modelo(CABALLO, Posicion(5, 3), &modelo_caballo_blanco, true));
	coronacion_negros .addElem(new Modelo(ALFIL,   Posicion(2, 4), &modelo_alfil_negro,    false));
	coronacion_negros .addElem(new Modelo(TORRE,   Posicion(3, 4), &modelo_torre_negra,    false));
	coronacion_negros .addElem(new Modelo(DAMA,    Posicion(4, 4), &modelo_dama_negra,     false));
	coronacion_negros .addElem(new Modelo(CABALLO, Posicion(5, 4), &modelo_caballo_negro,  false));

	for (int i = 0; i < 10; i++)
	{
		peones_blancos  .addElem(new Modelo(PEON,    Posicion(), &modelo_peon_blanco,    true));
		peones_negros   .addElem(new Modelo(PEON,    Posicion(), &modelo_peon_negro,     false));
		damas_blancas   .addElem(new Modelo(DAMA,    Posicion(), &modelo_dama_blanca,    true));
		damas_negras    .addElem(new Modelo(DAMA,    Posicion(), &modelo_dama_negra,     false));
		torres_blancas  .addElem(new Modelo(TORRE,   Posicion(), &modelo_torre_blanca,   true));
		torres_negras   .addElem(new Modelo(TORRE,   Posicion(), &modelo_torre_negra,    false));
		caballos_blancos.addElem(new Modelo(CABALLO, Posicion(), &modelo_caballo_blanco, true));
		caballos_negros .addElem(new Modelo(CABALLO, Posicion(), &modelo_caballo_negro,  false));
		alfiles_blancos .addElem(new Modelo(ALFIL,   Posicion(), &modelo_alfil_blanco,   true));
		alfiles_negros  .addElem(new Modelo(ALFIL,   Posicion(), &modelo_alfil_negro,    false));

		marcos.addElem(new Modelo(NONE, Point::zero, &modelo_marco));
	}

	posicion_leida = Posicion();
}

void Mundo::cargarTexturas(void)
{
	casillas_blancas->cargarTextura();
	casillas_negras	->cargarTextura();
	letras			->cargarTextura();
	fondoA			->cargarTextura();
	fondoB			->cargarTextura();
}

void Mundo::renderizarModelos(void)
{
	if (!coronando_blancas && !coronando_negras)
	{
		rey_blanco			  .renderModelos();
		rey_negro			  .renderModelos();
		damas_blancas		  .renderModelos();
		damas_negras		  .renderModelos();
		alfiles_blancos		  .renderModelos();
		alfiles_negros		  .renderModelos();
		caballos_blancos	  .renderModelos();
		caballos_negros		  .renderModelos();
		torres_blancas		  .renderModelos();
		torres_negras		  .renderModelos();
		peones_blancos		  .renderModelos();
		peones_negros		  .renderModelos();
		casillas_comibles	  .renderModelos();
		casillas_coronacion	  .renderModelos();
		casillas_seleccionadas.renderModelos();
		casillas_puede_mover  .renderModelos();
		casillas_ultimo_mov	  .renderModelos();
		casillas_jaque		  .renderModelos();
	}
	else if (coronando_blancas && !coronando_negras)
		coronacion_blancos.renderModelos();
	else if (coronando_negras && !coronando_blancas)
		coronacion_negros .renderModelos();

	casillas_blancas->render();
	casillas_negras ->render();
	letras->render();
	marcos.renderConRotacion();

	//glScalef(4, 4, 4);
	glRotatef(90, 0, 0, 1);
	glRotatef(Camara::phi * 2, 1, 0, 0);
	fondoB->render();
	glRotatef(-Camara::phi * 2, 1, 0, 0);
	glRotatef(-90, 0, 0, 1);
	//glScalef(0.25f, 0.25f, 0.25f);
}

void Mundo::seleccionCasilla(int button, int state, int x_mouse, int y_mouse)
{
	if (state == 1 || button != 0)
		return;

	Posicion result = Posicion{ -1, -1 };
	Corners<Point> slot;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			slot = casillas_px.getSlotCoords(i, j);
			if (x_mouse < slot.lr.x && x_mouse > slot.ll.x && y_mouse < slot.ll.y && y_mouse > slot.ul.y)
				result = Posicion{ i, j };
		}
	}

	if (!camara.getGirado())
	{
		result.x = 7 - result.x;
		result.y = 7 - result.y;
	}

	this->posicion_leida = result;
}

void Mundo::moverModelos(const Movimiento& mov)
{
	if (mov.inicio != Posicion{-1, -1} && mov.fin != Posicion{ -1, -1 })
	{
		rey_blanco      .moverModelos(mov);
		rey_negro       .moverModelos(mov);
		damas_blancas   .moverModelos(mov);
		damas_negras    .moverModelos(mov);
		alfiles_blancos .moverModelos(mov);
		alfiles_negros  .moverModelos(mov);
		caballos_blancos.moverModelos(mov);
		caballos_negros .moverModelos(mov);
		torres_blancas  .moverModelos(mov);
		torres_negras   .moverModelos(mov);
		peones_blancos  .moverModelos(mov);
		peones_negros   .moverModelos(mov);
	}
}

void Mundo::movimiento(const float time)
{ 
	camara.movement(time);
	camara.motion(time);
}

ListaModelo* Mundo::seleccionarLista(bool color, Pieza::tipo_t tipo_pieza)
{
	switch (tipo_pieza)
	{
	case Pieza::tipo_t::REY:
		if (color)
			return &rey_blanco;
		else
			return &rey_negro;
		break;

	case Pieza::tipo_t::DAMA:
		if (color)
			return &damas_blancas;
		else
			return &damas_negras;
		break;

	case Pieza::tipo_t::ALFIL:
		if (color)
			return &alfiles_blancos;
		else
			return &alfiles_negros;
		break;

	case Pieza::tipo_t::CABALLO:
		if (color)
			return &caballos_blancos;
		else
			return &caballos_negros;
		break;

	case Pieza::tipo_t::TORRE:
		if (color)
			return &torres_blancas;
		else
			return &torres_negras;
		break;

	case Pieza::tipo_t::PEON:
		if (color)
			return &peones_blancos;
		else
			return &peones_negros;
		break;

	default:
		return nullptr;
		break;
	}
}

Pieza::tipo_t Mundo::seleccionPiezaCoronacion(bool color)
{
	if (color) this->coronando_blancas = true;
	else	   this->coronando_negras  = true;

	Posicion& posicion = this->posicion_leida;
	while (posicion.y != 3 || posicion.y != 4 || posicion.x != 2 || posicion.x != 3 || posicion.x != 4 || posicion.x != 5)
	{
		if ((posicion.y == 3 && color) || (posicion.y == 4 && !color))
		{
			switch (posicion.x)
			{
			case 2:
				this->coronando_blancas = false;
				this->coronando_negras  = false;
				return Pieza::tipo_t::ALFIL;
				break;
			case 3:
				this->coronando_blancas = false;
				this->coronando_negras  = false;
				return Pieza::tipo_t::TORRE;
				break;
			case 4:
				this->coronando_blancas = false;
				this->coronando_negras  = false;
				return Pieza::tipo_t::DAMA;
				break;
			case 5:
				this->coronando_blancas = false;
				this->coronando_negras  = false;
				return Pieza::tipo_t::CABALLO;
				break;
			}
		}
	}
}

Pieza::tipo_t Mundo::getTipoFromCoords(const Posicion& pos) const
{
	if      (rey_blanco      .getTipo(pos) != Pieza::tipo_t::NULA) return rey_blanco      .getTipo(pos);
	else if (rey_negro       .getTipo(pos) != Pieza::tipo_t::NULA) return rey_negro       .getTipo(pos);
	else if (damas_blancas   .getTipo(pos) != Pieza::tipo_t::NULA) return damas_blancas   .getTipo(pos);
	else if (damas_negras    .getTipo(pos) != Pieza::tipo_t::NULA) return damas_negras    .getTipo(pos);
	else if (alfiles_blancos .getTipo(pos) != Pieza::tipo_t::NULA) return alfiles_blancos .getTipo(pos);
	else if (alfiles_negros  .getTipo(pos) != Pieza::tipo_t::NULA) return alfiles_negros  .getTipo(pos);
	else if (caballos_blancos.getTipo(pos) != Pieza::tipo_t::NULA) return caballos_blancos.getTipo(pos);
	else if (caballos_negros .getTipo(pos) != Pieza::tipo_t::NULA) return caballos_negros .getTipo(pos);
	else if (torres_blancas  .getTipo(pos) != Pieza::tipo_t::NULA) return torres_blancas  .getTipo(pos);
	else if (torres_negras   .getTipo(pos) != Pieza::tipo_t::NULA) return torres_negras   .getTipo(pos);
	else if (peones_blancos  .getTipo(pos) != Pieza::tipo_t::NULA) return peones_blancos  .getTipo(pos);
	else if (peones_negros   .getTipo(pos) != Pieza::tipo_t::NULA) return peones_negros   .getTipo(pos);
	else return Pieza::tipo_t::NULA;
}

bool Mundo::getColorFromCoords(const Posicion& pos) const
{
	if      (rey_blanco      .getTipo(pos) != Pieza::tipo_t::NULA) return rey_blanco      .getColor(pos);
	else if (rey_negro       .getTipo(pos) != Pieza::tipo_t::NULA) return rey_negro       .getColor(pos);
	else if (damas_blancas   .getTipo(pos) != Pieza::tipo_t::NULA) return damas_blancas   .getColor(pos);
	else if (damas_negras    .getTipo(pos) != Pieza::tipo_t::NULA) return damas_negras    .getColor(pos);
	else if (alfiles_blancos .getTipo(pos) != Pieza::tipo_t::NULA) return alfiles_blancos .getColor(pos);
	else if (alfiles_negros  .getTipo(pos) != Pieza::tipo_t::NULA) return alfiles_negros  .getColor(pos);
	else if (caballos_blancos.getTipo(pos) != Pieza::tipo_t::NULA) return caballos_blancos.getColor(pos);
	else if (caballos_negros .getTipo(pos) != Pieza::tipo_t::NULA) return caballos_negros .getColor(pos);
	else if (torres_blancas  .getTipo(pos) != Pieza::tipo_t::NULA) return torres_blancas  .getColor(pos);
	else if (torres_negras   .getTipo(pos) != Pieza::tipo_t::NULA) return torres_negras   .getColor(pos);
	else if (peones_blancos  .getTipo(pos) != Pieza::tipo_t::NULA) return peones_blancos  .getColor(pos);
	else if (peones_negros   .getTipo(pos) != Pieza::tipo_t::NULA) return peones_negros   .getColor(pos);
	else return false;
}

void Mundo::actualizarCamara(bool turno, float time, const ConfiguracionDeJuego& config)
{
	ConfiguracionDeJuego::FormasDeInteraccion local = ConfiguracionDeJuego::FormasDeInteraccion::LOCAL;
	ConfiguracionDeJuego::FormasDeInteraccion ia = ConfiguracionDeJuego::FormasDeInteraccion::IA;
	ConfiguracionDeJuego::FormasDeInteraccion emisor = ConfiguracionDeJuego::FormasDeInteraccion::EMISOR;
	ConfiguracionDeJuego::FormasDeInteraccion receptor = ConfiguracionDeJuego::FormasDeInteraccion::RECEPTOR;

	if (config[0] == local && config[1] == local)
	{
		if (turno && !this->getGirado())
			this->cambiarGirado();
		else if (!turno && this->getGirado())
			this->cambiarGirado();
	}
	else if (config[0] == local && config[1] == ia)
	{
		if (this->getGirado())
			this->cambiarGirado();
	}
	else if (config[0] == ia && config[1] == local)
	{
		if (!this->getGirado())
			this->cambiarGirado();
	}
	else if (config[0] == ia && config[1] == ia)
	{
		camara.setPosition(Point{ Camara::radius, Camara::height, Camara::radius });
		return;
	}
	else if (config[0] == emisor)
	{
		if (this->getGirado())
			this->cambiarGirado();
		camara.setAngle(M_PI_2);
	}
	else if (config[0] == receptor)
	{
		if (!this->getGirado())
			this->cambiarGirado();
		camara.setAngle(-M_PI_2);
	}

	camara.movement(time);
}

void Mundo::resetCasillas(void)
{
	for (int i = 0; i < this->casillas_comibles.getNumElem(); i++)
		this->casillas_comibles.setPosicion(i, Posicion());

	for (int i = 0; i < this->casillas_seleccionadas.getNumElem(); i++)
		this->casillas_seleccionadas.setPosicion(i, Posicion());

	for (int i = 0; i < this->casillas_puede_mover.getNumElem(); i++)
		this->casillas_puede_mover.setPosicion(i, Posicion());

	for (int i = 0; i < this->casillas_coronacion.getNumElem(); i++)
		this->casillas_coronacion.setPosicion(i, Posicion());
}

void Mundo::resetCasillas(ListaModelo* lista)
{
	for (int i = 0; i < lista->getNumElem(); i++)
		lista->setPosicion(i, Posicion());
}

void Mundo::leerTablero(Tablero* tablero)
{
	if (tablero == nullptr) return;

	reiniciarTablero();
	for (int i = 0; i < 64; i++)
	{
		Pieza* pieza_leida = tablero->leer(Posicion(i % 8, i / 8));
		if (pieza_leida != nullptr)
		{
			ListaModelo* lista = seleccionarLista(pieza_leida->getColor(), pieza_leida->getTipo());
			if (lista != nullptr) lista->moverElemento(Movimiento(Posicion(), Posicion(i % 8, i / 8)));
		}
	}
}

void Mundo::reiniciarTablero(void)
{
	rey_blanco.setPosicion(Posicion());
	rey_negro .setPosicion(Posicion());

	peones_blancos.setPosicion(Posicion());
	peones_negros .setPosicion(Posicion());

	damas_blancas.setPosicion(Posicion());
	damas_negras .setPosicion(Posicion());

	torres_blancas.setPosicion(Posicion());
	torres_negras .setPosicion(Posicion());

	caballos_blancos.setPosicion(Posicion());
	caballos_negros .setPosicion(Posicion());

	alfiles_blancos.setPosicion(Posicion());
	alfiles_negros .setPosicion(Posicion());
}

void Mundo::antisolapamientoCasillas(const Tablero& tablero)
{
	// Comprobación de que la casilla de ultimo movimiento no coincida con otra.
	this->resetCasillas(this->getCasillaUltimoMov());
	this->getCasillaUltimoMov()->moverElemento(Movimiento(Posicion(), tablero.getUltimaJugada().inicio));
	this->getCasillaUltimoMov()->moverElemento(Movimiento(Posicion(), tablero.getUltimaJugada().fin));
	for (int i = 0; i < 2; i++)
	{
		bool erase = false;
		Posicion pos = this->getCasillaUltimoMov()->getPosicion(i);
		for (int i = 0; i < this->getCasillaComible()->size(); i++) if (this->getCasillaComible()->getPosicion(i) == pos) erase = true;
		for (int i = 0; i < this->getCasillaSeleccionada()->size(); i++) if (this->getCasillaSeleccionada()->getPosicion(i) == pos) erase = true;
		for (int i = 0; i < this->getCasillaPuedeMover()->size(); i++) if (this->getCasillaPuedeMover()->getPosicion(i) == pos) erase = true;
		for (int i = 0; i < this->getCasillaCoronacion()->size(); i++) if (this->getCasillaCoronacion()->getPosicion(i) == pos) erase = true;
		for (int i = 0; i < this->getCasillaJaque()->size(); i++) if (this->getCasillaJaque()->getPosicion(i) == pos) erase = true;
		if (erase)
			this->getCasillaUltimoMov()->moverElemento(Movimiento(pos, Posicion()));
	}
}