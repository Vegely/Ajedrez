#include "Mundo.h"
#include "Tablero.h"

#include <ETSIDI.h>
#include <string>

CasillasTablero casillas_tablero_array;

Mundo::Mundo(void) :
	tablero_anterior(),
	tablero_actual(),
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
	casillas_blancas(),
	casillas_negras(),
	marcos(),
	letras(),
	camara({ 0.0f, 20.5f, -15.6f }),
	posicion_leida(),
	casillas_px()
{

}

void Mundo::init(void)
{
	asignarModelos();
	cargarTexturas();
}

void Mundo::asignarModelos(void)
{
	casillas_blancas = new Modelo(NONE, Posicion(0, 0), Modelo::ruta_modelo_casillas_blancas, Modelo::ruta_textura_blanco_oscuro);
	casillas_negras  = new Modelo(NONE, Posicion(0, 0), Modelo::ruta_modelo_casillas_negras,  Modelo::ruta_textura_negro_claro);
	marcos			 = new Modelo(NONE, Posicion(0, 0), Modelo::ruta_modelo_marcos,			  Modelo::ruta_textura_marco);
	letras			 = new Modelo(NONE, Posicion(0, 0), Modelo::ruta_modelo_letras,			  Modelo::ruta_textura_blanco);

	rey_blanco.addElem(new Modelo(REY, Posicion(4, 0), true ));
	rey_negro .addElem(new Modelo(REY, Posicion(4, 7), false));

	for (int i = 0; i < 9; i++)
	{
		if (i < 8)
		{
			// Peones
			peones_blancos.addElem(new Modelo(PEON, Posicion(i, 1), true));
			peones_negros .addElem(new Modelo(PEON, Posicion(i, 6), false));
		}
		// Damas
		if (i == 0)
		{
			damas_blancas.addElem(new Modelo(DAMA, Posicion(3, 0), true));
			damas_negras .addElem(new Modelo(DAMA, Posicion(3, 7), false));
		}
		else
		{
			damas_blancas.addElem(new Modelo(DAMA, Point{ 100, 0, 0 }, true));
			damas_negras .addElem(new Modelo(DAMA, Point{ 100, 0, 0 }, false));
		}
		// Resto
		if (i < 2)
		{
			torres_blancas.addElem(new Modelo(TORRE, Posicion(0 + i * 7, 0), true));
			torres_negras .addElem(new Modelo(TORRE, Posicion(0 + i * 7, 7), false));

			caballos_blancos.addElem(new Modelo(CABALLO, Posicion(1 + i * 5, 0), true));
			caballos_negros .addElem(new Modelo(CABALLO, Posicion(1 + i * 5, 7), false));

			alfiles_blancos.addElem(new Modelo(ALFIL, Posicion(2 + i * 3, 0), true));
			alfiles_negros .addElem(new Modelo(ALFIL, Posicion(2 + i * 3, 7), false));
		}
		else
		{
			torres_blancas.addElem(new Modelo(TORRE, Point{ 100, 0, 0 }, true));
			torres_negras.addElem(new Modelo(TORRE, Point{ 100, 0, 0 }, false));

			caballos_blancos.addElem(new Modelo(CABALLO, Point{ 100, 0, 0 }, true));
			caballos_negros.addElem(new Modelo(CABALLO, Point{ 100, 0, 0 }, false));

			alfiles_blancos.addElem(new Modelo(ALFIL, Point{ 100, 0, 0 }, true));
			alfiles_negros.addElem(new Modelo(ALFIL, Point{ 100, 0, 0 }, false));
		}
	}

	posicion_leida = Posicion{ -1, -1 };

	std::cout << "Modelos asignados." << std::endl;
}

void Mundo::cargarTexturas(void)
{
	rey_blanco       .cargarTexturas();
	rey_negro        .cargarTexturas();
	damas_blancas    .cargarTexturas();
	damas_negras     .cargarTexturas();
	alfiles_blancos  .cargarTexturas();
	alfiles_negros   .cargarTexturas();
	caballos_blancos .cargarTexturas();
	caballos_negros  .cargarTexturas();
	torres_blancas   .cargarTexturas();
	torres_negras    .cargarTexturas();
	peones_blancos   .cargarTexturas();
	peones_negros    .cargarTexturas();
	casillas_blancas->cargarTextura();
	casillas_negras ->cargarTextura();
	marcos          ->cargarTextura();
	letras          ->cargarTextura();
}

