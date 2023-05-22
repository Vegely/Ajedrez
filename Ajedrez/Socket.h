#pragma once

#undef UNICODE

#define WIN32_LEAN_AND_MEAN
constexpr int MAX_LONG_BUFF = 256;
//Puerto en el que se realiza la conexi�n por defecto
constexpr const char* PUERTO_PREDETERMINADO = "42069";

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

#pragma comment (lib, "Ws2_32.lib")

class Socket
{
private:
	//Almacena par�metros de la red
	addrinfo* red_info = nullptr;
	//Almacena informaci�n de la conexi�n que acepta el host
	addrinfo* host_info = nullptr;
	//Servidor: comunicaci�n y acepar peticiones de conexi�n
	//Cliente: comunicaci�n
	SOCKET sck = INVALID_SOCKET;

public:
	//Inicializaci�n por defecto
	Socket() {};
	//Inicializaci�n
	//@param int flags: servidor --> AI_PASSIVE, cliente --> NULL
	//@param int familia: familia del protocolo (AF_INET para familia IPv4)
	//@param int tipo_socket: tipo de socket a usar (SOCK_STREAM por defecto)
	//@param int protocolo: protocolo usado (IPPROTO_TCP para TCP)
	Socket(int flags, int familia = AF_INET,
		int tipo_socket = SOCK_STREAM, int protocolo = IPPROTO_TCP);

	//No defino destructor porque no existe posibilidad de copia/asignaci�n (no hay conflicto de recursos)
	//Adem�s, las estructuras de datos dentro de Socket son complejas y no est�n orientadas a objetos (no tienen destructor),
	//por lo que es mejor dejar al SO que se encargue de la gesti�n de dicha memoria.

	//No se pueden copiar ni asignar los sockets
	Socket(const Socket&) = delete;
	Socket& operator= (const Socket&) = delete;

	//Crea un socket asociado a una direcci�n IP
	//@param const char* direccion: direcci�n IP del host (nullptr si lo usamos desde el servidor)
	void creaSocket(const char* direccion);
	//Vincula el programa con el socket creado
	void vincula();
	//Atiende peticiones de conexi�n del cliente
	void escucha();
	//Acepta peticiones de conexi�n del cliente
	//Cierra el socket que acepta las conexiones (solo hay 1 conexi�n) y crea un socket de comunicaci�n
	//@param Socket& sck_aux: socket para la comunicaci�n con el cliente
	void aceptaConexion(Socket& sck_aux);
	//Conecta el cliente con el servidor
	void conectarAServidor();
	//Env�a una cadena de caracteres al cliente/servidor
	//@param std::string s: cadena de caracteres a enviar
	//@return  N�mero de bytes enviados
	int envia(std::string s);
	//Recibe una caddena de caracteres del cliente/servidor
	//@param std::string& s: cadena de caracteres recibida
	//@return N�mero de bytes recibidos
	int recibe(std::string& s);

	//Desconecta el cliente/servidor: termina la conexi�n y cierra los sockets
	void desconecta();
};

//Inicializa la librer�a WinSock
void inicializaWinSock();



