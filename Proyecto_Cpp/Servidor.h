#pragma once

#undef UNICODE

#define WIN32_LEAN_AND_MEAN




#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Socket.h"
// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")



class servidor
{
private:
	Socket* sck = nullptr; //Atiende peticiones de conexión
	Socket* comunicacion_sck = nullptr; //Se encarga de la comunicación

public:

	std::string recibirDeCliente();
	void enviarACliente(std::string s);

	void conectarServidor();
	void desconectarServidor();
};