void Mundo::leerTablero(const Tablero& tablero)
{
	for (int i = 0; i < 64; i++)
	{
		tablero_anterior[i] = tablero_actual[i];
		if (tablero.leer(casillas_tablero_array[i]) != nullptr)
			tablero_actual[i] = DatosPieza { 
			tablero.leer(casillas_tablero_array[i])->getColor(),
			tablero.leer(casillas_tablero_array[i])->getTipo(), 
			tablero.leer(casillas_tablero_array[i])->getPosicion(), 
			true };
		else
			tablero_actual[i].valido = false;

		bool flag_coronacion = false;

		// DEBUG
		//std::cout << "i: " << i << std::endl
		//	<< "Coords: " << casillas_tablero_array[i].x << casillas_tablero_array[i].y << std::endl
		//	<< "Turno: " << tablero.getTurno() << std::endl;
		//if (tablero_anterior[i].valido)
		//{
		//	std::cout << "Pieza anterior: " << static_cast<const int>(tablero_anterior[i].tipo) << std::endl
		//		<< "Color anterior: " << static_cast<const int>(tablero_anterior[i].color) << std::endl;
		//}
		//else
		//	std::cout << "Pieza no valida." << std::endl;
		//if (tablero_actual[i].valido)
		//{
		//	std::cout << "Pieza actual: " << static_cast<const int>(tablero_actual[i].tipo) << std::endl
		//			  << "Color actual: " << static_cast<const int>(tablero_actual[i].color) << std::endl;
		//}
		//else
		//	std::cout << "Pieza no valida." << std::endl;
		// END_DEBUG

		if (tablero_anterior[i].valido || tablero_actual[i].valido &&
			tablero_anterior[i] != tablero_actual[i]) // Si alguna casilla no sigue vacía y son distintas
		{ 
			// Movimiento normal
			if (!tablero_anterior[i].valido && tablero_actual[i].valido)
			{
				moverModelo(tablero.getUltimaJugada(), tablero_actual[i].color, tablero_actual[i].tipo);
			}
			// Captura al paso.
			if (tablero_anterior[i].valido && !tablero_actual[i].valido && tablero_anterior[i].tipo == Pieza::tipo_t::PEON) // Si una casilla pasa de estar ocupada a no estarlo
			{
				if (tablero.getUltimaJugada().inicio != tablero_anterior[i].posicion && tablero.getUltimaJugada().fin != tablero_anterior[i].posicion)
					seleccionarLista(tablero_anterior[i].color, tablero_anterior[i].tipo)->deleteFromCoord(tablero_anterior[i].posicion);
			}
			// Comidas
			else if (tablero_anterior[i].valido && tablero_actual[i].valido)
			{
				// Una ha comido a la otra. Se sustituye la nueva por la antigua.
				if (tablero_anterior[i].color != tablero_actual[i].color)
				{
					seleccionarLista(tablero_anterior[i].color, tablero_anterior[i].tipo)->
						deleteFromCoord(tablero_anterior[i].posicion);

					moverModelo(tablero.getUltimaJugada(), tablero_actual[i].color, tablero_actual[i].tipo);
				}
			}
			// Coronacion
			else if (tablero_anterior[i].tipo == Pieza::tipo_t::PEON && !tablero_actual[i].valido &&
				(tablero_anterior[i].posicion.y == 6 && tablero_anterior[i].color || tablero_anterior[i].posicion.y == 1 && !tablero_anterior[i].color))
			{
				seleccionarLista(tablero_anterior[i].color, Pieza::tipo_t::PEON)->deleteFromCoord(tablero_anterior[i].posicion); // Borrar el peón
				// Volver a leer el tablero porque han pasado dos cosas a la vez: destrucción del peón y promoción a la nueva pieza.
				for (int j = 0; j < 64; j++)
				{
					if (!tablero_anterior[j].valido && tablero_actual[j].valido ||
						(tablero_anterior[j].valido && tablero_actual[j].valido &&
						(tablero_anterior[j].color  != tablero_actual[j].color)))
					{
						moverModelo(Movimiento(Posicion(-1, -1), tablero_actual[j].posicion), tablero_actual[j].color, tablero_actual[j].tipo);
					}
				}
			}
			// Enroque
			else if (!tablero_anterior[i].valido && tablero_actual[i].tipo == Pieza::tipo_t::REY &&
				(tablero.getUltimaJugada().fin == Posicion(2, 0) || tablero.getUltimaJugada().fin == Posicion(6, 0) || 
				 tablero.getUltimaJugada().fin == Posicion(2, 7) || tablero.getUltimaJugada().fin == Posicion(6, 7)))
			{
				if (tablero_actual[i].color)
				{
					if (tablero_actual[i].posicion == Posicion(2, 0))
					{
						moverModelo(Movimiento(Posicion(0, 0), Posicion(3, 0)), tablero_actual[i].color, Pieza::tipo_t::TORRE);
					}
					else if (tablero_actual[i].posicion == Posicion(6, 0))
					{
						moverModelo(Movimiento(Posicion(7, 0), Posicion(5, 0)), tablero_actual[i].color, Pieza::tipo_t::TORRE);
					}
				}
				else
				{
					if (tablero_actual[i].posicion == Posicion(2, 7))
					{
						moverModelo(Movimiento(Posicion(0, 7), Posicion(3, 7)), tablero_actual[i].color, Pieza::tipo_t::TORRE);
					}
					else if (tablero_actual[i].posicion == Posicion(6, 7))
					{
						moverModelo(Movimiento(Posicion(7, 7), Posicion(5, 7)), tablero_actual[i].color, Pieza::tipo_t::TORRE);
					}
				}
			}
		}
	}
}

