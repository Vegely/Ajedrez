#include "Mundo.h"
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
	casillas_leidas(),
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

	rey_blanco.addElem(new Modelo(REY, Posicion(5, 1), true ));
	rey_negro .addElem(new Modelo(REY, Posicion(5, 8), false));

	for (int i = 0; i < 8; i++)
	{
		// Damas
		if (i == 0)
		{
			damas_blancas.addElem(new Modelo(DAMA, Posicion(4, 1), true ));
			damas_negras .addElem(new Modelo(DAMA, Posicion(4, 8), false));
		}
		// Resto de piezas excepto peones
		if (i == 0 || i == 1)
		{
			torres_blancas  .addElem(new Modelo(TORRE,   Posicion(1 + i * 7, 1), true ));
			torres_negras   .addElem(new Modelo(TORRE,   Posicion(1 + i * 7, 8), false));

			caballos_blancos.addElem(new Modelo(CABALLO, Posicion(2 + i * 5, 1), true ));
			caballos_negros .addElem(new Modelo(CABALLO, Posicion(2 + i * 5, 8), false));

			alfiles_blancos .addElem(new Modelo(ALFIL,   Posicion(3 + i * 3, 1), true ));
			alfiles_negros  .addElem(new Modelo(ALFIL,   Posicion(3 + i * 3, 8), false));
		}
		// Peones
		peones_blancos  .addElem(new Modelo(PEON, Posicion(1 + i, 2), true ));
		peones_negros   .addElem(new Modelo(PEON, Posicion(1 + i, 7), false));
	}

	casillas_leidas.inicio = Posicion{ -1, -1 };
	casillas_leidas.fin    = Posicion{ -1, -1 };

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

