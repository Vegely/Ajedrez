#include "Mundo.h"

//Modelo  rey_blanco(REY,  getPointFromCoords('e', 1),  "modelos/rey.obj", "texturas/marmol_blanco.jpg");
//Modelo dama_blanca(DAMA, getPointFromCoords('d', 1), "modelos/dama.obj", "texturas/marmol_blanco.jpg");
//
//Modelo   rey_negro(REY,  getPointFromCoords('e', 8),  "modelos/rey.obj",  "texturas/marmol_negro.jpg");
//Modelo  dama_negra(DAMA, getPointFromCoords('d', 8), "modelos/dama.obj",  "texturas/marmol_negro.jpg");
//
//std::vector<Modelo>  alfiles_blancos;
//std::vector<Modelo> caballos_blancos;
//std::vector<Modelo>   torres_blancas;
//std::vector<Modelo>   peones_blancos;
//
//std::vector<Modelo>   alfiles_negros;
//std::vector<Modelo>  caballos_negros;
//std::vector<Modelo>    torres_negras;
//std::vector<Modelo>    peones_negros;

Modelo casillas_blancas(NONE, { 0, 0, 0 }, "modelos/casillas_blancas.obj", "texturas/marmol_blanco_oscuro.jpg");
Modelo casillas_negras (NONE, { 0, 0, 0 }, "modelos/casillas_negras.obj",    "texturas/marmol_negro_claro.jpg");

Mundo::Mundo(void) :
	piezas_blancas(0),
	piezas_negras(0),
	tablero(0),
	camara({ 0.0f, 205.0f, 156.0f }, { 0 }, 60.0f),
	rayo_raton({ 0 })
{

}

void Mundo::asignarModelos(void)
{
	//for (int i = 0; i < 8; i++)
	//{
	//	peones_blancos.push_back(Modelo(PEON, getPointFromCoords('a' + i, 2), "modelos/peon.obj", "texturas/marmol_blanco.jpg"));
	//	peones_negros.push_back(Modelo(PEON, getPointFromCoords('a' + i, 7), "modelos/peon.obj", "texturas/marmol_negro.jpg"));
	//}

	//for (int i = 0; i < 2; i++)
	//{
	//	alfiles_blancos.push_back(Modelo(ALFIL, getPointFromCoords('c' + i * 3, 1), "modelos/alfil.obj", "texturas/marmol_blanco.jpg"));
	//	alfiles_negros.push_back(Modelo(ALFIL, getPointFromCoords('c' + i * 3, 8), "modelos/alfil.obj", "texturas/marmol_negro.jpg"));
	//	caballos_blancos.push_back(Modelo(CABALLO, getPointFromCoords('b' + i * 5, 1), "modelos/caballo.obj", "texturas/marmol_blanco.jpg"));
	//	caballos_negros.push_back(Modelo(CABALLO, getPointFromCoords('b' + i * 5, 8), "modelos/caballo.obj", "texturas/marmol_negro.jpg"));
	//	torres_blancas.push_back(Modelo(TORRE, getPointFromCoords('a' + i * 7, 1), "modelos/torre.obj", "texturas/marmol_blanco.jpg"));
	//	torres_negras.push_back(Modelo(TORRE, getPointFromCoords('a' + i * 7, 8), "modelos/torre.obj", "texturas/marmol_negro.jpg"));
	//}
}

void Mundo::cargarTexturas(void)
{
	//rey_blanco.cargarTextura();
	//rey_negro.cargarTextura();
	//dama_blanca.cargarTextura();
	//dama_negra.cargarTextura();

	//for (int i = 0; i < 2; i++)
	//{
	//	alfiles_blancos[i].cargarTextura();
	//	alfiles_negros[i].cargarTextura();
	//	caballos_blancos[i].cargarTextura();
	//	caballos_negros[i].cargarTextura();
	//	torres_blancas[i].cargarTextura();
	//	torres_negras[i].cargarTextura();
	//}

	//for (int i = 0; i < 8; i++)
	//{
	//	peones_blancos[i].cargarTextura();
	//	peones_negros[i].cargarTextura();
	//}

	casillas_blancas.cargarTextura();
	casillas_negras.cargarTextura();
}

void Mundo::renderizarModelos(void)
{
	//rey_blanco.render();
	//rey_negro.render();
	//dama_blanca.render();
	//dama_negra.render();

	//for (int i = 0; i < 2; i++)
	//{
	//	alfiles_blancos[i].render();
	//	alfiles_negros[i].render();
	//	caballos_blancos[i].render();
	//	caballos_negros[i].render();
	//	torres_blancas[i].render();
	//	torres_negras[i].render();
	//}

	//for (int i = 0; i < 8; i++)
	//{
	//	peones_blancos[i].render();
	//	peones_negros[i].render();
	//}

	casillas_blancas.render();
	casillas_negras.render();
}

