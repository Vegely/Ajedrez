#include "ListaModelo.h"

void ListaModelo::addElem(Modelo* modelo)
{
	if (_numElem == _maxElem)
	{
		std::cout << "Max number of elements reached." << std::endl;
		return;
	}
	else
	{
		_modelo[_numElem++] = modelo;
		std::cout << "Element added. Number of elemets is now " << this->_numElem << std::endl;
	}
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
		std::cout << "Element deleted. Number of elemets is now " << this->_numElem << std::endl;
	}
}

void ListaModelo::deleteFromCoord(const Posicion& pos)
{
	for (int i = 0; i < this->size(); i++)
	{
		if (this->getPosicion(i) == pos)
			this->deleteElem(i);
	}
}