#include "Cliente.h"

int Cliente::enviarAServidor(std::string s) {
	return sck->envia(s);
}

int Cliente::recibirDeServidor(std::string& s) {
	return sck->recibe(s);
}

bool Cliente::conectarCliente() {
	//IP del equipo al que se conecta ("127.0.0.1" --> localhost)
	//NULL: no se especifican opciones en host_info
	sck = new Socket{ NULL };

	sck->creaSocket(ipv4.c_str());


	if (!sck->conectarAServidor())
		return false;
	return true;
}

void Cliente::desconectarCliente() {
	sck->desconecta();

	//Conexión cerrada: elimina el socket para la comunicación
	delete sck;
}
