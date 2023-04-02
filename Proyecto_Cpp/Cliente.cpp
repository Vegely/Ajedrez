#include "cliente.h"

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"


void cliente::inicializa() {
	error_inicializacion_ws = WSAStartup(MAKEWORD(2, 2), &sck_info); //Argumentos: (versión, puntero a estructura WSADATA)

	//Éxito: 0 , Fracaso: código de error (https://learn.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsastartup)
	if (error_inicializacion_ws != 0)
		std::cout << "Error en la inicializacion de la libreria: " << error_inicializacion_ws << std::endl;
}

void cliente::creaSocket(int argc, char** argv) {

	if (argc != 2) {
		printf("usage: %s server-name\n", argv[0]);

	}

	//Pone el bloque de memoria donde está red_info a 0
	ZeroMemory(&red_info, sizeof(red_info));
	red_info.ai_family = AF_INET; //IPv4
	red_info.ai_socktype = SOCK_STREAM;//Socket de tipo stream
	red_info.ai_protocol = IPPROTO_TCP;//Protocolo TCP

	//Pide información sobre el tipo de conexión en el servidor
	error_creacion = getaddrinfo(argv[1], DEFAULT_PORT, &red_info, &host_info);

	//Comprobación de errores
	if (error_creacion != 0) {
		printf("getaddrinfo failed with error: %d\n", error_creacion);
		WSACleanup();
	}

	//Crea un socket en el cliente, a través del cual se realiza la conexión
	//¡Ojo! "host_info" es una lista enlazada, habría que iterar para realizar la conexión
	cliente_socket = socket(host_info->ai_family, host_info->ai_socktype, host_info->ai_protocol);

	//Comprobación errores
	if (cliente_socket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		WSACleanup();
	}
}

void cliente::conecta() {
	//Establece una conexión entre los sockets del cliente y servidor 
	//¡Ojo! "host_info" es una lista enlazada, habría que iterar para realizar la conexión
	error_conexion = connect(cliente_socket, host_info->ai_addr, (int)host_info->ai_addrlen);

	//Comprobación de errores
	if (error_conexion == SOCKET_ERROR) {
		closesocket(cliente_socket);
		printf("Unable to connect to server!\n");
		WSACleanup();
	}

	//Ya no es necesario host_info
	freeaddrinfo(host_info);

}

void cliente::envia(std::string s) {
	iResult = send(cliente_socket, s.c_str(), s.length(), 0);

	if (iResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(cliente_socket);
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

}

void cliente::desconecta() {
	iResult = shutdown(cliente_socket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(cliente_socket);
		WSACleanup();

	}
}

void cliente::apaga() {
	closesocket(cliente_socket);
	WSACleanup();
}

