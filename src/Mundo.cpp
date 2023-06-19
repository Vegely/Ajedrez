#include "Mundo.h"
#include "Tablero.h"

#include <ETSIDI.h>
#include <string>

CasillasTablero casillas_tablero_array;

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
	tablero_anterior(),
	tablero_actual(),
	posicion_leida(),
	casillas_px(),
	casillas_blancas(),
	casillas_negras(),
	marcos(),
	letras(),
	camara({ 0.0f, 20.5f, -15.6f }),
	peon(),
	alfil(),
	dama(),
	rey(),
	torre(),
	caballo()
{

}

void Mundo::init(void)
{
	alfil.init(Modelo::ruta_modelo_alfil);
	caballo.init(Modelo::ruta_modelo_caballo);
	dama.init(Modelo::ruta_modelo_dama);
	rey.init(Modelo::ruta_modelo_rey);
	torre.init(Modelo::ruta_modelo_torre);
	peon.init(Modelo::ruta_modelo_peon);

	asignarModelos();
	cargarTexturas();
}

void Mundo::asignarModelos(void)
{
	casillas_blancas = new Modelo(NONE, Posicion(0, 0), Modelo::ruta_modelo_casillas_blancas, Modelo::ruta_textura_blanco_oscuro);
	casillas_negras  = new Modelo(NONE, Posicion(0, 0), Modelo::ruta_modelo_casillas_negras,  Modelo::ruta_textura_negro_claro);
	marcos			 = new Modelo(NONE, Posicion(0, 0), Modelo::ruta_modelo_marcos,			  Modelo::ruta_textura_marco);
	letras			 = new Modelo(NONE, Posicion(0, 0), Modelo::ruta_modelo_letras,			  Modelo::ruta_textura_blanco);

	rey_blanco.addElem(new Modelo(REY, Posicion(4, 0), true,  rey.scene));
	rey_negro .addElem(new Modelo(REY, Posicion(4, 7), false, rey.scene));

	coronacion_blancos.addElem(new Modelo(ALFIL,   Posicion(2, 3), true,  alfil.scene));
	coronacion_blancos.addElem(new Modelo(TORRE,   Posicion(3, 3), true,  torre.scene));
	coronacion_blancos.addElem(new Modelo(DAMA,    Posicion(4, 3), true,  dama.scene));
	coronacion_blancos.addElem(new Modelo(CABALLO, Posicion(5, 3), true,  caballo.scene));
	coronacion_negros .addElem(new Modelo(ALFIL,   Posicion(2, 4), false, alfil.scene));
	coronacion_negros .addElem(new Modelo(TORRE,   Posicion(3, 4), false, torre.scene));
	coronacion_negros .addElem(new Modelo(DAMA,    Posicion(4, 4), false, dama.scene));
	coronacion_negros .addElem(new Modelo(CABALLO, Posicion(5, 4), false, caballo.scene));

	for (int i = 0; i < 10; i++)
	{
		// Peones
		peones_blancos.addElem(new Modelo(PEON, Posicion(i, 1), true,  peon.scene));
		peones_negros .addElem(new Modelo(PEON, Posicion(i, 6), false, peon.scene));
		// Damas
		if (i == 0)
		{
			damas_blancas.addElem(new Modelo(DAMA, Posicion(3, 0), true,  dama.scene));
			damas_negras .addElem(new Modelo(DAMA, Posicion(3, 7), false, dama.scene));
		}
		else
		{
			damas_blancas.addElem(new Modelo(DAMA, Posicion(-1, -1), true,  dama.scene));
			damas_negras .addElem(new Modelo(DAMA, Posicion(-1, -1), false, dama.scene));
		}
		// Resto
		if (i < 2)
		{
			torres_blancas.addElem(new Modelo(TORRE, Posicion(0 + i * 7, 0), true,  torre.scene));
			torres_negras .addElem(new Modelo(TORRE, Posicion(0 + i * 7, 7), false, torre.scene));

			caballos_blancos.addElem(new Modelo(CABALLO, Posicion(1 + i * 5, 0), true,  caballo.scene));
			caballos_negros .addElem(new Modelo(CABALLO, Posicion(1 + i * 5, 7), false, caballo.scene));

			alfiles_blancos.addElem(new Modelo(ALFIL, Posicion(2 + i * 3, 0), true,  alfil.scene));
			alfiles_negros .addElem(new Modelo(ALFIL, Posicion(2 + i * 3, 7), false, alfil.scene));
		}
		else
		{
			torres_blancas.addElem(new Modelo(TORRE, Posicion(-1, -1), true,  torre.scene));
			torres_negras .addElem(new Modelo(TORRE, Posicion(-1, -1), false, torre.scene));

			caballos_blancos.addElem(new Modelo(CABALLO, Posicion(-1, -1), true,  caballo.scene));
			caballos_negros .addElem(new Modelo(CABALLO, Posicion(-1, -1), false, caballo.scene));

			alfiles_blancos.addElem(new Modelo(ALFIL, Posicion(-1, -1), true,  alfil.scene));
			alfiles_negros .addElem(new Modelo(ALFIL, Posicion(-1, -1), false, alfil.scene));
		}
	}

	posicion_leida = Posicion{ -1, -1 };

	std::cout << "Modelos asignados." << std::endl;
}

