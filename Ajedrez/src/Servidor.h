#pragma once

#include "Socket.h"
#include <fstream>
#include <sstream>

/*
* Compartir 5 n�meros de 0 a 7 y el �ltimo de 0 a 1
*/

class Servidor
{
private:
	//Atiende peticiones de conexi�n
	Socket* sck = nullptr;
	//Se encarga de la comunicaci�n
	Socket* comunicacion_sck = nullptr;
	//Almacena ip en la que est� conectada el servidor
	std::string ipv4 = "";

	//Obtiene la direcci�n ipv4 a la que est� conectada el ordenador
	void ipDir();

public:
	//Constructor: 
	// - Inicializaci�n por defecto
	// - Inicializaci�n WinSock
	// - Obtenci�n de la ip del host
	Servidor() { inicializaWinSock(); ipDir(); };

	//No hace falta destructor (conflictos de copia/asignaci�n eliminados), lo gestiona el SO

	//Eliminamos posibles conflictos de copia/asignaci�n
	Servidor(const Servidor&) = delete;
	Servidor& operator= (const Servidor&) = delete;

	//Conecta el servidor
	void conectarServidor();
	//Desconecta el servidor
	void desconectarServidor();

	//Genera un c�digo de partida a partir de la ip del equipo
	//@return String con c�digo de la partida
	//////////////////////////////////////
	std::string generarCodigoPartida(); //
	//////////////////////////////////////

	//Recibe una cadena de caracteres del cliente
	//@param std::string s: cadena recibida
	//@return N�mero de bytes recibidos
	int recibirDeCliente(std::string& s);
	//Manda una cadena de caracteres al cliente
	//@param std::string s: cadena a enviar
	//@return N�mero de bytes enviados
	int enviarACliente(std::string s);

	std::string getip() { return ipv4; };

};

// Main
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
Servidor s;
std::string str;

std::cout << s.getip();

s.conectarServidor();

while (!salir) {
	if (tnegras) {
		cenviar = "";
		std::getline(std::cin, cenviar);
		s.enviarACliente(cenviar);
		cambiarTurno(tnegras, tblancas);
	}
	else if (tblancas) {
		if (s.recibirDeCliente(crecibir) > 0) {
			std::cout << crecibir << std::endl;
			crecibir = "";
		}
		cambiarTurno(tnegras, tblancas);
	}

}

s.desconectarServidor();
*/