void Mundo::renderizarHitboxes(void)
{
	//rey_blanco.renderHitbox();
	//rey_negro.renderHitbox();
	//dama_blanca.renderHitbox();
	//dama_negra.renderHitbox();

	//for (int i = 0; i < 2; i++)
	//{
	//	alfiles_blancos[i].renderHitbox();
	//	alfiles_negros[i].renderHitbox();
	//	caballos_blancos[i].renderHitbox();
	//	caballos_negros[i].renderHitbox();
	//	torres_blancas[i].renderHitbox();
	//	torres_negras[i].renderHitbox();
	//}

	//for (int i = 0; i < 8; i++)
	//{
	//	peones_blancos[i].renderHitbox();
	//	peones_negros[i].renderHitbox();
	//}

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
	static bool flag = false;
	switch (tecla)
	{
	case 'w':
		if (camara.getGirado() == false)
			camara.setPosition({ 0.0f, 205.0f, -156.0f });
		else
			camara.setPosition({ 0.0f, 205.0f, 156.0f });
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

void Mundo::raycasting(int button, int state, int x_mouse, int y_mouse)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		// Inicialización de variables necesarias
		Point proj  = { 0 };
		float radius = 0;
		float gamma = 0;
		float phi   = 0;
		float alpha = 0;
		float beta  = 0;
		float dist_cam_lookat = distanciaPuntos(camara.getPosition(), camara.getLookAt());
		float w_screen = glutGet(GLUT_WINDOW_WIDTH);
		float h_screen = glutGet(GLUT_WINDOW_HEIGHT);
		float dist_cam_screen = h_screen / tan((camara.getFovY() * (PI / 180)) / 2);
		// Obtención del ángulo del segmento camara-lookAt con el origen
		radius = sqrtf(
			camara.getPosition().x * camara.getPosition().x + 
			camara.getPosition().y * camara.getPosition().y + 
			camara.getPosition().z * camara.getPosition().z);
		gamma = atan(camara.getPosition().z / camara.getPosition().x);
		phi   = acos(camara.getPosition().y / radius);
		// Cálculo de los ángulos del rayo con el segmento camara-lookAt
		if (y_mouse > h_screen / 2)
			beta = atan((y_mouse - h_screen / 2) / dist_cam_screen);
		else if (y_mouse < h_screen / 2)
			beta = -atan(h_screen / 2 - y_mouse / dist_cam_screen);
		else
			beta = 0;
		if (x_mouse < w_screen / 2)
			alpha = -atan(w_screen / 2 - x_mouse / dist_cam_screen);
		else if (x_mouse > w_screen / 2)
			alpha = atan((x_mouse - w_screen / 2) / dist_cam_screen);
		else
			alpha = 0;
		// Ángulos finales
		float gamma_final = gamma + alpha;
		float   phi_final = phi   + beta;
		// Paso de coordenadas esféricas a cartesianas (r = 1)
		proj.x = sin(phi_final) * cos(gamma_final);
		proj.z = cos(phi_final) * sin(gamma_final);
		proj.y = cos(phi_final);
		// Normalización del vector director
		Point vec_dir = (camara.getPosition() - proj) / distanciaPuntos(camara.getPosition(), proj);
		// Rayo final
		// rayo_raton = { camara.getPosition(), Point{100, 100, 100} };
		rayo_raton = { camara.getPosition(), camara.getPosition() + vec_dir * 1000 };

		std::cout << "d_c_la: " << dist_cam_lookat << std::endl;
		std::cout << "d_c_sc: " << dist_cam_screen << std::endl;
		std::cout << "Alpha:  " << alpha  << std::endl;
		std::cout << "Beta :  " << beta   << std::endl;
		std::cout << "Radius: " << radius << std::endl;
		std::cout << "Gamma:  " << gamma  << std::endl;
		std::cout << "Phi:    " << phi    << std::endl;
		//glTranslatef(proj.x, proj.y, proj.z);
		//	glutSolidSphere(10, 10, 10);
		//glTranslatef(-proj.x, -proj.y, -proj.z);
	}
	else
		rayo_raton = { 0 };
}

Casilla Mundo::seleccionCasilla(int button, int state, int x_mouse, int y_mouse)
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

	if (camara.getGirado())
	{
		result.numero = 9 - result.numero;
		result.letra = 9 - result.letra;
	}

	std::cout << result.letra << result.numero << std::endl;
	return result;
}

int Mundo::calcMirror(int mirror)
{
	return 960 - (mirror - 960);
}