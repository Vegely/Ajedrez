#pragma once

#include "Socket.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")



class Cliente
{
private:
    //Se encarga de la comunicación
    Socket* sck = nullptr;

    //Guarda la dirección ip del host
    std::string ipv4 = "";

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

