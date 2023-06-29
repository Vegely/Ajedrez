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
    //Se encarga de la comunicación
    Socket* sck = nullptr;

    //Guarda la dirección ip del host
    std::string ipv4 = ""; // Para jugar en el mismo ordenador: 127.0.0.1
public:
    //Constructor:
    // - Inicialización por defecto
    // - Inicialización Winsock
    Cliente() { };

    //No hace falta destructor (conflictos de copia/asignación eliminados), lo gestiona el SO

    //Eliminamos posibles conflictos de copia/asignación
    Cliente(const Cliente&) = delete;
    Cliente& operator= (const Cliente&) = delete;

    void inicializa() { inicializaWinSock(); };
    //Conecta el cliente
    bool conectar();
    //Desconecta el cliente
    void desconectar();

    //Envía una cadena de caracteres al servidor
    //@param std::string s: cadena a enviar
    //@return Número de bytes enviados
    int enviar(std::string s) const;
    //Recibe una cadena de caracteres del servidor
    //@param std::string& s: cadena recibida
    //@return Número de bytes recibidos
    int recibir(std::string& s) const;

    std::string getIp() { return ipv4; };
    void setIp(std::string ip) { ipv4 = ip; }
};

#endif // !_CLIENTE__H_