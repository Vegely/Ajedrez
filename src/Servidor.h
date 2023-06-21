#ifndef _SERVIDOR__H_
#define _SERVIDOR__H_

#include "Socket.h"
#include "ElementoRed.h"

#include <fstream>
#include <sstream>

constexpr const char* RUTA_IPCONFIG = "../temp/ipconfig.txt";
constexpr const char* COMANDO_IPCONFIG = "ipconfig > ../temp/ipconfig.txt";

/*
* Compartir 5 números de 0 a 7 y el último de 0 a 1
*/

class Servidor : public ElementoRed
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
	Servidor() { };

	//No hace falta destructor (conflictos de copia/asignación eliminados), lo gestiona el SO

	//Eliminamos posibles conflictos de copia/asignación
	Servidor(const Servidor&) = delete;
	Servidor& operator= (const Servidor&) = delete;

	void inicializa() { inicializaWinSock(); ipDir(); };
	//Conecta el servidor
	bool conectarServidor();
	//Desconecta el servidor
	void desconectarServidor();

	//Genera un código de partida a partir de la ip del equipo
	//@return String con código de la partida
	//////////////////////////////////////
	//std::string generarCodigoPartida(); //
	//////////////////////////////////////

	//Recibe una cadena de caracteres del cliente
	//@param std::string s: cadena recibida
	//@return Número de bytes recibidos
	int recibir(std::string& s) const;
	//Manda una cadena de caracteres al cliente
	//@param std::string s: cadena a enviar
	//@return Número de bytes enviados
	int enviar(std::string s) const;

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

#endif