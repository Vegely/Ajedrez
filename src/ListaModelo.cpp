#include "ListaModelo.h"

ListaModelo::ListaModelo(int maxElem) :
	_modelo(new Modelo* [maxElem]),
	_numElem(0),
	_maxElem(maxElem)
{
	for (int i = 0; i < _maxElem; i++) _modelo[i] = new Modelo();
}

ListaModelo::~ListaModelo(void)
{
	for (int i = 0; i < _maxElem; i++) 
		delete _modelo[i];

	delete[] _modelo;
}

void ListaModelo::addElem(Modelo* modelo)
{
	if (this->_numElem == this->_maxElem)
		return;
	else
		this->_modelo[this->_numElem++] = modelo;
}

void ListaModelo::addElem(Modelo* modelo, const Posicion& initial_pos)
{
	addElem(modelo);
	modelo->setCoords(initial_pos);
}

void ListaModelo::deleteElem(int k)
{
	if (k > _numElem)
	{
		std::cout << "Not an existing element." << std::endl;
		return;
	}
	else
	{
		delete _modelo[k];
		for (int i = k; i < _numElem; i++) // Shift
		{
			_modelo[i] = _modelo[i + 1];
		}
		_numElem--;
	}
}

void ListaModelo::deleteFromCoord(const Posicion& pos)
{
	if (this != nullptr)
	{
		for (int i = 0; i < this->size(); i++)
		{
			if (this->getPosicion(i) == pos)
			{
				this->deleteElem(i);
				return;
			}
		}
	}
	else
		std::cout << "This list is a nullptr." << std::endl;
}

int ListaModelo::getIndex(const Posicion& pos) const
{
	for (int i = 0; i < this->_numElem; i++)
	{
		if (_modelo[i]->getCoords() == pos)
			return i;
	}
	return -1;
}

Pieza::tipo_t ListaModelo::getTipo(const Posicion& pos) const
{
	for (int i = 0; i < this->size(); i++)
	{
		if (this->_modelo[i]->getCoords() == pos)
			return this->getTipo(i);
		if (i == this->size() - 1)
			return Pieza::tipo_t::NULA;
	}
}

bool ListaModelo::getColor(const Posicion& pos) const
{
	for (int i = 0; i < this->size(); i++)
	{
		if (this->_modelo[i]->getCoords() == pos)
			return this->getColor(i);
		if (i == this->size() - 1)
			return false;
	}
}

void ListaModelo::setPosicion(int i, const Posicion& posicion)
{
	if (i <= _numElem)
		_modelo[i]->setCoords(posicion);
	else
		std::cout << "Not an element in the list." << std::endl;
}

void ListaModelo::moverElemento(const Movimiento& mov)
{
	if (_numElem <= _maxElem && this != nullptr)
	{
		for (int i = 0; i < _numElem; i++)
		{
			if (_modelo[i]->moverModelo(mov))
				return;
		}
	}
}