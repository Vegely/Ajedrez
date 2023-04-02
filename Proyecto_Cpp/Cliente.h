#pragma once
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

class cliente
{
private:
    int error_inicializacion_ws; //Comprueba errores en la inicialización de WinSock
    int error_creacion; //Comprueba errores en la creación del socket del servidor
    int error_conexion; //Comprueba errores en la conexión
    int error_desconexion; //Comprueba errores en la desconexión
    WSADATA sck_info;
    SOCKET cliente_socket = INVALID_SOCKET;
    addrinfo* host_info = NULL,
        red_info;
    const char* sendbuf = "hola mundo en red";
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;

public:
    void inicializa();
    void creaSocket(int argc, char** argv);
    void conecta();
    void envia(std::string s);
    void recibe();
    void desconecta();
    void apaga();

    int do_stuff(int argc, char** argv);
};

