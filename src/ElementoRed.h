#pragma once

#include <string>

class ElementoRed
{
public:
	virtual int enviar(std::string s) const = 0;
	virtual int recibir(std::string& s) const = 0;
};