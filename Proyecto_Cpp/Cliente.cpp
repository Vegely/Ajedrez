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



#define DEFAULT_PORT "27015"

/*
void cliente::enviarInfo(std::string s) {
	//Envía una cadena de caracteres (const char*) al servidor
	bytes_enviados = send(sck->getSck(), s.c_str(), s.length(), 0);

	if (bytes_enviados == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(sck->getSck());
		WSACleanup();
	}
}


void cliente::recibe() {
	do {

		iResult = recv(cliente_socket, recvbuf, recvbuflen, 0);
		if (iResult > 0)
			printf("Bytes received: %d\n", iResult);
		else if (iResult == 0)
			printf("Connection closed\n");
		else
			printf("recv failed with error: %d\n", WSAGetLastError());

	} while (iResult > 0);

}*/

void cliente::enviarAServidor(std::string s) {
	sck->envia(s);
}
std::string cliente::recibirDeServidor() {
	return sck->recibe() + "\0";
}

void cliente::conectarCliente() {
	sck = new Socket{ "127.0.0.1",NULL };

	sck->conectarAServidor();
}

void cliente::desconectarCliente() {
	sck->desconecta();

	delete sck;
}
