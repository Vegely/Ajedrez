#ifndef _ELEMENTORED__H_
#define _ELEMENTORED__H_

#include <string>

class ElementoRed
{
public:
	virtual int enviar(std::string s) const = 0;
	virtual int recibir(std::string& s) const = 0;
};

#endif // !_ELEMENTORED__H_