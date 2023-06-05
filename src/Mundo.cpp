#include "Mundo.h"
#include <ETSIDI.h>
#include <string>

#define ruta_rey     "modelos/rey.obj"
#define ruta_dama    "modelos/dama.obj"
#define ruta_alfil   "modelos/alfil.obj"
#define ruta_caballo "modelos/caballo.obj"
#define ruta_torre   "modelos/torre.obj"
#define ruta_peon    "modelos/peon.obj"

#define ruta_casillas_negras  "modelos/casillas_negras.obj"
#define ruta_casillas_blancas "modelos/casillas_blancas.obj"
#define ruta_marcos           "modelos/marcos.obj"
#define ruta_letras           "modelos/letras.obj"

#define ruta_textura_blanco			"texturas/marmol_blanco.jpg"
#define ruta_textura_negro			"texturas/marmol_negro.jpg"
#define ruta_textura_blanco_oscuro "texturas/marmol_blanco_oscuro.jpg"
#define ruta_textura_negro_claro   "texturas/marmol_negro_claro.jpg"

#define ruta_fondo "texturas/espacio.png"

Modelo  rey_blanco(REY,  getPointFromCoords('e', 1), ruta_rey,  ruta_textura_blanco);
Modelo dama_blanca(DAMA, getPointFromCoords('d', 1), ruta_dama, ruta_textura_blanco);

Modelo   rey_negro(REY,  getPointFromCoords('e', 8), ruta_rey,  ruta_textura_negro);
Modelo  dama_negra(DAMA, getPointFromCoords('d', 8), ruta_dama, ruta_textura_negro);


std::vector<Modelo>  alfiles_blancos;
std::vector<Modelo> caballos_blancos;
std::vector<Modelo>   torres_blancas;
std::vector<Modelo>   peones_blancos;

std::vector<Modelo>   alfiles_negros;
std::vector<Modelo>  caballos_negros;
std::vector<Modelo>    torres_negras;
std::vector<Modelo>    peones_negros;

Modelo casillas_blancas(NONE, { 0, 0, 0 }, ruta_casillas_blancas, ruta_textura_blanco_oscuro);
Modelo casillas_negras (NONE, { 0, 0, 0 }, ruta_casillas_negras,  ruta_textura_negro_claro);
Modelo marcos(NONE, { 0 }, ruta_marcos, ruta_textura_negro_claro);
Modelo letras(NONE, { 0 }, ruta_letras, ruta_textura_blanco_oscuro);



Mundo::Mundo(void) :
	arrayModelos(0),
	camara({ 0.0f, 205.0f, 156.0f }, { 0 }, 60.0f),
	casilla_leida({0})
{
	asignarModelos();

	arrayModelos.push_back(&rey_blanco);
	arrayModelos.push_back(&rey_negro);
	arrayModelos.push_back(&dama_blanca);
	arrayModelos.push_back(&dama_negra);

	/*for (int i = 0; i < 8; i++)
	{
		arrayModelos.push_back(&peones_blancos[i]);
		arrayModelos.push_back(&peones_negros[i]);
	}*/

	for (int i = 0; i < 2; i++)
	{
		arrayModelos.push_back(&alfiles_blancos[i]);
		arrayModelos.push_back(&alfiles_negros[i]);
		arrayModelos.push_back(&caballos_blancos[i]);
		arrayModelos.push_back(&caballos_negros[i]);
		arrayModelos.push_back(&torres_blancas[i]);
		arrayModelos.push_back(&torres_negras[i]);
	}
}

