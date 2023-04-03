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



class Servidor
{
private:
	//Atiende peticiones de conexión
	Socket* sck = nullptr;
	//Se encarga de la comunicación
	Socket* comunicacion_sck = nullptr;

public:
	//Constructor: 
	// - Inicialización por defecto
	// - Inicialización WinSock
	Servidor() { inicializaWinSock(); };

	//No hace falta destructor (conflictos de copia/asignación eliminados), lo gestiona el SO

	//Eliminamos posibles conflictos de copia/asignación
	Servidor(const Servidor&) = delete;
	Servidor& operator= (const Servidor&) = delete;

	//Conecta el servidor
	void conectarServidor();
	//Desconecta el servidor
	void desconectarServidor();

	//Recibe una cadena de caracteres del cliente
	//@param std::string s: cadena recibida
	//@return Número de bytes recibidos
	int recibirDeCliente(std::string& s);
	//Manda una cadena de caracteres al cliente
	//@param std::string s: cadena a enviar
	//@return Número de bytes enviados
	int enviarACliente(std::string s);


};

