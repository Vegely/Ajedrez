#include "Mundo.h"
#include <ETSIDI.h>
#include <string>

#define ruta_modelo_rey     "modelos/rey.obj"
#define ruta_modelo_dama    "modelos/dama.obj"
#define ruta_modelo_alfil   "modelos/alfil.obj"
#define ruta_modelo_caballo "modelos/caballo.obj"
#define ruta_modelo_torre   "modelos/torre.obj"
#define ruta_modelo_peon    "modelos/peon.obj"

#define ruta_modelo_casillas_negras  "modelos/casillas_negras.obj"
#define ruta_modelo_casillas_blancas "modelos/casillas_blancas.obj"
#define ruta_modelo_marcos           "modelos/marcos.obj"
#define ruta_modelo_letras           "modelos/letras.obj"

#define ruta_textura_blanco		   "texturas/marmol_blanco.jpg"
#define ruta_textura_negro		   "texturas/marmol_negro.jpg"
#define ruta_textura_blanco_oscuro "texturas/marmol_blanco_oscuro.jpg"
#define ruta_textura_negro_claro   "texturas/marmol_negro_claro.jpg"
#define ruta_textura_marco		   "texturas/marmol_negro_marco.jpg"

#define ruta_fondo "texturas/espacio.png"

Mundo::Mundo(void) :
	rey_blanco(),
	rey_negro(),
	damas_blancas(),
	damas_negras(),
	alfiles_blancos(),
	alfiles_negros(),
	caballos_blancos(),
	caballos_negros(),
	torres_blancas(),
	torres_negras(),
	peones_blancos(),
	peones_negros(),
	casillas_blancas(),
	casillas_negras(),
	marcos(),
	letras(),
	modelos(0),
	camara({ 0.0f, 20.5f, -15.6f }),
	casilla_leida({ 0 }),
	casillas_px()
{
	casillas_blancas = new Modelo(NONE, { 0 }, ruta_modelo_casillas_blancas, ruta_textura_blanco_oscuro);
	casillas_negras  = new Modelo(NONE, { 0 }, ruta_modelo_casillas_negras,  ruta_textura_negro_claro);
	marcos			 = new Modelo(NONE, { 0 }, ruta_modelo_marcos, ruta_textura_marco);
	letras			 = new Modelo(NONE, { 0 }, ruta_modelo_letras, ruta_textura_blanco);

	rey_blanco = new Modelo(REY, getPointFromCoords(5, 1), ruta_modelo_rey, ruta_textura_blanco);
	rey_negro  = new Modelo(REY, getPointFromCoords(5, 8), ruta_modelo_rey, ruta_textura_negro);

	for (int i = 0; i < 10; i++)
	{
		// Damas
		if (i < 9)
		{
			if (i == 0)
			{
				damas_blancas[i] = new Modelo(DAMA, getPointFromCoords(4, 1), ruta_modelo_dama, ruta_textura_blanco);
				damas_negras [i] = new Modelo(DAMA, getPointFromCoords(4, 8), ruta_modelo_dama, ruta_textura_negro);
			}
			else
			{
				damas_blancas[i] = new Modelo();
				damas_negras [i] = new Modelo();
			}
		}
		// Resto de piezas excepto peones
		if (i == 0 || i == 1)
		{
			torres_blancas  [i] = new Modelo(TORRE, getPointFromCoords(1 + i * 7, 1), ruta_modelo_torre, ruta_textura_blanco);
			torres_negras   [i] = new Modelo(TORRE, getPointFromCoords(1 + i * 7, 8), ruta_modelo_torre, ruta_textura_negro);

			caballos_blancos[i] = new Modelo(CABALLO, getPointFromCoords(2 + i * 5, 1), ruta_modelo_caballo, ruta_textura_blanco);
			caballos_negros [i] = new Modelo(CABALLO, getPointFromCoords(2 + i * 5, 8), ruta_modelo_caballo, ruta_textura_negro);

			alfiles_blancos [i] = new Modelo(ALFIL, getPointFromCoords(3 + i * 3, 1), ruta_modelo_alfil, ruta_textura_blanco);
			alfiles_negros  [i] = new Modelo(ALFIL, getPointFromCoords(3 + i * 3, 8), ruta_modelo_alfil, ruta_textura_negro);
		}
		else
		{
			torres_blancas  [i] = new Modelo();
			torres_negras   [i] = new Modelo();
			caballos_blancos[i] = new Modelo();
			caballos_negros [i] = new Modelo();
			alfiles_blancos [i] = new Modelo();
			alfiles_negros  [i] = new Modelo();
		}
		// Peones
		if (i < 8)
		{
			peones_blancos  [i] = new Modelo(ALFIL, getPointFromCoords(1 + i, 2), ruta_modelo_peon, ruta_textura_blanco);
			peones_negros   [i] = new Modelo(ALFIL, getPointFromCoords(1 + i, 7), ruta_modelo_peon, ruta_textura_negro);
		}
	}
}