void Mundo::asignarModelos(void)
{
	//peones_blancos.push_back(Modelo(PEON, Point{ (float)0,2 }, ruta_peon, ruta_textura_blanco));
	//peones_blancos.push_back(Modelo(PEON, Point{ (float)1,2 }, ruta_peon, ruta_textura_blanco));
	//peones_blancos.push_back(Modelo(PEON, Point{ (float)2,2 }, ruta_peon, ruta_textura_blanco));
	//peones_blancos.push_back(Modelo(PEON, Point{ (float)3,2 }, ruta_peon, ruta_textura_blanco));
	//peones_blancos.push_back(Modelo(PEON, Point{ (float)4,2 }, ruta_peon, ruta_textura_blanco));
	//peones_blancos.push_back(Modelo(PEON, Point{ (float)5,2 }, ruta_peon, ruta_textura_blanco));
	//peones_blancos.push_back(Modelo(PEON, Point{ (float)6,2 }, ruta_peon, ruta_textura_blanco));
	//peones_blancos.push_back(Modelo(PEON, Point{ (float)7,2 }, ruta_peon, ruta_textura_blanco));
	
	/*for (int i = 0; i < 8; i++)
	{
		peones_blancos.push_back(Modelo(PEON,Point{(float)i,2}, ruta_peon, ruta_textura_blanco));
		peones_negros.push_back(Modelo(PEON, Point{(float)i,7}, ruta_peon, ruta_textura_negro));
	}*/

	for (int i = 0; i < 2; i++)
	{
		 alfiles_blancos.push_back(Modelo(ALFIL,   getPointFromCoords('c' + i * 3, 1), ruta_alfil,   ruta_textura_blanco));
		  alfiles_negros.push_back(Modelo(ALFIL,   getPointFromCoords('c' + i * 3, 8), ruta_alfil,   ruta_textura_negro));
		caballos_blancos.push_back(Modelo(CABALLO, getPointFromCoords('b' + i * 5, 1), ruta_caballo, ruta_textura_blanco));
		 caballos_negros.push_back(Modelo(CABALLO, getPointFromCoords('b' + i * 5, 8), ruta_caballo, ruta_textura_negro));
		  torres_blancas.push_back(Modelo(TORRE,   getPointFromCoords('a' + i * 7, 1), ruta_torre,   ruta_textura_blanco));
		   torres_negras.push_back(Modelo(TORRE,   getPointFromCoords('a' + i * 7, 8), ruta_torre,   ruta_textura_negro));
	}
	std::cout << "Modelos asignados." << std::endl;
}

void Mundo::cargarTexturas(void)
{
	 rey_blanco.cargarTextura();
	  rey_negro.cargarTextura();
	dama_blanca.cargarTextura();
	 dama_negra.cargarTextura();

	for (int i = 0; i < 2; i++)
	{
		 alfiles_blancos[i].cargarTextura();
		  alfiles_negros[i].cargarTextura();
		caballos_blancos[i].cargarTextura();
		 caballos_negros[i].cargarTextura();
		  torres_blancas[i].cargarTextura();
		   torres_negras[i].cargarTextura();
	}

	for (int i = 0; i < 8; i++)
	{
		peones_blancos[i].cargarTextura();
		 peones_negros[i].cargarTextura();
	}

	casillas_blancas.cargarTextura();
	 casillas_negras.cargarTextura();
			  //marcos.cargarTextura();
			  //letras.cargarTextura();
}

void Mundo::renderizarModelos(void)
{
	 rey_blanco.render();
	  rey_negro.render();
	dama_blanca.render();
	 dama_negra.render();

	for (int i = 0; i < 2; i++)
	{
		 alfiles_blancos[i].render();
		  alfiles_negros[i].render();
		caballos_blancos[i].render();
		 caballos_negros[i].render();
		  torres_blancas[i].render();
		   torres_negras[i].render();
	}

	for (int i = 0; i < 8; i++)
	{
		peones_blancos[i].render();
		 peones_negros[i].render();
	}

	casillas_blancas.render();
	 casillas_negras.render();
			  //marcos.render();
			  //letras.render();
}


