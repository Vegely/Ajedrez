#include "servidor.h"

#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")




int Servidor::recibirDeCliente(std::string& s) {
	return comunicacion_sck->recibe(s);
}

int Servidor::enviarACliente(std::string s) {
	return comunicacion_sck->envia(s);
}

void Servidor::conectarServidor() {
	//NULL: almacena en host_info todas las direcciones de red almacenadas en el equipo 
	//AI_PASSIVE: indica que vamos a hacer una llamada a bind()
	sck = new Socket{ NULL,AI_PASSIVE };
	comunicacion_sck = new Socket;

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