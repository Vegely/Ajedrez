#include "Socket.h"

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


Socket::Socket(const char* direccion, int flags, int familia,
	int tipo_socket, int protocolo) {
	//Inicializamos WinSock
	inicializaWinSock(); //Fuera del constructor, en el main

	red_info = new addrinfo;
	//Pone el bloque de memoria donde est� red_info a 0
	ZeroMemory(red_info, sizeof(*red_info));
	red_info->ai_family = familia;
	red_info->ai_socktype = tipo_socket;
	red_info->ai_protocol = protocolo;
	red_info->ai_flags = flags;

	creaSocket(direccion);
}


void Socket::creaSocket(const char* direccion) {
	int error_creacion;

	//Obtiene informaci�n sobre la direcciones registradas en el ordenador 
	error_creacion = getaddrinfo(direccion, DEFAULT_PORT, red_info, &host_info);

	//Comprobaci�n de errores
	if (error_creacion != 0) {
		printf("getaddrinfo failed with error: %d\n", error_creacion);
		WSACleanup();
	}

	//Creo un socket en el servidor con la informaci�n de conexi�n del host
	//Este socket se encargar� de aceptar peticiones de conexi�n
	sck = socket(host_info->ai_family, host_info->ai_socktype, host_info->ai_protocol);

	//Comprobaci�n de errores
	if (sck == INVALID_SOCKET) {
		std::cout << "Error en la creacion del socket: " << WSAGetLastError();
		freeaddrinfo(host_info);
	}
}

void Socket::vincula() {
	int error_vinculacion;

	//Asocia nuestro programa con el socket creado
	error_vinculacion = bind(sck, host_info->ai_addr, (int)(host_info->ai_addrlen));

	//Comprobaci�n de errores
	if (error_vinculacion == SOCKET_ERROR) {
		std::cout << "Error en la vinculacion: " << WSAGetLastError();
		freeaddrinfo(host_info);
		closesocket(sck);
		WSACleanup();
	}

	//Ya no hace falta la informaci�n sobre la conexi�n (el socket ya est� creado y vinculado)
	freeaddrinfo(host_info); //???
}

void Socket::escucha() {
	int error_escucha;

	//Avisamos al SO de que comience a atender conexiones
	error_escucha = listen(sck, SOMAXCONN);

	//Comprobaci�n de errores
	if (error_escucha == SOCKET_ERROR) {
		printf("Listen failed with error: %ld\n", WSAGetLastError());
		closesocket(sck);
		WSACleanup();
	}
}

void Socket::aceptaConexion(Socket& sck_aux) {
	//Indicamos al SO que acepte conexiones de clientes si las hay
	//Devuelve un socket a trav�s del cual se va a realizar la conexi�n
	//Si se tratara con varios clientes, se mandar�a este socket a un hilo diferente
	sck_aux.sck = accept(sck, nullptr, nullptr);

	//Comprobaci�n de errores
	if (sck_aux.sck == INVALID_SOCKET) {
		printf("accept failed with error: %d\n", WSAGetLastError());
		closesocket(sck);
		WSACleanup();
	}

	//Solo nos comunicamos con un cliente, no es necesario aceptar m�s peticiones
	closesocket(sck);
}

void Socket::conectarAServidor() {
	int error_conexion;

	//Establece una conexi�n entre los sockets del cliente y servidor 
	//�Ojo! "host_info" es una lista enlazada, habr�a que iterar para realizar la conexi�n
	error_conexion = connect(sck, host_info->ai_addr, (int)host_info->ai_addrlen);

	//Comprobaci�n de errores
	if (error_conexion == SOCKET_ERROR) {
		closesocket(sck);
		printf("Unable to connect to server!\n");
		WSACleanup();
	}

	//Ya no es necesario host_info
	freeaddrinfo(host_info);
}

void Socket::envia(std::string s) {
	int bytes_enviados;

	//Env�a una cadena de caracteres (const char*)
	bytes_enviados = send(sck, s.c_str(), s.length(), 0);

	if (bytes_enviados == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(sck);
		WSACleanup();
	}
}

std::string Socket::recibe() {
	int bytes_recibidos;
	char buffer[MAX_LONG_BUFF];

	//Recibe informaci�n del cliente y devuelve n�mero de bytes recibidos
	//Longitud del mensaje limitada (gusanos)
	bytes_recibidos = recv(sck, buffer, (int)sizeof(buffer), 0);

	//Si no se producen errores, sigo trabajando
	if (bytes_recibidos > 0) {
		for (int i = 0; i < bytes_recibidos; i++)
			std::cout << buffer[i];
		std::string s(buffer);
		return s;
	}
	else
		return "";
}

void Socket::desconecta() {
	int error_desconexion;

	//Cierra la conexi�n con el servidor
	error_desconexion = shutdown(sck, SD_SEND);

	//Comprobaci�n de errores
	if (error_desconexion == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(sck);
		WSACleanup();

	}

	//Cierra el socket del cliente
	closesocket(sck);
	WSACleanup();
}

void inicializaWinSock() {
	WSADATA sck_info; //Contiene informaci�n para la implementaci�n de sockets
	int error_inicializacion_ws;

	error_inicializacion_ws = WSAStartup(MAKEWORD(2, 2), &sck_info); //Argumentos: (versi�n, puntero a estructura WSADATA)

	//�xito: 0 , Fracaso: c�digo de error (https://learn.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsastartup)
	if (error_inicializacion_ws != 0)
		std::cout << "Error en la inicializacion de la libreria: " << error_inicializacion_ws << std::endl;
}