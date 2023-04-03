#include "cliente.h"

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "Socket.h"


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")





int Cliente::enviarAServidor(std::string s) {
	return sck->envia(s);
}

int Cliente::recibirDeServidor(std::string& s) {
	return sck->recibe(s);
}

void Cliente::conectarCliente() {
	//IP del equipo al que se conecta ("127.0.0.1" --> localhost)
	//NULL: no se especifican opciones en host_info
	sck = new Socket{ "127.0.0.1",NULL };

	sck->conectarAServidor();
}

void Cliente::desconectarCliente() {
	sck->desconecta();

	//Conexión cerrada: elimina el socket para la comunicación
	delete sck;
}