void Mundo::moverModelo(const Movimiento& mov, bool color, const Pieza::tipo_t tipo)
{
	int index = seleccionarLista(color, tipo)->getIndex(mov.inicio);

	if (index != -1)
		seleccionarLista(color, tipo)->setPosicion(index, mov.fin);
}

void Mundo::renderizarModelos(void)
{
	rey_blanco       .renderModelos();
	rey_negro        .renderModelos();
	damas_blancas    .renderModelos();
	damas_negras     .renderModelos();
	alfiles_blancos  .renderModelos();
	alfiles_negros   .renderModelos();
	caballos_blancos .renderModelos();
	caballos_negros  .renderModelos();
	torres_blancas   .renderModelos();
	torres_negras    .renderModelos();
	peones_blancos   .renderModelos();
	peones_negros    .renderModelos();
	casillas_blancas->render();
	casillas_negras ->render();
	marcos          ->render();
	letras          ->render();
}

/* PROVISIONAL */
void Mundo::keypress(unsigned char tecla)
{

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

	if (camara.getGirado())
	{
		result.x = 9 - result.x;
		result.y = 9 - result.y;
	}

	this->posicion_leida = result;
	std::cout << "Casilla seleccionada: " << posicion_leida.x << posicion_leida.y << std::endl;
	//moverModelos();
}

/* REVISAR */
void Mundo::dibujarFondo(void)
{
	glTranslatef(100, -10, 0);
	glRotatef(90.0f, 1, 0, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(Modelo::ruta_fondo.c_str()).id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 0); glVertex2f(-1000, -1000);
	glTexCoord2d(0, 1); glVertex2f(-1000,  1000);
	glTexCoord2d(1, 1); glVertex2f( 1000,  1000);
	glTexCoord2d(1, 0); glVertex2f( 1000, -1000);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glRotatef(-90.0f, 1, 0, 0);
	glTranslatef(-100, 10, 0);
}

void Mundo::moverModelos(const Movimiento& mov)
{
	if (mov.inicio != Posicion{-1, -1} && mov.fin != Posicion{ -1, -1 })
	{
		rey_blanco       .moverModelos(mov);
		rey_negro        .moverModelos(mov);
		damas_blancas    .moverModelos(mov);
		damas_negras     .moverModelos(mov);
		alfiles_blancos  .moverModelos(mov);
		alfiles_negros   .moverModelos(mov);
		caballos_blancos .moverModelos(mov);
		caballos_negros  .moverModelos(mov);
		torres_blancas   .moverModelos(mov);
		torres_negras    .moverModelos(mov);
		peones_blancos   .moverModelos(mov);
		peones_negros    .moverModelos(mov);
	}
}

void Mundo::movimiento(const float time)
{ 
	camara.movement(time);
}

void Mundo::borrarPieza(const Posicion& pos)
{
	damas_blancas   .deleteFromCoord(pos);
	damas_negras    .deleteFromCoord(pos);
	alfiles_blancos .deleteFromCoord(pos);
	alfiles_negros  .deleteFromCoord(pos);
	caballos_blancos.deleteFromCoord(pos);
	caballos_negros .deleteFromCoord(pos);
	torres_blancas  .deleteFromCoord(pos);
	torres_negras   .deleteFromCoord(pos);
	peones_blancos  .deleteFromCoord(pos);
	peones_negros   .deleteFromCoord(pos);
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
		break;
	}
}

Pieza::tipo_t Mundo::seleccionPiezaCoronacion(void)
{
	do
	{
		if (posicion_leida.y == 4)
		{
			switch (posicion_leida.x)
			{
			case 3:
				return Pieza::tipo_t::ALFIL;
				break;
			case 4:
				return Pieza::tipo_t::TORRE;
				break;
			case 5:
				return Pieza::tipo_t::DAMA;
				break;
			case 6:
				return Pieza::tipo_t::CABALLO;
				break;
			default:
				std::cout << "No es una pieza valida para coronar." << std::endl;
				break;
			}
		}
	} while (posicion_leida.x != 3, 4, 5, 6 || posicion_leida.y != 4);
}