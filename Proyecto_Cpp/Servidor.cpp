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

#define DEFAULT_PORT "27015" //Puerto en el que se realiza la conexi�n por defecto

void servidor::inicializa() {
	error_inicializacion_ws = WSAStartup(MAKEWORD(2, 2), &sck_info); //Argumentos: (versi�n, puntero a estructura WSADATA)

	//�xito: 0 , Fracaso: c�digo de error (https://learn.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsastartup)
	if (error_inicializacion_ws != 0)
		std::cout << "Error en la inicializacion de la libreria: " << error_inicializacion_ws << std::endl;
}

void servidor::creaSocket() {
	ZeroMemory(&red_info, sizeof(red_info));
	red_info.ai_family = AF_INET; //IPv4
	red_info.ai_socktype = SOCK_STREAM;//Socket de tipo stream
	red_info.ai_protocol = IPPROTO_TCP;//Protocolo TCP
	red_info.ai_flags = AI_PASSIVE; //Indica que vamos a vincular nuestro programa con el socket mediante bind()

	//Indico el tipo de conexi�n ("red_info") y recibo el tipo de conexi�n que acepta el servidor ("host_info")
	//�xito: 0, Fracaso: c�digo de error (https://learn.microsoft.com/en-us/windows/win32/winsock/creating-a-socket-for-the-server)
	error_creacion = getaddrinfo(NULL, DEFAULT_PORT, &red_info, &host_info);

	//Comprobaci�n de errores
	if (error_creacion != 0) {
		printf("getaddrinfo failed with error: %d\n", error_creacion);
		WSACleanup();
	}

	//Creo un socket en el servidor con la informaci�n de conexi�n del host
	//Este socket se encargar� de aceptar peticiones de conexi�n
	servidor_sck = socket(host_info->ai_family, host_info->ai_socktype, host_info->ai_protocol);

	//Comprobaci�n de errores
	if (servidor_sck == INVALID_SOCKET) {
		std::cout << "Error en la creacion del socket: " << WSAGetLastError();
		freeaddrinfo(host_info);
	}
}

void servidor::vincula() {
	//Asocia nuestro programa con el socket creado
	error_vinculacion = bind(servidor_sck, host_info->ai_addr, (int)(host_info->ai_addrlen));

	//Comprobaci�n de errores
	if (error_vinculacion == SOCKET_ERROR) {
		std::cout << "Error en la vinculacion: " << WSAGetLastError();
		freeaddrinfo(host_info);
		closesocket(servidor_sck);
		WSACleanup();
	}

	//Ya no hace falta la informaci�n sobre la conexi�n (el socket ya est� creado y vinculado)
	freeaddrinfo(host_info);
}

void servidor::escucha() {
	//Avisamos al SO de que comience a atender conexiones
	error_escucha = listen(servidor_sck, SOMAXCONN);

	//Comprobaci�n de errores
	if (error_escucha == SOCKET_ERROR) {
		printf("Listen failed with error: %ld\n", WSAGetLastError());
		closesocket(servidor_sck);
		WSACleanup();
	}
}

void servidor::aceptaConexion() {
	//Indicamos al SO que acepte conexiones de clientes si las hay
	//Devuelve un socket a trav�s del cual se va a realizar la conexi�n
	//Si se tratara con varios clientes, se mandar�a este socket a un hilo diferente
	cliente_socket = accept(servidor_sck, nullptr, nullptr);

	//Comprobaci�n de errores
	if (cliente_socket == INVALID_SOCKET) {
		printf("accept failed with error: %d\n", WSAGetLastError());
		closesocket(servidor_sck);
		WSACleanup();
	}

	//Solo nos comunicamos con un cliente, no es necesario aceptar m�s peticiones
	closesocket(servidor_sck);
}

void servidor::recibe() {
	do {
		//Recibe informaci�n del cliente
		//Longitud del mensaje limitada (gusanos)
		error = recv(cliente_socket, recvbuf, recvbuflen, 0);

		//Si no se producen errores, sigo trabajando
		if (error > 0) {
			printf("Bytes received: %d\n", error);

			for (int i = 0; i < error; i++)
				std::cout << recvbuf[i];
		}
	} while (error > 0);
}

void servidor::desconecta() {
	//Termina la conexi�n en la que se produce el intercambio de informaci�n
	error_desconexion = shutdown(cliente_socket, SD_SEND);

	//Comprobaci�n de errores
	if (error_desconexion == SOCKET_ERROR) {
		std::cout << "shutdown failed: " << WSAGetLastError() << std::endl;
		closesocket(cliente_socket);
		WSACleanup();
	}

	//Cerramos socket
	closesocket(cliente_socket);
	WSACleanup();
}