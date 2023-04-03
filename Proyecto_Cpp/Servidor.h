#pragma once

#include "Socket.h"
#include <fstream>
#include <sstream>

class Servidor
{
private:
	//Atiende peticiones de conexi�n
	Socket* sck = nullptr;
	//Se encarga de la comunicaci�n
	Socket* comunicacion_sck = nullptr;
	//Almacena las posibles direcciones IP del equipo
	std::string direccion_ip;

public:
	//Constructor: 
	// - Inicializaci�n por defecto
	// - Inicializaci�n WinSock
	Servidor() { inicializaWinSock(); };

	//No hace falta destructor (conflictos de copia/asignaci�n eliminados), lo gestiona el SO

	//Eliminamos posibles conflictos de copia/asignaci�n
	Servidor(const Servidor&) = delete;
	Servidor& operator= (const Servidor&) = delete;

	//Conecta el servidor
	void conectarServidor();
	//Desconecta el servidor
	void desconectarServidor();

	//Recibe una cadena de caracteres del cliente
	//@param std::string s: cadena recibida
	//@return N�mero de bytes recibidos
	int recibirDeCliente(std::string& s);
	//Manda una cadena de caracteres al cliente
	//@param std::string s: cadena a enviar
	//@return N�mero de bytes enviados
	int enviarACliente(std::string s);


};

