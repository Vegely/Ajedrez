#include "Mundo.h"
#include "Tablero.h"

#include <ETSIDI.h>
#include <string>

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
	marcos(),
	casilla_seleccionada(20),
	casilla_comible(20),
	casilla_puede_mover(20),
	casilla_coronacion(20),
	casilla_ultimo_mov(2),
	casilla_jaque(10),
	letras(),
	camara(Camara::white_pov),
	peon(),
	alfil(),
	dama(),
	rey(),
	torre(),
	caballo(),
	casilla()
{

}

void Mundo::init(void)
{
	alfil  .init(Mundo::ruta_modelo_alfil);
	caballo.init(Mundo::ruta_modelo_caballo);
	dama   .init(Mundo::ruta_modelo_dama);
	rey    .init(Mundo::ruta_modelo_rey);
	torre  .init(Mundo::ruta_modelo_torre);
	peon   .init(Mundo::ruta_modelo_peon);
	casilla.init(Mundo::ruta_casilla);

	asignarModelos();
	cargarTexturas();
}

void Mundo::asignarModelos(void)
{
	for (int i = 0; i < 20; i++)
	{
		casilla_seleccionada.addElem(new Modelo(Posicion(-1, -1), casilla.scene, Mundo::ruta_textura_casilla_seleccionada));
		casilla_comible     .addElem(new Modelo(Posicion(-1, -1), casilla.scene, Mundo::ruta_textura_casilla_comible));
		casilla_puede_mover .addElem(new Modelo(Posicion(-1, -1), casilla.scene, Mundo::ruta_textura_casilla_puede_mover));
		casilla_coronacion  .addElem(new Modelo(Posicion(-1, -1), casilla.scene, Mundo::ruta_textura_casilla_coronacion));
		casilla_ultimo_mov  .addElem(new Modelo(Posicion(-1, -1), casilla.scene, Mundo::ruta_textura_casilla_ultimo_mov));
		casilla_jaque		.addElem(new Modelo(Posicion(-1, -1), casilla.scene, Mundo::ruta_textura_casilla_comible));
	}

	casillas_blancas = new Modelo(NONE, Point::zero, Mundo::ruta_modelo_casillas_blancas, Mundo::ruta_textura_blanco_oscuro);
	casillas_negras  = new Modelo(NONE, Point::zero, Mundo::ruta_modelo_casillas_negras,  Mundo::ruta_textura_negro_claro);
	marcos			 = new Modelo(NONE, Point::zero, Mundo::ruta_modelo_marcos,			  Mundo::ruta_textura_marco);
	letras			 = new Modelo(NONE, Point::zero, Mundo::ruta_modelo_letras,			  Mundo::ruta_textura_blanco);

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
			damas_blancas.addElem(new Modelo(DAMA, Posicion(), true,  dama.scene));
			damas_negras .addElem(new Modelo(DAMA, Posicion(), false, dama.scene));
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
			torres_blancas.addElem(new Modelo(TORRE, Posicion(), true,  torre.scene));
			torres_negras .addElem(new Modelo(TORRE, Posicion(), false, torre.scene));

			caballos_blancos.addElem(new Modelo(CABALLO, Posicion(), true, caballo.scene));
			caballos_negros .addElem(new Modelo(CABALLO, Posicion(), false, caballo.scene));

			alfiles_blancos.addElem(new Modelo(ALFIL, Posicion(), true,  alfil.scene));
			alfiles_negros .addElem(new Modelo(ALFIL, Posicion(), false, alfil.scene));
		}
	}

	posicion_leida = Posicion();
}

void Mundo::cargarTexturas(void)
{
	rey_blanco           .cargarTexturas();
	rey_negro            .cargarTexturas();
	damas_blancas        .cargarTexturas();
	damas_negras         .cargarTexturas();
	alfiles_blancos      .cargarTexturas();
	alfiles_negros       .cargarTexturas();
	caballos_blancos     .cargarTexturas();
	caballos_negros      .cargarTexturas();
	torres_blancas       .cargarTexturas();
	torres_negras        .cargarTexturas();
	peones_blancos       .cargarTexturas();
	peones_negros        .cargarTexturas();
	coronacion_blancos   .cargarTexturas();
	coronacion_negros    .cargarTexturas();
	casilla_seleccionada .cargarTexturas();
	casilla_puede_mover  .cargarTexturas();
	casilla_coronacion   .cargarTexturas();
	casilla_comible      .cargarTexturas();
	casilla_ultimo_mov   .cargarTexturas();
	casilla_jaque		 .cargarTexturas();
	casillas_blancas    ->cargarTextura();
	casillas_negras     ->cargarTextura();
	marcos              ->cargarTextura();
	letras              ->cargarTextura();
}

