#ifndef MUNDO_H
#define MUNDO_H

#include <vector>
#include "Modelo.h"
#include "Camara.h"

class Mundo
{
private:
	std::vector<Modelo*> piezas_blancas;
	std::vector<Modelo*> piezas_negras;
	std::vector<Modelo*> tablero;
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
};


#endif // !MUNDO_H


