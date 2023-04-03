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


#define DEFAULT_PORT "27015"

class cliente
{
private:
    Socket* sck = nullptr; //Se encarga de la comunicación

public:
    int enviarAServidor(std::string s);
    int recibirDeServidor(std::string& s);
    void conectarCliente();
    void desconectarCliente();
};

