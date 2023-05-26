#ifndef MUNDO_H
#define MUNDO_H

#include <vector>
#include "Modelo.h"
#include "Camara.h"

struct Casilla
{
	int letra;
	int numero;
};

class Mundo
{
private:
	Camara camara;

public:
	Mundo(void);

	void asignarModelos    (void);
	void cargarTexturas    (void);
	void renderizarModelos (void);
	void renderizarHitboxes(void);
	void inicializarIluminacion(void);
	void updateCamara(void) { camara.update(); }
	void movimiento(const float time) { camara.movement(time); }
	void keypress(unsigned char tecla);
	void keylift(unsigned char tecla);
	void raycasting(int button, int state, int x_mouse, int y_mouse);
	//void renderizarRayoRaton(void) { glColor3f(255, 0, 0); drawLine(rayo_raton.p1, rayo_raton.p2); }
	float getFovY(void) const { return camara.getFovY(); }
	Casilla seleccionCasilla(int button, int state, int x_mouse, int y_mouse);
	int calcMirror(int mirror);
	bool getGirado(void) { return camara.getGirado(); }
	void dibujarFondo(void);
};


#endif // !MUNDO_H