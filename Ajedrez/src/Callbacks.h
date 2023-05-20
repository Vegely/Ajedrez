// Callbacks.h | Header file for callback functions called by GLUT

#ifndef GLUTCALLBACKS_H
#define GLUTCALLBAKCS_H

#include <freeglut.h>
#include "Globals.h"

#include "Camera.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <iostream>

void graphicsInit(int* argc, char** argv);

void OnDraw(void);
void OnTimer(int value);
void OnReshape(int w, int h);
void OnMouseMotion(int x, int y);
void OnMouseClick(int button, int state, int x, int y);
void OnKeyboardDown(const unsigned char key, int x, int y);
void OnKeyboardUp(const unsigned char key, int x, int y);
void OnKeyboardSpecial(int key, int x, int y);

void debugAxis(void);

void import_model(const char* filename);

#endif