void Mundo::dibujarTablero(const Tablero& tablero)
{
	tablero_anterior.copiar(tablero_actual);
	tablero_actual  .copiar(tablero);
	static Pieza* pieza_anterior = nullptr;
	static Pieza* pieza_actual   = nullptr;

	for (int i = 0; i < 64; i++)
	{
		pieza_anterior = tablero_anterior.leer(casillas_tablero_array[i]);
		pieza_actual   = tablero_actual  .leer(casillas_tablero_array[i]);

		if (pieza_anterior != nullptr || pieza_actual != nullptr) // Si la casilla no sigue vacía
		{
			// Si los tipos y colores son iguales no ha pasado nada
			if (pieza_anterior->getTipo() == pieza_actual->getTipo() && pieza_anterior->getColor() == pieza_actual->getColor())
				return;
			// Si los tipos son pieza y pieza una ha comido a la otra o ha ocurrido una coronación
			if (pieza_anterior != nullptr && pieza_actual != nullptr)
			{
				if (pieza_anterior->getColor() != pieza_actual->getColor()) // Una ha comido a la otra. Se sustituye la nueva por la antigua.
				{
					seleccionarLista(pieza_anterior->getColor(), pieza_anterior->getTipo())->
					deleteFromCoord(pieza_anterior->getPosicion());

					seleccionarLista(pieza_actual->getColor(), pieza_actual->getTipo())->
					addElem(new Modelo(Modelo::castTipo(pieza_actual->getTipo()), pieza_actual->getPosicion(), pieza_actual->getColor()));
				}
				else if (pieza_anterior->getTipo() == Pieza::tipo_t::PEON) // Ha ocurrido una coronación
				{
					seleccionarLista(pieza_anterior->getColor(), pieza_anterior->getTipo())->
					deleteFromCoord(pieza_anterior->getPosicion());

					seleccionarLista(pieza_actual->getColor(), pieza_actual->getTipo())->
					addElem(new Modelo(Modelo::castTipo(pieza_actual->getTipo()), pieza_actual->getPosicion(), pieza_actual->getColor()));
				}
			}
			// Si los tipos son nullptr y pieza o viceversa, una pieza se ha movido.
			else if (pieza_anterior == nullptr && pieza_actual != nullptr || pieza_anterior != nullptr && pieza_actual == nullptr)
			{
				if (pieza_actual == nullptr)
					seleccionarLista(pieza_anterior->getColor(), pieza_anterior->getTipo())->
					deleteFromCoord(pieza_anterior->getPosicion());
				else
					seleccionarLista(pieza_actual->getColor(), pieza_actual->getTipo())->
					addElem(new Modelo(Modelo::castTipo(pieza_actual->getTipo()), pieza_actual->getPosicion(), pieza_actual->getColor()));
			}
		}
	}
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
	static bool flag = false;
	switch (tecla)
	{
	case 'w':
		if (camara.getGirado() == false)
			camara.setPosition({ 0.0f, 20.5f, -15.6f });
		else
			camara.setPosition({ 0.0f, 20.5f, 15.6f });

		camara.cambiarGirado();
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void Mundo::seleccionCasilla(int button, int state, int x_mouse, int y_mouse)
{
	static bool elem_casilla = false;
	Posicion result = Posicion{ 0 };
	Corners<Point> slot;

	if (state == 1 || button != 0)
		return;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			slot = casillas_px.getSlotCoords(i, j);
			if (x_mouse < slot.lr.x && x_mouse > slot.ll.x && y_mouse < slot.ll.y && y_mouse > slot.ul.y)
				result = Posicion{ i + 1, j + 1 };
		}
	}

	if (camara.getGirado())
	{
		result.x = 9 - result.x;
		result.y = 9 - result.y;
	}

	if (!elem_casilla)
	{
		casillas_leidas.inicio = result;
		elem_casilla = !elem_casilla;
	}
	else
	{
		casillas_leidas.fin = result;
		elem_casilla = !elem_casilla;
	}

	std::cout << casillas_leidas.inicio.x << casillas_leidas.inicio.y << std::endl;
	std::cout << casillas_leidas.fin.x << casillas_leidas.fin.y << std::endl << std::endl;

	moverModelos();
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

void Mundo::moverModelos(void)
{
	if (casillas_leidas.inicio != Posicion{-1, -1} && casillas_leidas.fin != Posicion{ -1, -1 })
	{
		rey_blanco       .moverModelos(casillas_leidas);
		rey_negro        .moverModelos(casillas_leidas);
		damas_blancas    .moverModelos(casillas_leidas);
		damas_negras     .moverModelos(casillas_leidas);
		alfiles_blancos  .moverModelos(casillas_leidas);
		alfiles_negros   .moverModelos(casillas_leidas);
		caballos_blancos .moverModelos(casillas_leidas);
		caballos_negros  .moverModelos(casillas_leidas);
		torres_blancas   .moverModelos(casillas_leidas);
		torres_negras    .moverModelos(casillas_leidas);
		peones_blancos   .moverModelos(casillas_leidas);
		peones_negros    .moverModelos(casillas_leidas);

		casillas_leidas = Movimiento{ Posicion{-1, -1}, Posicion{-1, -1} };
	}
}

void Mundo::movimiento(const float time)
{ 
	camara.movement(time);
}

/* REVISAR */
void Mundo::coronarPeon(const Posicion& pos) // Promocionar (comprobaciones)
{
	bool flag = false; // To check if there has been a promotion later in the code.
	bool color = true; // true == white, false == black;
	if (pos.y == 0)	   // If the position is at the beggining of the board (white's POV), the piece will always be black,
		color = false; // since the pawns can't move backwards.
	int tipo_nuevo = 0;

	if (color)
	{
		for (int i = 0; i < peones_blancos.size(); i++)
		{
			if (peones_blancos.getPosicion(i).y == pos.y && pos.y == 8) // The pawn reached the end of the board.
			{
				peones_blancos.deleteElem(i);
				flag = true;
			}
		}
	}
	else
	{
		for (int i = 0; i < peones_negros.size(); i++)
		{
			if (peones_negros.getPosicion(i).y == pos.y && pos.y == 0) // The pawn reached the end of the board.
			{
				peones_negros.deleteElem(i);
				flag = true;
			}
		}
	}
	if (flag == false) return;

	std::cout << "Promotion is possible. Select a piece to promote to:" << std::endl;
	std::cout << "2: Queen\n4: Knight\n3: Bishop\n5: Rook" << std::endl;
	std::cin >> tipo_nuevo;

	switch (tipo_nuevo)
	{
	case DAMA:
		if (color)
			this->damas_blancas.addElem(new Modelo(static_cast<TipoPieza>(tipo_nuevo), pos, Modelo::ruta_modelo_dama, Modelo::ruta_textura_blanco));
		else
			this->damas_negras .addElem(new Modelo(static_cast<TipoPieza>(tipo_nuevo), pos, Modelo::ruta_modelo_dama, Modelo::ruta_textura_negro));
		break;

	case ALFIL:
		if (color)
			this->alfiles_blancos.addElem(new Modelo(static_cast<TipoPieza>(tipo_nuevo), pos, Modelo::ruta_modelo_alfil, Modelo::ruta_textura_blanco));
		else
			this->alfiles_negros .addElem(new Modelo(static_cast<TipoPieza>(tipo_nuevo), pos, Modelo::ruta_modelo_alfil, Modelo::ruta_textura_negro));
		break;

	case CABALLO:
		if (color)
			this->caballos_blancos.addElem(new Modelo(static_cast<TipoPieza>(tipo_nuevo), pos, Modelo::ruta_modelo_caballo, Modelo::ruta_textura_blanco));
		else
			this->caballos_negros .addElem(new Modelo(static_cast<TipoPieza>(tipo_nuevo), pos, Modelo::ruta_modelo_caballo, Modelo::ruta_textura_negro));
		break;

	case TORRE:
		if (color)
			this->torres_blancas.addElem(new Modelo(static_cast<TipoPieza>(tipo_nuevo), pos, Modelo::ruta_modelo_torre, Modelo::ruta_textura_blanco));
		else
			this->torres_negras .addElem(new Modelo(static_cast<TipoPieza>(tipo_nuevo), pos, Modelo::ruta_modelo_torre, Modelo::ruta_textura_negro));
		break;

	default:
		break;
	}
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