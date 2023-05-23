#include "Mundo.h"

Modelo  rey_blanco(REY,  getPointFromCoords('e', 1),  "modelos/rey.obj", "texturas/marmol_blanco.jpg");
Modelo dama_blanca(DAMA, getPointFromCoords('d', 1), "modelos/dama.obj", "texturas/marmol_blanco.jpg");

Modelo   rey_negro(REY,  getPointFromCoords('e', 8),  "modelos/rey.obj",  "texturas/marmol_negro.jpg");
Modelo  dama_negra(DAMA, getPointFromCoords('d', 8), "modelos/dama.obj",  "texturas/marmol_negro.jpg");

std::vector<Modelo>  alfiles_blancos;
std::vector<Modelo> caballos_blancos;
std::vector<Modelo>   torres_blancas;
std::vector<Modelo>   peones_blancos;

std::vector<Modelo>   alfiles_negros;
std::vector<Modelo>  caballos_negros;
std::vector<Modelo>    torres_negras;
std::vector<Modelo>    peones_negros;

Modelo casillas_blancas(NONE, { 0, 0, 0 }, "modelos/casillas_blancas.obj", "texturas/marmol_blanco_oscuro.jpg");
Modelo casillas_negras (NONE, { 0, 0, 0 }, "modelos/casillas_negras.obj",    "texturas/marmol_negro_claro.jpg");

Mundo::Mundo(void) :
	piezas_blancas(0),
	piezas_negras(0),
	tablero(0),
	camara({ 0.0f, 220.0f, 111.0f }, { 0 })
{

}

void Mundo::asignarModelos(void)
{
	for (int i = 0; i < 8; i++)
	{
		peones_blancos.push_back(Modelo(PEON, getPointFromCoords('a' + i, 2), "modelos/peon.obj", "texturas/marmol_blanco.jpg"));
		peones_negros.push_back(Modelo(PEON, getPointFromCoords('a' + i, 7), "modelos/peon.obj", "texturas/marmol_negro.jpg"));
	}

	for (int i = 0; i < 2; i++)
	{
		alfiles_blancos.push_back(Modelo(ALFIL, getPointFromCoords('c' + i * 3, 1), "modelos/alfil.obj", "texturas/marmol_blanco.jpg"));
		alfiles_negros.push_back(Modelo(ALFIL, getPointFromCoords('c' + i * 3, 8), "modelos/alfil.obj", "texturas/marmol_negro.jpg"));
		caballos_blancos.push_back(Modelo(CABALLO, getPointFromCoords('b' + i * 5, 1), "modelos/caballo.obj", "texturas/marmol_blanco.jpg"));
		caballos_negros.push_back(Modelo(CABALLO, getPointFromCoords('b' + i * 5, 8), "modelos/caballo.obj", "texturas/marmol_negro.jpg"));
		torres_blancas.push_back(Modelo(TORRE, getPointFromCoords('a' + i * 7, 1), "modelos/torre.obj", "texturas/marmol_blanco.jpg"));
		torres_negras.push_back(Modelo(TORRE, getPointFromCoords('a' + i * 7, 8), "modelos/torre.obj", "texturas/marmol_negro.jpg"));
	}
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
}

void Mundo::renderizarHitboxes(void)
{
	rey_blanco.renderHitbox();
	rey_negro.renderHitbox();
	dama_blanca.renderHitbox();
	dama_negra.renderHitbox();

	for (int i = 0; i < 2; i++)
	{
		alfiles_blancos[i].renderHitbox();
		alfiles_negros[i].renderHitbox();
		caballos_blancos[i].renderHitbox();
		caballos_negros[i].renderHitbox();
		torres_blancas[i].renderHitbox();
		torres_negras[i].renderHitbox();
	}

	for (int i = 0; i < 8; i++)
	{
		peones_blancos[i].renderHitbox();
		peones_negros[i].renderHitbox();
	}

	casillas_blancas.renderHitbox();
	casillas_negras.renderHitbox();
}

void Mundo::inicializarIluminacion(void)
{
	glLightfv(GL_LIGHT0, GL_POSITION, camara.getLightPos());
	glLightfv(GL_LIGHT0, GL_AMBIENT,  camara.getLightAmb());
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  camara.getLightDif());
	glLightfv(GL_LIGHT0, GL_SPECULAR, camara.getLightSpe());
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
}

void Mundo::keypress(unsigned char tecla)
{
	switch (tecla)
	{
	case 'a':
		camara.setSpeed({ -500.0f, 0, 0 });
		break;
	case 'd':
		camara.setSpeed({ 500.0f, 0, 0 });
		break;
	case 's':
		camara.setSpeed({ 0, -500.0f, 0 });
		break;
	case 'w':
		camara.setSpeed({ 0, 500.0f, 0 });
		break;
	case 'q':
		camara.setSpeed({ 0, 0, 500.0f });
		break;
	case 'e':
		camara.setSpeed({ 0, 0, -500.0f });
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