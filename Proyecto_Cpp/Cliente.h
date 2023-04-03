#pragma once
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "Socket.h"


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define PUERTO_PREDETERMINADO "27015"

class Cliente
{
private:
    //Se encarga de la comunicaci�n
    Socket* sck = nullptr;

public:
    //Constructor:
    // - Inicializaci�n por defecto
    // - Inicializaci�n Winsock
    Cliente() { inicializaWinSock(); };

    //No hace falta destructor (conflictos de copia/asignaci�n eliminados), lo gestiona el SO

    //Eliminamos posibles conflictos de copia/asignaci�n
    Cliente(const Cliente&) = delete;
    Cliente& operator= (const Cliente&) = delete;

    //Conecta el cliente
    void conectarCliente();
    //Desconecta el cliente
    void desconectarCliente();

    //Env�a una cadena de caracteres al servidor
    //@param std::string s: cadena a enviar
    //@return N�mero de bytes enviados
    int enviarAServidor(std::string s);
    //Recibe una cadena de caracteres del servidor
    //@param std::string& s: cadena recibida
    //@return N�mero de bytes recibidos
    int recibirDeServidor(std::string& s);

};

