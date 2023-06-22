#ifndef _ELEMENTORED__H_
#define _ELEMENTORED__H_

#include <string>

class ElementoRed
{
public:
	std::string recibido = "";

	virtual void inicializa() = 0;

	virtual bool conectar() = 0;
	virtual void desconectar() = 0;

	virtual int enviar(std::string s) const = 0;
	virtual int recibir(std::string& s) const = 0;

	virtual std::string getIp() = 0;
	virtual void setIp(std::string ip) {}
};

#endif // !_ELEMENTORED__H_