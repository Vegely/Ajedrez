#ifndef _CLIENTE__H_
#define _CLIENTE__H_

#include "Socket.h"
#include "ElementoRed.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

class Cliente : public ElementoRed
{
private:
    //Se encarga de la comunicaci�n
    Socket* sck = nullptr;

    //Guarda la direcci�n ip del host
    std::string ipv4 = "127.0.0.1";//"192.168.0.21";
public:
    //Constructor:
    // - Inicializaci�n por defecto
    // - Inicializaci�n Winsock
    Cliente() { };

    //No hace falta destructor (conflictos de copia/asignaci�n eliminados), lo gestiona el SO

    //Eliminamos posibles conflictos de copia/asignaci�n
    Cliente(const Cliente&) = delete;
    Cliente& operator= (const Cliente&) = delete;

    void inicializa() { inicializaWinSock(); };
    //Conecta el cliente
    bool conectar();
    //Desconecta el cliente
    void desconectar();

    //Env�a una cadena de caracteres al servidor
    //@param std::string s: cadena a enviar
    //@return N�mero de bytes enviados
    int enviar(std::string s) const;
    //Recibe una cadena de caracteres del servidor
    //@param std::string& s: cadena recibida
    //@return N�mero de bytes recibidos
    int recibir(std::string& s) const;

    std::string getIp() { return ipv4; };
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

#endif // !_CLIENTE__H_