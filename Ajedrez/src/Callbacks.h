// Callbacks.h | Header file for callback functions

#ifndef CALLBACKS_H
#define CALLBAKCS_H

#include "Camara.h"  // Cámara
#include "Modelo.h"	 // Clase Modelo

/* INITIALIZATION */
void motorGrafico(int* argc, char** argv);

/* GLUT CALLBACKS */
void OnDraw(void);
void OnTimer(int value);
void OnReshape(int w, int h);
void OnMouseMotion(int x, int y);
void OnMouseClick(int button, int state, int x, int y);
void OnKeyboardDown(const unsigned char key, int x, int y);
void OnKeyboardUp(const unsigned char key, int x, int y);
void OnKeyboardSpecial(int key, int x, int y);

/* DEBUG AXIS */
void debugAxis(void);

void inicializarEstadoOpenGL(void);
void inicializarIluminacion(void);
void registrarCallbacks(void);
void asignarModelos(void);
void cargarTexturas(void);
void renderizarModelos(void);

#endif
