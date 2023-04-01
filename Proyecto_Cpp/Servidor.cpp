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

	res = bind(listen_socket, this->res->ai_addr, static_cast<int>(this->res->ai_addrlen));

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
	client_socket = accept(listen_socket, NULL, NULL);
	if (client_socket == INVALID_SOCKET) {
		printf("accept failed: %d\n", WSAGetLastError());
		closesocket(listen_socket);
		WSACleanup();
	}
	closesocket(listen_socket);
}