void Mundo::asignarModelos(void)
{
	modelos.push_back(casillas_blancas);
	modelos.push_back(casillas_negras);
	modelos.push_back(marcos);
	modelos.push_back(letras);

	modelos.push_back(rey_blanco);
	modelos.push_back(rey_negro);

	for (int i = 0; i < 9; i++)
	{
		modelos.push_back(damas_blancas[i]);
		modelos.push_back(damas_negras[i]);
	}
	for (int i = 0; i < 10; i++)
	{
		modelos.push_back(torres_blancas[i]);
		modelos.push_back(torres_negras[i]);
		modelos.push_back(caballos_blancos[i]);
		modelos.push_back(caballos_negros[i]);
		modelos.push_back(alfiles_blancos[i]);
		modelos.push_back(alfiles_negros[i]);
	}
	for (int i = 0; i < 8; i++)
	{
		modelos.push_back(peones_blancos[i]);
		modelos.push_back(peones_negros[i]);
	}

	std::cout << "Modelos asignados." << std::endl;
}

void Mundo::cargarTexturas(void)
{
	for (auto i : modelos)
		i->cargarTextura();

	//rey_blanco->cargarTextura();
	//rey_negro ->cargarTextura();

	//for (int i = 0; i < 9; i++)
	//{
	//	damas_blancas[i]->cargarTextura();
	//	damas_negras [i]->cargarTextura();
	//}

	//for (int i = 0; i < 2; i++)
	//{
	//	alfiles_blancos [i]->cargarTextura();
	//	alfiles_negros  [i]->cargarTextura();
	//	caballos_blancos[i]->cargarTextura();
	//	caballos_negros [i]->cargarTextura();
	//	torres_blancas  [i]->cargarTextura();
	//	torres_negras   [i]->cargarTextura();
	//}

	//for (int i = 0; i < 8; i++)
	//{
	//	peones_blancos[i]->cargarTextura();
	//	 peones_negros[i]->cargarTextura();
	//}

	//casillas_blancas->cargarTextura();
	//casillas_negras ->cargarTextura();
}

void Mundo::renderizarModelos(void)
{
	for (auto i : modelos)
		i->render();

	//rey_blanco->render();
	//rey_negro ->render();

	//for (int i = 0; i < 9; i++)
	//{
	//	damas_blancas[i]->render();
	//	damas_negras [i]->render();
	//}

	//for (int i = 0; i < 2; i++)
	//{
	//	alfiles_blancos [i]->render();
	//	alfiles_negros  [i]->render();
	//	caballos_blancos[i]->render();
	//	caballos_negros [i]->render();
	//	torres_blancas  [i]->render();
	//	torres_negras   [i]->render();
	//}

	//for (int i = 0; i < 8; i++)
	//{
	//	peones_blancos[i]->render();
	//	 peones_negros[i]->render();
	//}

	//casillas_blancas->render();
	//casillas_negras ->render();
}

