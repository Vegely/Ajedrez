// Callbacks.h | Header file for callback functions

#ifndef CALLBACKS_H
#define CALLBAKCS_H

/* INICIALIZACION */
void motorGrafico(int* argc, char** argv);
void inicializarIluminacion(void);
void inicializarEstadoOpenGL(void);
void registrarCallbacks(void);
/* GLUT CALLBACKS */
void OnDraw(void);
void OnReshape(int w, int h);
void OnTimer(int value);
void OnKeyboardDown(const unsigned char key, int x, int y);
void OnKeyboardUp(const unsigned char key, int x, int y);
void OnKeyboardSpecial(int key, int x, int y);
void OnMouseClick(int button, int state, int x, int y);
void OnMouseMotion(int x, int y);
/* DEBUG AXIS */
void debugAxis(void);
#endif
