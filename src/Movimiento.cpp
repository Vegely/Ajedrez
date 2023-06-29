#include "Movimiento.h";

#include <sstream>

Movimiento::Movimiento(const std::string& str)
{
	if (str.empty() || str.size() > 11) *this = Movimiento();
	else
	{
		std::stringstream ss(str);
		std::string elementos[5];

		for (int i = 0; i < 5; i++) ss >> elementos[i];

		Movimiento movimiento(Posicion(stoi(elementos[0]), stoi(elementos[1])), Posicion(stoi(elementos[2]), stoi(elementos[3])));

		if (elementos[4] == "\0")
			*this = movimiento;
		else
			*this = Movimiento();
	}
}