#ifndef _CLIENTE__H_
#define _CLIENTE__H_

#include "Socket.h"
#include "ElementoRed.h"

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
    std::string ipv4 = ""; // Para jugar en el mismo ordenador: 127.0.0.1
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
    void setIp(std::string ip) { ipv4 = ip; }
};

#endif // !_CLIENTE__H_