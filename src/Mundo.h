#ifndef MUNDO_H
#define MUNDO_H

#include <vector>
#include "ListaModelo.h"
#include "Camara.h"
#include "Movimiento.h"
#include "Plane.h"



class Casilla
{
private:
	Corners<Point> casillas[8][8];

public:
	Casilla(void) : casillas()
	{
		for (int i = 0; i < 8; i++)
		{
			casillas[i][0].ll.y = 900;
			casillas[i][0].ul.y = 790;
			casillas[i][1].ul.y = 690;
			casillas[i][2].ul.y = 606;
			casillas[i][3].ul.y = 530;
			casillas[i][4].ul.y = 465;
			casillas[i][5].ul.y = 405;
			casillas[i][6].ul.y = 350;
			casillas[i][7].ul.y = 300;
		}

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (j < 7)
					casillas[i][j + 1].ll.y = casillas[i][j].ul.y;

				casillas[i][j].lr.y = casillas[i][j].ll.y;
				casillas[i][j].ur.y = casillas[i][j].ul.y;
			}
		}

		casillas[0][0].ll.x = 527;
		casillas[0][0].lr.x = 635;
		casillas[1][0].lr.x = 743;
		casillas[2][0].lr.x = 852;
		casillas[3][0].lr.x = 960;
		casillas[4][0].lr.x = 1068;
		casillas[5][0].lr.x = 1177;
		casillas[6][0].lr.x = 1285;
		casillas[7][0].lr.x = 1393;

		casillas[0][1].ll.x = 557;
		casillas[0][1].lr.x = 657;
		casillas[1][1].lr.x = 757;
		casillas[2][1].lr.x = 859;
		casillas[3][1].lr.x = 960;
		casillas[4][1].lr.x = 1061;
		casillas[5][1].lr.x = 1163;
		casillas[6][1].lr.x = 1263;
		casillas[7][1].lr.x = 1363;

		casillas[0][2].ll.x = 580;
		casillas[0][2].lr.x = 675;
		casillas[1][2].lr.x = 770;
		casillas[2][2].lr.x = 865;
		casillas[3][2].lr.x = 960;
		casillas[4][2].lr.x = 1055;
		casillas[5][2].lr.x = 1150;
		casillas[6][2].lr.x = 1245;
		casillas[7][2].lr.x = 1340;

		casillas[0][3].ll.x = 600;
		casillas[0][3].lr.x = 690;
		casillas[1][3].lr.x = 780;
		casillas[2][3].lr.x = 870;
		casillas[3][3].lr.x = 960;
		casillas[4][3].lr.x = 1050;
		casillas[5][3].lr.x = 1140;
		casillas[6][3].lr.x = 1230;
		casillas[7][3].lr.x = 1320;

		casillas[0][4].ll.x = 620;
		casillas[0][4].lr.x = 707;
		casillas[1][4].lr.x = 792;
		casillas[2][4].lr.x = 875;
		casillas[3][4].lr.x = 960;
		casillas[4][4].lr.x = 1045;
		casillas[5][4].lr.x = 1128;
		casillas[6][4].lr.x = 1213;
		casillas[7][4].lr.x = 1300;

		casillas[0][5].ll.x = 640;
		casillas[0][5].lr.x = 720;
		casillas[1][5].lr.x = 800;
		casillas[2][5].lr.x = 880;
		casillas[3][5].lr.x = 960;
		casillas[4][5].lr.x = 1040;
		casillas[5][5].lr.x = 1120;
		casillas[6][5].lr.x = 1200;
		casillas[7][5].lr.x = 1280;

		casillas[0][6].ll.x = 652;
		casillas[0][6].lr.x = 732;
		casillas[1][6].lr.x = 809;
		casillas[2][6].lr.x = 880;
		casillas[3][6].lr.x = 960;
		casillas[4][6].lr.x = 1040;
		casillas[5][6].lr.x = 1111;
		casillas[6][6].lr.x = 1188;
		casillas[7][6].lr.x = 1268;

		casillas[0][7].ll.x = 670;
		casillas[0][7].lr.x = 743;
		casillas[1][7].lr.x = 820;
		casillas[2][7].lr.x = 888;
		casillas[3][7].lr.x = 960;
		casillas[4][7].lr.x = 1032;
		casillas[5][7].lr.x = 1100;
		casillas[6][7].lr.x = 1177;
		casillas[7][7].lr.x = 1250;

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (i < 7)
					casillas[i + 1][j].ll.x = casillas[i][j].lr.x;

				casillas[i][j].ul.x = casillas[i][j].ll.x;
				casillas[i][j].ur.x = casillas[i][j].lr.x;
			}
		}
	}

	Corners<Point> getSlotCoords(int i, int j) const
	{
		float factor_escala_y = static_cast<float>(glutGet(GLUT_WINDOW_HEIGHT)) / 1080.0f;
		float factor_escala_x = static_cast<float>(glutGet(GLUT_WINDOW_WIDTH)) / 1920.0f;
		Corners<Point> result = this->casillas[i][j];
		result *= Factor(factor_escala_x, factor_escala_y);
		std::cout << "Window height: " << glutGet(GLUT_WINDOW_HEIGHT) << std::endl;
		std::cout << "Ratio: " << factor_escala_x << " " << factor_escala_y << std::endl;
		return result;
	}
};

