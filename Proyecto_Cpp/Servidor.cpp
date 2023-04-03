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

	//Creación de la conexión
	sck->creaSocket(NULL);
	sck->vincula();
	sck->escucha();
	sck->aceptaConexion(*comunicacion_sck);

	//Solo se hace una conexión: no es necesario aceptar más conexiones
	delete sck;
}

void Servidor::desconectarServidor() {
	comunicacion_sck->desconecta();

	//Conexión cerrada: elimina el socket para la comunicación
	delete comunicacion_sck;
}