void Mundo::inicializarIluminacion(void)
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);  
	//glEnable(GL_LIGHT1);  
	//glEnable(GL_LIGHT2);  
	//glEnable(GL_LIGHT3);  
	//glEnable(GL_LIGHT4);
	//glEnable(GL_LIGHT5);
	//glEnable(GL_LIGHT6);
	//glEnable(GL_LIGHT7);

	// Light 0 properties (from above)
	GLfloat light0_position[] = {  1.0,  1.0,   1.0, 0.0 };
	GLfloat light1_position[] = { -1.0,  1.0,   1.0, 0.0 };
	GLfloat light2_position[] = {  1.0,  1.0,  -1.0, 0.0 };
	GLfloat light3_position[] = { -1.0,  1.0,  -1.0, 0.0 };
	GLfloat light4_position[] = {  1.0,  1.0,   1.0, 0.0 };
	GLfloat light5_position[] = { -1.0, -1.0,   1.0, 0.0 };
	GLfloat light6_position[] = {  1.0, -1.0,  -1.0, 0.0 };
	GLfloat light7_position[] = { -1.0, -1.0,  -1.0, 0.0 };

	GLfloat light_ambient[]  = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	//glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	//glLightfv(GL_LIGHT1, GL_AMBIENT,  light_ambient);
	//glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_diffuse);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);

	//glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
	//glLightfv(GL_LIGHT2, GL_AMBIENT,  light_ambient);
	//glLightfv(GL_LIGHT2, GL_DIFFUSE,  light_diffuse);
	//glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);

	//glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
	//glLightfv(GL_LIGHT3, GL_AMBIENT,  light_ambient);
	//glLightfv(GL_LIGHT3, GL_DIFFUSE,  light_diffuse);
	//glLightfv(GL_LIGHT3, GL_SPECULAR, light_specular);

	//glLightfv(GL_LIGHT4, GL_POSITION, light4_position);
	//glLightfv(GL_LIGHT4, GL_AMBIENT,  light_ambient);
	//glLightfv(GL_LIGHT4, GL_DIFFUSE,  light_diffuse);
	//glLightfv(GL_LIGHT4, GL_SPECULAR, light_specular);

	//glLightfv(GL_LIGHT5, GL_POSITION, light5_position);
	//glLightfv(GL_LIGHT5, GL_AMBIENT,  light_ambient);
	//glLightfv(GL_LIGHT5, GL_DIFFUSE,  light_diffuse);
	//glLightfv(GL_LIGHT5, GL_SPECULAR, light_specular);

	//glLightfv(GL_LIGHT6, GL_POSITION, light6_position);
	//glLightfv(GL_LIGHT6, GL_AMBIENT,  light_ambient);
	//glLightfv(GL_LIGHT6, GL_DIFFUSE,  light_diffuse);
	//glLightfv(GL_LIGHT6, GL_SPECULAR, light_specular);

	//glLightfv(GL_LIGHT7, GL_POSITION, light7_position);
	//glLightfv(GL_LIGHT7, GL_AMBIENT,  light_ambient);
	//glLightfv(GL_LIGHT7, GL_DIFFUSE,  light_diffuse);
	//glLightfv(GL_LIGHT7, GL_SPECULAR, light_specular);

	glClearColor(0.0, 0.0, 0.0, 0.0);
}

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

void Mundo::keylift(unsigned char tecla)
{
	camara.setSpeed({ 0 });
	camara.printPosition(std::cout);
}

void Mundo::seleccionCasilla(int button, int state, int x_mouse, int y_mouse)
{
	Posicion result = Posicion{ 0 };
	Corners<Point> slot;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			slot = casillas_px.getSlotCoords(i, j);
			if (x_mouse < slot.lr.x && x_mouse > slot.ll.x && y_mouse < slot.ll.y && y_mouse > slot.ul.y)
				result = Posicion{ i + 1, j + 1 };
		}
	}

	if (!camara.getGirado())
	{
		result.x = 9 - result.x;
		result.y = 9 - result.y;
	}

	std::cout << result.x << result.y << std::endl;
	casilla_leida = result;
}

void Mundo::dibujarFondo(void)
{
	glTranslatef(100, -10, 0);
	glRotatef(90.0f, 1, 0, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(ruta_fondo).id);
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

void Mundo::moverModelo(const Movimiento& movimiento)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			
		}
	}
}