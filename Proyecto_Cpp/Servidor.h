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
	//Almacena ip en la que está conectada el servidor
	std::string ipv4 = "";

	//Obtiene la dirección ipv4 a la que está conectada el ordenador
	void ipDir();

public:
	//Constructor: 
	// - Inicialización por defecto
	// - Inicialización WinSock
	// - Obtención de la ip del host
	Servidor() { inicializaWinSock(); ipDir(); };

	//No hace falta destructor (conflictos de copia/asignación eliminados), lo gestiona el SO

	//Eliminamos posibles conflictos de copia/asignación
	Servidor(const Servidor&) = delete;
	Servidor& operator= (const Servidor&) = delete;

	//Conecta el servidor
	void conectarServidor();
	//Desconecta el servidor
	void desconectarServidor();

	//Genera un código de partida a partir de la ip del equipo
	//@return String con código de la partida
	//////////////////////////////////////
	std::string generarCodigoPartida(); //
	//////////////////////////////////////

	//Recibe una cadena de caracteres del cliente
	//@param std::string s: cadena recibida
	//@return Número de bytes recibidos
	int recibirDeCliente(std::string& s);
	//Manda una cadena de caracteres al cliente
	//@param std::string s: cadena a enviar
	//@return Número de bytes enviados
	int enviarACliente(std::string s);

	std::string getip() { return ipv4; };

};

