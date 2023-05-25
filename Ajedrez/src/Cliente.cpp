#include "Cliente.h"

int Cliente::enviarAServidor(std::string s) {
	return sck->envia(s);
}

int Cliente::recibirDeServidor(std::string& s) {
	return sck->recibe(s);
}

void Cliente::conectarCliente() {
	//IP del equipo al que se conecta ("127.0.0.1" --> localhost)
	//NULL: no se especifican opciones en host_info
	sck = new Socket{ NULL };

	sck->creaSocket(ipv4.c_str());


	sck->conectarAServidor();
}

void Cliente::desconectarCliente() {
	sck->desconecta();

	//Conexión cerrada: elimina el socket para la comunicación
	delete sck;
}
