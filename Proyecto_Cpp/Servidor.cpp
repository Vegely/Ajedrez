#include "servidor.h"

int Servidor::recibirDeCliente(std::string& s) {
	return comunicacion_sck->recibe(s);
}

int Servidor::enviarACliente(std::string s) {
	return comunicacion_sck->envia(s);
}

void Servidor::conectarServidor() {
	//NULL: almacena en host_info todas las direcciones de red almacenadas en el equipo 
	//AI_PASSIVE: indica que vamos a hacer una llamada a bind()
	sck = new Socket{ AI_PASSIVE };
	comunicacion_sck = new Socket;

	//Obtiene una lista con direcciones IP
	sck->listaIp(direccion_ip);
	std::cout << direccion_ip;

	//Creaci�n de la conexi�n
	sck->creaSocket(NULL);
	sck->vincula();
	sck->escucha();
	sck->aceptaConexion(*comunicacion_sck);

	//Solo se hace una conexi�n: no es necesario aceptar m�s conexiones
	delete sck;
}

void Servidor::desconectarServidor() {
	comunicacion_sck->desconecta();

	//Conexi�n cerrada: elimina el socket para la comunicaci�n
	delete comunicacion_sck;
}