void Mundo::inicializarIluminacion(void)
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);  
	glEnable(GL_LIGHT1);  
	glEnable(GL_LIGHT2);  
	glEnable(GL_LIGHT3);  
	glEnable(GL_LIGHT4);
	glEnable(GL_LIGHT5);
	glEnable(GL_LIGHT6);
	glEnable(GL_LIGHT7);

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

	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightfv(GL_LIGHT1, GL_AMBIENT,  light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);

	glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
	glLightfv(GL_LIGHT2, GL_AMBIENT,  light_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE,  light_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);

	glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
	glLightfv(GL_LIGHT3, GL_AMBIENT,  light_ambient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE,  light_diffuse);
	glLightfv(GL_LIGHT3, GL_SPECULAR, light_specular);

	glLightfv(GL_LIGHT4, GL_POSITION, light4_position);
	glLightfv(GL_LIGHT4, GL_AMBIENT,  light_ambient);
	glLightfv(GL_LIGHT4, GL_DIFFUSE,  light_diffuse);
	glLightfv(GL_LIGHT4, GL_SPECULAR, light_specular);

	glLightfv(GL_LIGHT5, GL_POSITION, light5_position);
	glLightfv(GL_LIGHT5, GL_AMBIENT,  light_ambient);
	glLightfv(GL_LIGHT5, GL_DIFFUSE,  light_diffuse);
	glLightfv(GL_LIGHT5, GL_SPECULAR, light_specular);

	glLightfv(GL_LIGHT6, GL_POSITION, light6_position);
	glLightfv(GL_LIGHT6, GL_AMBIENT,  light_ambient);
	glLightfv(GL_LIGHT6, GL_DIFFUSE,  light_diffuse);
	glLightfv(GL_LIGHT6, GL_SPECULAR, light_specular);

	glLightfv(GL_LIGHT7, GL_POSITION, light7_position);
	glLightfv(GL_LIGHT7, GL_AMBIENT,  light_ambient);
	glLightfv(GL_LIGHT7, GL_DIFFUSE,  light_diffuse);
	glLightfv(GL_LIGHT7, GL_SPECULAR, light_specular);

	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void Mundo::keypress(unsigned char tecla)
{
	static bool flag = false;
	switch (tecla)
	{
	case 'w':
		if (camara.getGirado() == false)
			camara.setPosition({ 0.0f, 205.0f, -156.0f });
		else
			camara.setPosition({ 0.0f, 205.0f, -156.0f });

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
	Casilla result;
	if (y_mouse < 900 && y_mouse > 790)
		result.numero = 1;
	if (y_mouse < 790 && y_mouse > 690)
		result.numero = 2;
	if (y_mouse < 690 && y_mouse > 606)
		result.numero = 3;
	if (y_mouse < 606 && y_mouse > 530)
		result.numero = 4;
	if (y_mouse < 530 && y_mouse > 465)
		result.numero = 5;
	if (y_mouse < 465 && y_mouse > 405)
		result.numero = 6;
	if (y_mouse < 405 && y_mouse > 350)
		result.numero = 7;
	if (y_mouse < 350 && y_mouse > 300)
		result.numero = 8;

	if (result.numero == 1)
	{
		if (x_mouse > calcMirror(1393) && x_mouse < calcMirror(1285))
			result.letra = 1;
		if (x_mouse > calcMirror(1285) && x_mouse < calcMirror(1177))
			result.letra = 2;
		if (x_mouse > calcMirror(1177) && x_mouse < calcMirror(1068))
			result.letra = 3;
		if (x_mouse > calcMirror(1068) && x_mouse < calcMirror(960))
			result.letra = 4;
		if (x_mouse > 960 && x_mouse < 1068)
			result.letra = 5;
		if (x_mouse > 1068 && x_mouse < 1177)
			result.letra = 6;
		if (x_mouse > 1177 && x_mouse < 1285)
			result.letra = 7;
		if (x_mouse > 1285 && x_mouse < 1393)
			result.letra = 8;
	}
	if (result.numero == 2)
	{
		if (x_mouse > calcMirror(1363) && x_mouse < calcMirror(1263))
			result.letra = 1;
		if (x_mouse > calcMirror(1263) && x_mouse < calcMirror(1163))
			result.letra = 2;
		if (x_mouse > calcMirror(1163) && x_mouse < calcMirror(1061))
			result.letra = 3;
		if (x_mouse > calcMirror(1061) && x_mouse < calcMirror(960))
			result.letra = 4;
		if (x_mouse > 960 && x_mouse < 1061)
			result.letra = 5;
		if (x_mouse > 1061 && x_mouse < 1163)
			result.letra = 6;
		if (x_mouse > 1163 && x_mouse < 1263)
			result.letra = 7;
		if (x_mouse > 1263 && x_mouse < 1363)
			result.letra = 8;
	}
	if (result.numero == 3)
	{
		if (x_mouse > calcMirror(1340) && x_mouse < calcMirror(1245))
			result.letra = 1;
		if (x_mouse > calcMirror(1245) && x_mouse < calcMirror(1150))
			result.letra = 2;
		if (x_mouse > calcMirror(1150) && x_mouse < calcMirror(1055))
			result.letra = 3;
		if (x_mouse > calcMirror(1055) && x_mouse < calcMirror(960))
			result.letra = 4;
		if (x_mouse > 960 && x_mouse < 1055)
			result.letra = 5;
		if (x_mouse > 1055 && x_mouse < 1150)
			result.letra = 6;
		if (x_mouse > 1150 && x_mouse < 1245)
			result.letra = 7;
		if (x_mouse > 1245 && x_mouse < 1340)
			result.letra = 8;
	}
	if (result.numero == 4)
	{
		if (x_mouse > calcMirror(1320) && x_mouse < calcMirror(1230))
			result.letra = 1;
		if (x_mouse > calcMirror(1230) && x_mouse < calcMirror(1140))
			result.letra = 2;
		if (x_mouse > calcMirror(1140) && x_mouse < calcMirror(1050))
			result.letra = 3;
		if (x_mouse > calcMirror(1050) && x_mouse < calcMirror(960))
			result.letra = 4;
		if (x_mouse > 960 && x_mouse < 1050)
			result.letra = 5;
		if (x_mouse > 1050 && x_mouse < 1140)
			result.letra = 6;
		if (x_mouse > 1140 && x_mouse < 1230)
			result.letra = 7;
		if (x_mouse > 1230 && x_mouse < 1320)
			result.letra = 8;
	}
	if (result.numero == 5)
	{
		if (x_mouse > calcMirror(1300) && x_mouse < calcMirror(1213))
			result.letra = 1;
		if (x_mouse > calcMirror(1213) && x_mouse < calcMirror(1128))
			result.letra = 2;
		if (x_mouse > calcMirror(1128) && x_mouse < calcMirror(1045))
			result.letra = 3;
		if (x_mouse > calcMirror(1045) && x_mouse < calcMirror(960))
			result.letra = 4;
		if (x_mouse > 960 && x_mouse < 1045)
			result.letra = 5;
		if (x_mouse > 1045 && x_mouse < 1128)
			result.letra = 6;
		if (x_mouse > 1128 && x_mouse < 1213)
			result.letra = 7;
		if (x_mouse > 1213 && x_mouse < 1300)
			result.letra = 8;
	}
	if (result.numero == 6)
	{
		if (x_mouse > calcMirror(1280) && x_mouse < calcMirror(1200))
			result.letra = 1;
		if (x_mouse > calcMirror(1200) && x_mouse < calcMirror(1120))
			result.letra = 2;
		if (x_mouse > calcMirror(1120) && x_mouse < calcMirror(1040))
			result.letra = 3;
		if (x_mouse > calcMirror(1040) && x_mouse < calcMirror(960))
			result.letra = 4;
		if (x_mouse > 960 && x_mouse < 1040)
			result.letra = 5;
		if (x_mouse > 1040 && x_mouse < 1120)
			result.letra = 6;
		if (x_mouse > 1120 && x_mouse < 1200)
			result.letra = 7;
		if (x_mouse > 1200 && x_mouse < 1280)
			result.letra = 8;
	}
	if (result.numero == 7)
	{
		if (x_mouse > calcMirror(1268) && x_mouse < calcMirror(1188))
			result.letra = 1;
		if (x_mouse > calcMirror(1188) && x_mouse < calcMirror(1111))
			result.letra = 2;
		if (x_mouse > calcMirror(1111) && x_mouse < calcMirror(1040))
			result.letra = 3;
		if (x_mouse > calcMirror(1040) && x_mouse < calcMirror(960))
			result.letra = 4;
		if (x_mouse > 960 && x_mouse < 1040)
			result.letra = 5;
		if (x_mouse > 1040 && x_mouse < 1111)
			result.letra = 6;
		if (x_mouse > 1111 && x_mouse < 1188)
			result.letra = 7;
		if (x_mouse > 1188 && x_mouse < 1268)
			result.letra = 8;
	}
	if (result.numero == 8)
	{
		if (x_mouse > calcMirror(1268) && x_mouse < calcMirror(1188))
			result.letra = 1;
		if (x_mouse > calcMirror(1188) && x_mouse < calcMirror(1111))
			result.letra = 2;
		if (x_mouse > calcMirror(1111) && x_mouse < calcMirror(1040))
			result.letra = 3;
		if (x_mouse > calcMirror(1040) && x_mouse < calcMirror(960))
			result.letra = 4;
		if (x_mouse > 960 && x_mouse < 1032)
			result.letra = 5;
		if (x_mouse > 1032 && x_mouse < 1100)
			result.letra = 6;
		if (x_mouse > 1100 && x_mouse < 1177)
			result.letra = 7;
		if (x_mouse > 1177 && x_mouse < 1250)
			result.letra = 8;
	}

	if (!camara.getGirado())
	{
		result.numero = 9 - result.numero;
		result.letra = 9 - result.letra;
	}

	std::cout << result.letra << result.numero << std::endl;
	casilla_leida = result;;
}

int Mundo::calcMirror(int mirror)
{
	return 960 - (mirror - 960);
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
	for (auto iterador : arrayModelos)
	{
		iterador->moverModelo(movimiento);
	}
}