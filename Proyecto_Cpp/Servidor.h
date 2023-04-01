#pragma once

#undef UNICODE

#define WIN32_LEAN_AND_MEAN
#define DEFAULT_BUFLEN 512

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")



class servidor
{
private:


public:
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;
	int iResult, iSendResult;

	WSADATA sck_info;
	addrinfo* res = NULL;
	addrinfo* ptr = NULL;
	addrinfo hints;
	SOCKET listen_socket = INVALID_SOCKET;
	SOCKET client_socket = INVALID_SOCKET;

	void inicializa();
	void creaSocket();
	void vincula();
	void escucha();
	void aceptaConexion();
	void recibe();
	void desconecta();
};

