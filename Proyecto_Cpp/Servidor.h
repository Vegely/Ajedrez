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
	int error; //Comprobación de errores
	int error_desconexion; //Comprueba errores en la desconexión
	int error_inicializacion_ws; //Comprueba errores en la inicialización de WinSock
	int error_creacion; //Comprueba errores en la creación del socket del servidor
	int error_vinculacion; //Comprueba errores en la vinculación 
	int error_escucha; //Comprueba errores al escuchar
	WSADATA sck_info; //Contiene información para la implementación de sockets
	addrinfo red_info; //Información de la red
	addrinfo* host_info = NULL; //Almacena información del host
	SOCKET servidor_sck = INVALID_SOCKET; //Socket del servidor que atiende a conexiones de los clientes
	SOCKET cliente_socket = INVALID_SOCKET; //Socket a través del cual se realiza la conexión


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

