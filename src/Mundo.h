#ifndef MUNDO_H
#define MUNDO_H

#include <vector>
#include "Modelo.h"
#include "Camara.h"
#include "Movimiento.h"
#include "Casilla.h"

class Mundo
{
private:
	std::vector<Modelo*> arrayModelos;
	Camara camara;
	Casilla casilla_leida;

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
	//void raycasting(int button, int state, int x_mouse, int y_mouse);
	//void renderizarRayoRaton(void) { glColor3f(255, 0, 0); drawLine(rayo_raton.p1, rayo_raton.p2); }
	float getFovY(void) const { return camara.getFovY(); }
	void seleccionCasilla(int button, int state, int x_mouse, int y_mouse);
	int calcMirror(int mirror);
	bool getGirado(void) { return camara.getGirado(); }
	void dibujarFondo(void);
	Casilla getCasilla(void) { return this->casilla_leida; }

	void moverModelo(const Movimiento& movimiento);
};


#endif // !MUNDO_H