#pragma once
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

class cliente
{
private:
    int argc;
    char** argv;

    addrinfo* result = nullptr;
    addrinfo* ptr = nullptr;
    addrinfo hints;

    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;
    char recvbuf[DEFAULT_BUFLEN];
    const char* sendbuf = "hola mundo";


    SOCKET ConnectSocket = INVALID_SOCKET;

public:
    void creaSocket();
    void conecta();
    void envia();
    void recibe();
};

