#pragma once

#undef UNICODE

#define WIN32_LEAN_AND_MEAN
constexpr int MAX_LONG_BUFF = 256;

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")


//Podría implemetar herencia para distinguir entre socket cliente y socket servidor
class Socket
{
private:
	addrinfo* red_info = nullptr; //Información de la red
	addrinfo* host_info = nullptr; //Almacena información del host

	SOCKET sck = INVALID_SOCKET; //Servidor: aceptar conexiones, Cliente: comunicación con servidor

	void creaSocket(const char* direccion);

public:
	Socket() {}; //Inicialización por defecto
	Socket(PCSTR direccion, int flags, int familia = AF_INET,
		int tipo_socket = SOCK_STREAM, int protocolo = IPPROTO_TCP);

	void vincula();
	void escucha();
	void aceptaConexion(Socket& sck_aux);
	void conectarAServidor();
	void envia(std::string s);
	std::string recibe();

	void desconecta();
};

void inicializaWinSock(); //Inicializa la librería WinSock

/*
* UNIT TEST
* Servidor/Cliente:
*
* Socket* s; //No lo creo si no voy a jugar en línea
*
* s=inicializarSocket(...);  //Pertenece al servidor --> Libera espacio para el socket
*	{
*		Socket* sck = new Socket;
*		sck->inicializa, crea, vincula...
*		return sck;
*	}
*/

