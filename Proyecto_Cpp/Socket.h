#pragma once

#undef UNICODE

#define WIN32_LEAN_AND_MEAN
constexpr int MAX_LONG_BUFF = 256;
//Puerto en el que se realiza la conexión por defecto
constexpr const char* PUERTO_PREDETERMINADO = "42069";

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

#pragma comment (lib, "Ws2_32.lib")

class Socket
{
private:
	//Almacena parámetros de la red
	addrinfo* red_info = nullptr;
	//Almacena información de la conexión que acepta el host
	addrinfo* host_info = nullptr;
	//Servidor: comunicación y acepar peticiones de conexión
	//Cliente: comunicación
	SOCKET sck = INVALID_SOCKET;

public:
	//Inicialización por defecto
	Socket() {};
	//Inicialización
	//@param int flags: servidor --> AI_PASSIVE, cliente --> NULL
	//@param int familia: familia del protocolo (AF_INET para familia IPv4)
	//@param int tipo_socket: tipo de socket a usar (SOCK_STREAM por defecto)
	//@param int protocolo: protocolo usado (IPPROTO_TCP para TCP)
	Socket(int flags, int familia = AF_INET,
		int tipo_socket = SOCK_STREAM, int protocolo = IPPROTO_TCP);

	//No defino destructor porque no existe posibilidad de copia/asignación (no hay conflicto de recursos)
	//Además, las estructuras de datos dentro de Socket son complejas y no están orientadas a objetos (no tienen destructor),
	//por lo que es mejor dejar al SO que se encargue de la gestión de dicha memoria.

	//No se pueden copiar ni asignar los sockets
	Socket(const Socket&) = delete;
	Socket& operator= (const Socket&) = delete;

	//Crea un socket asociado a una dirección IP
	//@param const char* direccion: dirección IP del host (nullptr si lo usamos desde el servidor)
	void creaSocket(const char* direccion);
	//Vincula el programa con el socket creado
	void vincula();
	//Atiende peticiones de conexión del cliente
	void escucha();
	//Acepta peticiones de conexión del cliente
	//Cierra el socket que acepta las conexiones (solo hay 1 conexión) y crea un socket de comunicación
	//@param Socket& sck_aux: socket para la comunicación con el cliente
	void aceptaConexion(Socket& sck_aux);
	//Conecta el cliente con el servidor
	void conectarAServidor();
	//Envía una cadena de caracteres al cliente/servidor
	//@param std::string s: cadena de caracteres a enviar
	//@return  Número de bytes enviados
	int envia(std::string s);
	//Recibe una caddena de caracteres del cliente/servidor
	//@param std::string& s: cadena de caracteres recibida
	//@return Número de bytes recibidos
	int recibe(std::string& s);

	//Desconecta el cliente/servidor: termina la conexión y cierra los sockets
	void desconecta();
};

//Inicializa la librería WinSock
void inicializaWinSock();