struct DatosPieza
{
	bool color;
	Pieza::tipo_t tipo;
	Posicion posicion;
	bool valido;

	bool operator == (const DatosPieza& dp)
	{
		return
		(
			this->color    == dp.color    &&
			this->tipo     == dp.tipo     &&
			this->posicion == dp.posicion &&
			this->valido   == dp.valido
		);
	}
	bool operator != (const DatosPieza& dp) { return !(operator==(dp)); }
};

class Mundo
{
private:
	DatosPieza tablero_anterior[64];
	DatosPieza tablero_actual[64];

	ListaModelo rey_blanco;
	ListaModelo rey_negro;
	ListaModelo damas_blancas;
	ListaModelo damas_negras;
	ListaModelo alfiles_blancos;
	ListaModelo alfiles_negros;
	ListaModelo caballos_blancos;
	ListaModelo caballos_negros;
	ListaModelo torres_blancas;
	ListaModelo torres_negras;
	ListaModelo peones_blancos;
	ListaModelo peones_negros;
	Modelo* casillas_blancas;
	Modelo* casillas_negras;
	Modelo* marcos;
	Modelo* letras;

	Camara camara;
	Posicion posicion_leida;
	Casilla casillas_px;

public:
	Mundo(void);
	void init(void);
	void asignarModelos(void);
	void cargarTexturas(void);

	void leerTablero(const Tablero& tablero);

	void renderizarModelos(void);
	void updateCamara(void) { camara.update(); }
	void setCamaraPos(const Point& pt) { camara.setPosition(pt); }
	void movimiento(const float time);
	void keypress(unsigned char tecla);
	void seleccionCasilla(int button, int state, int x_mouse, int y_mouse);
	bool getGirado(void) { return camara.getGirado(); }
	void cambiarGirado(void) { camara.cambiarGirado(); }
	void dibujarFondo(void);
	void borrarPieza(const Posicion& pos);
	void moverModelos(const Movimiento& mov);
	Posicion getCasilla(void) const { return this->posicion_leida; }
	Pieza::tipo_t getTipoCoronacion(void) const;
	Pieza::tipo_t seleccionPiezaCoronacion(void);
	void resetLectura(void) { this->posicion_leida = Posicion(-1, -1); }

	/* GESTI�N DE MODELOS */
	ListaModelo* seleccionarLista(bool color, Pieza::tipo_t tipo_pieza);
	void moverModelo(const Movimiento& mov, bool color, const Pieza::tipo_t tipo);
	void generarModelosCoronacion(bool color);
	void renderModelosCoronacion(bool color);
};


#endif // !MUNDO_H