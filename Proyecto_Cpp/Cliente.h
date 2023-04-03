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
    //Se encarga de la comunicación
    Socket* sck = nullptr;

public:
    //Constructor:
    // - Inicialización por defecto
    // - Inicialización Winsock
    Cliente() { inicializaWinSock(); };

    //No hace falta destructor (conflictos de copia/asignación eliminados), lo gestiona el SO

    //Eliminamos posibles conflictos de copia/asignación
    Cliente(const Cliente&) = delete;
    Cliente& operator= (const Cliente&) = delete;

    //Conecta el cliente
    void conectarCliente();
    //Desconecta el cliente
    void desconectarCliente();

    //Envía una cadena de caracteres al servidor
    //@param std::string s: cadena a enviar
    //@return Número de bytes enviados
    int enviarAServidor(std::string s);
    //Recibe una cadena de caracteres del servidor
    //@param std::string& s: cadena recibida
    //@return Número de bytes recibidos
    int recibirDeServidor(std::string& s);

};

