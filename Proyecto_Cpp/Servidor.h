#pragma once

#include "Socket.h"
#include <fstream>
#include <sstream>

class Servidor
{
private:
	//Atiende peticiones de conexión
	Socket* sck = nullptr;
	//Se encarga de la comunicación
	Socket* comunicacion_sck = nullptr;
	//Almacena las posibles direcciones IP del equipo
	std::string direccion_ip;

public:
	//Constructor: 
	// - Inicialización por defecto
	// - Inicialización WinSock
	Servidor() { inicializaWinSock(); };

	//No hace falta destructor (conflictos de copia/asignación eliminados), lo gestiona el SO

	//Eliminamos posibles conflictos de copia/asignación
	Servidor(const Servidor&) = delete;
	Servidor& operator= (const Servidor&) = delete;

	//Conecta el servidor
	void conectarServidor();
	//Desconecta el servidor
	void desconectarServidor();

	//Recibe una cadena de caracteres del cliente
	//@param std::string s: cadena recibida
	//@return Número de bytes recibidos
	int recibirDeCliente(std::string& s);
	//Manda una cadena de caracteres al cliente
	//@param std::string s: cadena a enviar
	//@return Número de bytes enviados
	int enviarACliente(std::string s);


};

