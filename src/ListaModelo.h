#ifndef LISTAMODELO_H
#define LISTAMODELO_H

#include "Modelo.h"

class ListaModelo
{
private:
	Modelo** _modelo;
	int _numElem;
	const int _maxElem;

public:
	ListaModelo(int maxElem) : _modelo(new Modelo*[maxElem]), _numElem(0), _maxElem(maxElem) { for (int i = 0; i < _maxElem; i++) _modelo[i] = new Modelo(); }
	virtual ~ListaModelo(void) { for (int i = 0; i < _maxElem; i++) delete[] _modelo[i]; delete _modelo; }

	/* GESTIÓN DE ELEMENTOS */
	void addElem   (Modelo* modelo);
	void deleteElem(int k);
	void deleteFromCoord(const Posicion& pos);

	/* GETTERS */
	Modelo*  operator[] (int i) const { return _modelo[i]; }
	Posicion getPosicion(int i) const { return _modelo[i]->getCoords(); }
	int		 getMaxElem (void)  const { return _maxElem; }
	int		 size		(void)	const { return _numElem; }
	int		 getNumElem (void)	const { return _numElem; }
	
	/* SETTERS */
	void setPosicion(int i, const Posicion& posicion) { _modelo[i]->setCoords(posicion); }

	/* OTROS */
	void cargarTexturas(void)				   { for (int i = 0; i < _numElem; i++) _modelo[i]->cargarTextura(); }
	void renderModelos (void)				   { for (int i = 0; i < _numElem; i++) _modelo[i]->render(); }
	void moverModelos  (const Movimiento& mov) { for (int i = 0; i < _numElem; i++) _modelo[i]->moverModelo(mov); }
};

#endif