void Mundo::cargarTexturas(void)
{
	rey_blanco        .cargarTexturas();
	rey_negro         .cargarTexturas();
	damas_blancas     .cargarTexturas();
	damas_negras      .cargarTexturas();
	alfiles_blancos   .cargarTexturas();
	alfiles_negros    .cargarTexturas();
	caballos_blancos  .cargarTexturas();
	caballos_negros   .cargarTexturas();
	torres_blancas    .cargarTexturas();
	torres_negras     .cargarTexturas();
	peones_blancos    .cargarTexturas();
	peones_negros     .cargarTexturas();
	coronacion_blancos.cargarTexturas();
	coronacion_negros .cargarTexturas();
	casillas_blancas ->cargarTextura();
	casillas_negras  ->cargarTextura();
	marcos           ->cargarTextura();
	letras           ->cargarTextura();
}

void Mundo::leerTablero(const Tablero& tablero)
{
	for (int i = 0; i < 64; i++)
	{
		if (i != 0)
		{
			tablero_anterior[i] = tablero_actual[i];
		}
		if (tablero.leer(casillas_tablero_array[i]) != nullptr)
		{
			tablero_actual[i] = DatosPieza{
			tablero.leer(casillas_tablero_array[i])->getColor(),
			tablero.leer(casillas_tablero_array[i])->getTipo(),
			tablero.leer(casillas_tablero_array[i])->getPosicion(),
			true };
		}
		else
		{
			tablero_actual[i].valido = false;
			tablero_actual[i].tipo = Pieza::tipo_t::NULA;
		}

		if (tablero_anterior[i].valido || tablero_actual[i].valido && (tablero_anterior[i] != tablero_actual[i])) // Si alguna casilla no sigue vacia y son distintas
		{ 
			// Comidas
			if (tablero_anterior[i].valido && tablero_actual[i].valido)
			{
				// Una ha comido a la otra. Se sustituye la nueva por la antigua.
				if (tablero_anterior[i].color != tablero_actual[i].color)
				{
					moverModelo(Movimiento(tablero_anterior[i].posicion, Posicion(-1, -1)), tablero_anterior[i].color, tablero_anterior[i].tipo);
					moverModelo(tablero.getUltimaJugada(), tablero_actual[i].color, tablero_actual[i].tipo);
				}
				//else if (tablero_actual[i].tipo != tipo_actual || tablero_actual[i].color != color_actual)
				//{
				//	if (tablero_actual[i].tipo != Pieza::tipo_t::NULA)
				//		moverModelo(Movimiento(Posicion(-1, -1), casillas_tablero_array[i]), tablero_actual[i].color, tablero_actual[i].tipo);
				//	else
				//		moverModelo(Movimiento(casillas_tablero_array[i], Posicion(-1, -1)), tablero_actual[i].color, tablero_actual[i].tipo);
				//}
			}
			// Coronacion
			if (tablero_anterior[i].tipo == Pieza::tipo_t::PEON && !tablero_actual[i].valido)
			{
				if ((tablero_anterior[i].posicion.y == 6 && tablero_anterior[i].color) || (tablero_anterior[i].posicion.y == 1 && !tablero_anterior[i].color))
				{
					moverModelo(Movimiento(tablero_anterior[i].posicion, Posicion(-1, -1)), tablero_anterior[i].color, Pieza::tipo_t::PEON); // "Borrar" el peon
					// Volver a leer el tablero porque han pasado dos cosas a la vez: destruccion del peon y promocion a la nueva pieza.
					for (int j = 0; j < 64; j++)
					{
						std::string tipo = "";
						Pieza* pieza = tablero.leer(casillas_tablero_array[j]);
						if (pieza != nullptr)
						{
							switch (pieza->getTipo())
							{
							case Pieza::tipo_t::REY:
								tipo = "REY";
								break;

							case Pieza::tipo_t::DAMA:
								tipo = "DAMA";
								break;

							case Pieza::tipo_t::ALFIL:
								tipo = "ALFIL";
								break;

							case Pieza::tipo_t::CABALLO:
								tipo = "CABALLO";
								break;

							case Pieza::tipo_t::TORRE:
								tipo = "TORRE";
								break;

							case Pieza::tipo_t::PEON:
								tipo = "PEON";
								break;

							case Pieza::tipo_t::NULA:
								tipo = "NONE";
								break;

							default:
								break;
							}
							std::cout << "Tipo pieza posicion " << casillas_tablero_array[j].x << casillas_tablero_array[j].y << ": " << tipo << std::endl;
						}
						else
							std::cout << "Tipo pieza posicion " << casillas_tablero_array[j].x << casillas_tablero_array[j].y << ": " << "NONE" << std::endl;

							tablero_anterior[j] = tablero_actual[j];
						if (tablero.leer(casillas_tablero_array[j]) != nullptr)
						{
							tablero_actual[j] = DatosPieza{
							tablero.leer(casillas_tablero_array[j])->getColor(),
							tablero.leer(casillas_tablero_array[j])->getTipo(),
							tablero.leer(casillas_tablero_array[j])->getPosicion(),
							true };
						}
						else
						{
							tablero_actual[j].valido = false;
							tablero_actual[j].tipo = Pieza::tipo_t::NULA;
						}

						//if (!tablero_anterior[j].valido && tablero_actual[j].valido && tablero_actual[i].tipo != Pieza::tipo_t::PEON)
						//{
						//	moverModelo(Movimiento(Posicion(-1, -1), tablero.getUltimaJugada().fin), !tablero.getTurno(), tablero_actual[j].tipo);
						//}
						//else if (tablero_anterior[j].valido && tablero_actual[j].valido && (tablero_anterior[j].color != tablero_actual[j].color))
						//{
						//	moverModelo(Movimiento(tablero_anterior[j].posicion, Posicion(-1, -1)), tablero_anterior[j].color, tablero_anterior[j].tipo); // "Destruir" la pieza anterior
						//	moverModelo(Movimiento(Posicion(-1, -1), tablero.getUltimaJugada().fin), !tablero.getTurno(), tablero_actual[j].tipo);
						//}
						if(!tablero_anterior[j].valido && tablero_actual[j].valido ||
							(tablero_anterior[j].valido && tablero_actual[j].valido &&
								(tablero_anterior[j].color != tablero_actual[j].color)))
							moverModelo(Movimiento(Posicion(-1, -1), tablero.getUltimaJugada().fin), !tablero.getTurno(), tablero_actual[j].tipo);
					}
				}
			}
			// Movimiento normal
			else if (!tablero_anterior[i].valido && tablero_actual[i].valido)
			{
				moverModelo(tablero.getUltimaJugada(), tablero_actual[i].color, tablero_actual[i].tipo);
			}
			// Captura al paso.
			if (tablero_anterior[i].valido && !tablero_actual[i].valido && tablero_anterior[i].tipo == Pieza::tipo_t::PEON) // Si una casilla pasa de estar ocupada a no estarlo
			{
				if (tablero.getUltimaJugada().inicio != tablero_anterior[i].posicion && tablero.getUltimaJugada().fin != tablero_anterior[i].posicion)
					moverModelo(Movimiento(tablero_anterior[i].posicion, Posicion(-1, -1)), tablero_anterior[i].color, tablero_anterior[i].tipo);
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
	if (tipo != Pieza::tipo_t::NULA)
	{
		ListaModelo* lista = seleccionarLista(color, tipo);
		int index = -1;
		if (lista != nullptr) index = lista->getIndex(mov.inicio);
		else std::cout << "List was a nullptr." << std::endl;

		if (index != -1)
			lista->getElem(index)->moverModelo(mov);
	}
}

void Mundo::renderizarModelos(void)
{
	if (!coronando_blancas && !coronando_negras)
	{
		rey_blanco      .renderModelos();
		rey_negro       .renderModelos();
		damas_blancas   .renderModelos();
		damas_negras    .renderModelos();
		alfiles_blancos .renderModelos();
		alfiles_negros  .renderModelos();
		caballos_blancos.renderModelos();
		caballos_negros .renderModelos();
		torres_blancas  .renderModelos();
		torres_negras   .renderModelos();
		peones_blancos  .renderModelos();
		peones_negros   .renderModelos();
	}
	else if (coronando_blancas && !coronando_negras)
		coronacion_blancos.renderModelos();
	else if (coronando_negras && !coronando_blancas)
		coronacion_negros .renderModelos();

	casillas_blancas->render();
	casillas_negras ->render();
	marcos->render();
	letras->render();
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
	camara.movement(time, Point{ 0.0f, 20.5f, -15.6f }, Point{ 0.0f, 20.5f, 15.6f });
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
	do
	{
		if (color) this->coronando_blancas = true;
		else	   this->coronando_negras  = true;

		if ((posicion_leida.y == 3 && color) || (posicion_leida.y == 4 && !color))
		{
			switch (posicion_leida.x)
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
	} while (posicion_leida.x != 3 || posicion_leida.x != 4 || posicion_leida.x != 5 ||
		posicion_leida.x != 6 || (posicion_leida.y != 3 && color) || (posicion_leida.y != 4 && !color));
}

Pieza::tipo_t Mundo::getTipoFromCoords(const Posicion& pos)
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

bool Mundo::getColorFromCoords(const Posicion& pos)
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

void Mundo::actualizarCamara(bool turno)
{
	if (turno && !this->getGirado())
	{
		this->cambiarGirado();
	}
	else if (!turno && this->getGirado())
	{
		this->cambiarGirado();
	}
}