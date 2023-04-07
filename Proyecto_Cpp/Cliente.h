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
    //Se encarga de la comunicaci�n
    Socket* sck = nullptr;

    //Guarda la direcci�n ip del host
    std::string ipv4 = "192.168.0.21";

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

// Main (poner la direcci�n ip que aparece en la pantalla del servidor en el campo ipv4 del cliente)

/*

void cambiarTurno(bool& tnegras, bool& tblancas) {
    tnegras = !tnegras;
    tblancas = !tblancas;
}

    //Servidor: negras
    //Cliente: blancas
    std::string cenviar = "", crecibir = "";
    bool tblancas = 0, tnegras = 1;
    bool salir = 0, cambiar = 0;


    Cliente c;

    c.conectarCliente();

    while (!salir) {
        if (tnegras) {
            if (c.recibirDeServidor(crecibir) > 0) {
                std::cout << crecibir << std::endl;
                crecibir = "";
            }
            cambiarTurno(tnegras, tblancas);
        }
        else if (tblancas) {
            cenviar = "";
            std::getline(std::cin, cenviar);
            c.enviarAServidor(cenviar);
            cambiarTurno(tnegras, tblancas);
        }

    }

    c.desconectarCliente();

*/