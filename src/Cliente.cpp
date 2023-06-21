#include "Cliente.h"

int Cliente::enviar(std::string s) const
{
	return sck->envia(s);
}

int Cliente::recibir(std::string& s) const
{
	return sck->recibe(s);
}

bool Cliente::conectar() {
	//IP del equipo al que se conecta ("127.0.0.1" --> localhost)
	//NULL: no se especifican opciones en host_info
	sck = new Socket{ NULL };

	sck->creaSocket(ipv4.c_str());


	if (!sck->conectarAServidor())
		return false;
	return true;
}

void Cliente::desconectar() {
	sck->desconecta();

	//Conexión cerrada: elimina el socket para la comunicación
	delete sck;
}