void Mundo::renderizarModelos(void)
{
	if (!coronando_blancas && !coronando_negras)
	{
		rey_blanco			.renderModelos();
		rey_negro			.renderModelos();
		damas_blancas		.renderModelos();
		damas_negras		.renderModelos();
		alfiles_blancos		.renderModelos();
		alfiles_negros		.renderModelos();
		caballos_blancos	.renderModelos();
		caballos_negros		.renderModelos();
		torres_blancas		.renderModelos();
		torres_negras		.renderModelos();
		peones_blancos		.renderModelos();
		peones_negros		.renderModelos();
		casilla_comible		.renderModelos();
		casilla_coronacion	.renderModelos();
		casilla_seleccionada.renderModelos();
		casilla_puede_mover	.renderModelos();
		casilla_ultimo_mov	.renderModelos();
		casilla_jaque		.renderModelos();
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
}

//void Mundo::dibujarFondo(void)
//{
//	glTranslatef(100, -10, 0);
//	glRotatef(90.0f, 1, 0, 0);
//	glEnable(GL_TEXTURE_2D);
//	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(Mundo::ruta_fondo.c_str()).id);
//	glDisable(GL_LIGHTING);
//	glBegin(GL_POLYGON);
//	glColor3f(1, 1, 1);
//	glTexCoord2d(0, 0); glVertex2f(-1000, -1000);
//	glTexCoord2d(0, 1); glVertex2f(-1000,  1000);
//	glTexCoord2d(1, 1); glVertex2f( 1000,  1000);
//	glTexCoord2d(1, 0); glVertex2f( 1000, -1000);
//	glEnd();
//	glEnable(GL_LIGHTING);
//	glDisable(GL_TEXTURE_2D);
//	glRotatef(-90.0f, 1, 0, 0);
//	glTranslatef(-100, 10, 0);
//}

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
	}
	else if (config[0] == receptor)
	{
		if (!this->getGirado())
			this->cambiarGirado();
	}

	camara.movement(Camara::white_pov, Camara::black_pov, time);
}

void Mundo::resetCasillas(void)
{
	for (int i = 0; i < this->casilla_comible.getNumElem(); i++)
		this->casilla_comible.setPosicion(i, Posicion());

	for (int i = 0; i < this->casilla_seleccionada.getNumElem(); i++)
		this->casilla_seleccionada.setPosicion(i, Posicion());

	for (int i = 0; i < this->casilla_puede_mover.getNumElem(); i++)
		this->casilla_puede_mover.setPosicion(i, Posicion());

	for (int i = 0; i < this->casilla_coronacion.getNumElem(); i++)
		this->casilla_coronacion.setPosicion(i, Posicion());
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
			if (!tablero->jaqueMate())
			{
				ListaModelo* lista = seleccionarLista(pieza_leida->getColor(), pieza_leida->getTipo());
				if (lista != nullptr) lista->moverElemento(Movimiento(Posicion(), Posicion(i % 8, i / 8)));
			}
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

std::string Mundo::ruta_modelo_rey     = "modelos/rey.obj";
std::string Mundo::ruta_modelo_dama    = "modelos/dama.obj";
std::string Mundo::ruta_modelo_alfil   = "modelos/alfil.obj";
std::string Mundo::ruta_modelo_caballo = "modelos/caballo.obj";
std::string Mundo::ruta_modelo_torre   = "modelos/torre.obj";
std::string Mundo::ruta_modelo_peon    = "modelos/peon.obj";

std::string Mundo::ruta_casilla					= "modelos/casilla.obj";
std::string Mundo::ruta_modelo_casillas_negras  = "modelos/casillas_negras.obj";
std::string Mundo::ruta_modelo_casillas_blancas = "modelos/casillas_blancas.obj";
std::string Mundo::ruta_modelo_marcos			= "modelos/marcos.obj";
std::string Mundo::ruta_modelo_letras			= "modelos/letras.obj";

std::string Mundo::ruta_textura_blanco				 = "texturas/marmol_blanco.jpg";
std::string Mundo::ruta_textura_negro				 = "texturas/marmol_negro.jpg";
std::string Mundo::ruta_textura_blanco_oscuro		 = "texturas/marmol_blanco_oscuro.jpg";
std::string Mundo::ruta_textura_negro_claro			 = "texturas/marmol_negro_claro.jpg";
std::string Mundo::ruta_textura_marco				 = "texturas/marmol_negro_marco.jpg";
std::string Mundo::ruta_textura_casilla_seleccionada = "texturas/casilla_seleccionada.png";
std::string Mundo::ruta_textura_casilla_comible		 = "texturas/casilla_comer.png";
std::string Mundo::ruta_textura_casilla_puede_mover	 = "texturas/casilla_puede_mover.png";
std::string Mundo::ruta_textura_casilla_coronacion   = "texturas/casilla_coronacion.png";
std::string Mundo::ruta_textura_casilla_ultimo_mov	 = "texturas/casilla_ultimo_mov.png";

std::string Mundo::ruta_fondo = "texturas/espacio.png";