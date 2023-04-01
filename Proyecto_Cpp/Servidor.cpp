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

void servidor::inicializa() {
	int res; //Éxito: 0 , Fracaso: código de error (https://learn.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsastartup)

	res = WSAStartup(MAKEWORD(2, 2), &sck_info); //Argumentos: (versión, puntero a estructura WSADATA)

	if (res != 0)
		std::cout << "Error de inicializacion: " << res;
}

void servidor::creaSocket() {
	int res;//Éxito: 0, Fracaso: código de error (https://learn.microsoft.com/en-us/windows/win32/winsock/creating-a-socket-for-the-server)

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET; //IPv4
	hints.ai_socktype = SOCK_STREAM;//Socket de tipo stream
	hints.ai_protocol = IPPROTO_TCP;//Protocolo TCP
	hints.ai_flags = AI_PASSIVE; //Indica que vamos a vincular nuestro programa con el socket mediante bind()

	res = getaddrinfo(NULL, DEFAULT_PORT, &hints, &this->res);

	listen_socket = socket(this->res->ai_family, this->res->ai_socktype, this->res->ai_protocol);

	if (listen_socket == INVALID_SOCKET) {
		std::cout << "Error en la creacion del socket: " << WSAGetLastError();
		freeaddrinfo(this->res);
	}

}

void servidor::vincula() {
	int res;

	res = bind(listen_socket, this->res->ai_addr, (int)(this->res->ai_addrlen));

	if (res == SOCKET_ERROR) {
		std::cout << "Error en la vinculacion: " << WSAGetLastError();
		freeaddrinfo(this->res);
		closesocket(listen_socket);
		WSACleanup();
	}
	freeaddrinfo(this->res);
}

void servidor::escucha() {
	if (listen(listen_socket, SOMAXCONN) == SOCKET_ERROR) {
		printf("Listen failed with error: %ld\n", WSAGetLastError());
		closesocket(listen_socket);
		WSACleanup();
	}
}

void servidor::aceptaConexion() {
	client_socket = accept(listen_socket, nullptr, nullptr);
	if (client_socket == INVALID_SOCKET) {
		printf("accept failed with error: %d\n", WSAGetLastError());
		closesocket(listen_socket);
		WSACleanup();
	}
	closesocket(listen_socket);
}

void servidor::recibe() {
	do {

		iResult = recv(client_socket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			printf("Bytes received: %d\n", iResult);

			// Echo the buffer back to the sender
			iSendResult = send(client_socket, recvbuf, iResult, 0);
			if (iSendResult == SOCKET_ERROR) {
				printf("send failed: %d\n", WSAGetLastError());
				closesocket(client_socket);
				WSACleanup();
			}
			printf("Bytes sent: %d\n", iSendResult);
		}
		else if (iResult == 0)
			printf("Connection closing...\n");
		else {
			printf("recv failed: %d\n", WSAGetLastError());
			closesocket(client_socket);
			WSACleanup();
		}

	} while (iResult > 0);
}

void servidor::desconecta() {
	iResult = shutdown(client_socket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed: %d\n", WSAGetLastError());
		closesocket(client_socket);
		WSACleanup();
	}
	closesocket(client_socket);
	WSACleanup();
}