#ifndef _SERVIDOR__H_
#define _SERVIDOR__H_

#include "Socket.h"
#include "ElementoRed.h"

#include <fstream>
#include <sstream>

constexpr const char* RUTA_IPCONFIG = "../temp/ipconfig.txt";
constexpr const char* COMANDO_IPCONFIG = "ipconfig > ../temp/ipconfig.txt";

/*
* Compartir 5 n�meros de 0 a 7 y el �ltimo de 0 a 1
*/

class Servidor : public ElementoRed
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
	Servidor() { };

	//No hace falta destructor (conflictos de copia/asignaci�n eliminados), lo gestiona el SO

	//Eliminamos posibles conflictos de copia/asignaci�n
	Servidor(const Servidor&) = delete;
	Servidor& operator= (const Servidor&) = delete;

	void inicializa() { inicializaWinSock(); ipDir(); };
	//Conecta el servidor
	bool conectar();
	//Desconecta el servidor
	void desconectar();

	//Genera un c�digo de partida a partir de la ip del equipo
	//@return String con c�digo de la partida
	//////////////////////////////////////
	//std::string generarCodigoPartida(); //
	//////////////////////////////////////

	//Recibe una cadena de caracteres del cliente
	//@param std::string s: cadena recibida
	//@return N�mero de bytes recibidos
	int recibir(std::string& s) const;
	//Manda una cadena de caracteres al cliente
	//@param std::string s: cadena a enviar
	//@return N�mero de bytes enviados
	int enviar(std::string s) const;

	std::string getIp() { return ipv4; };

};

#endif