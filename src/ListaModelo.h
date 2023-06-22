#ifndef LISTAMODELO_H
#define LISTAMODELO_H

#include "Modelo.h"

class ListaModelo
{
private:
	Modelo**  _modelo;
	int		  _numElem;
	const int _maxElem;

public:
	ListaModelo(int maxElem);
	virtual ~ListaModelo(void);

	/* GESTION DE ELEMENTOS */
	void addElem   (Modelo* modelo);
	void addElem   (Modelo* modelo, const Posicion& initial_pos);
	void deleteElem(int k);
	void deleteFromCoord(const Posicion& pos);

	/* GETTERS */
	Modelo*		  operator[]  (int i)				const { return _modelo[i]; }
	Modelo*       getElem     (int i)				const { return _modelo[i]; }
	Posicion      getPosicion (int i)				const { return _modelo[i]->getCoords(); }
	int		      getMaxElem  (void)				const { return _maxElem; }
	int			  size        (void)				const { return _maxElem; }
	int			  getNumElem  (void)				const { return _numElem; }
	int			  getIndex    (const Posicion& pos) const;
	Pieza::tipo_t getTipo	  (int i)				const { return Modelo::castTipo(_modelo[i]->getTipo()); }
	bool		  getColor	  (int i)				const { return _modelo[i]->getColor(); }
	Pieza::tipo_t getTipo	  (const Posicion& pos) const;
	bool		  getColor	  (const Posicion& pos) const;
	
	/* SETTERS */
	void setPosicion(int i, const Posicion& posicion);
	void setPosicion(const Posicion& posicion) { for (int i = 0; i < _numElem; i++) _modelo[i]->setCoords(posicion); }

	/* OTROS */
	void cargarTexturas(void)				   { for (int i = 0; i < _numElem; i++) _modelo[i]->cargarTextura(); }
	void renderModelos (void)				   { for (int i = 0; i < _numElem; i++) _modelo[i]->render(); }
	void moverModelos  (const Movimiento& mov) { for (int i = 0; i < _numElem; i++) _modelo[i]->moverModelo(mov); }
	void moverElemento (const Movimiento& mov);
	void renderConRotacion(void)
	{ 
		for (int i = 0; i < _numElem; i++)
		{
			glRotatef(90 * i, 0, 1, 0);
			_modelo[i]->render();
			glRotatef(-90 * i, 0, 1, 0);
		}
	}
};

#endif
