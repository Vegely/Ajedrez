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
	int error; //Comprobaci�n de errores
	int error_desconexion; //Comprueba errores en la desconexi�n
	int error_inicializacion_ws; //Comprueba errores en la inicializaci�n de WinSock
	int error_creacion; //Comprueba errores en la creaci�n del socket del servidor
	int error_vinculacion; //Comprueba errores en la vinculaci�n 
	int error_escucha; //Comprueba errores al escuchar
	WSADATA sck_info; //Contiene informaci�n para la implementaci�n de sockets
	addrinfo red_info; //Informaci�n de la red
	addrinfo* host_info = NULL; //Almacena informaci�n del host
	SOCKET servidor_sck = INVALID_SOCKET; //Socket del servidor que atiende a conexiones de los clientes
	SOCKET cliente_socket = INVALID_SOCKET; //Socket a trav�s del cual se realiza la conexi�n


public:
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	void inicializa();
	void creaSocket();
	void vincula();
	void escucha();
	void aceptaConexion();
	void recibe();
	void desconecta();
};

