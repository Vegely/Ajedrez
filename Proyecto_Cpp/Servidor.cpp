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

#define DEFAULT_PORT "27015" //Puerto en el que se realiza la conexión por defecto


int servidor::recibirDeCliente(std::string& s) {
	return comunicacion_sck->recibe(s);
}

int servidor::enviarACliente(std::string s) {
	return comunicacion_sck->envia(s);
}

void servidor::conectarServidor() {
	sck = new Socket{ NULL,AI_PASSIVE };
	comunicacion_sck = new Socket;

	sck->vincula();
	sck->escucha();
	sck->aceptaConexion(*comunicacion_sck);

	//Solo hago una conexión, por lo que ya no es necesario atender más peticiones
	delete sck;
}

void servidor::desconectarServidor() {
	comunicacion_sck->desconecta();

	delete comunicacion_sck;
}