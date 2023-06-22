#include "Servidor.h"

int Servidor::recibir(std::string& s) const 
{
	return comunicacion_sck->recibe(s);
}

int Servidor::enviar(std::string s) const 
{
	return comunicacion_sck->envia(s);
}

void Servidor::ipDir() {
	/*
	* - El equipo puede tener varios adaptadores de red, cada uno con una ip diferente.
	* - Para distinguir la ip que usa el equipo para conectarse a internet (las otras direcciones ip pueden
	*	ser para m�quinas virtuales o simplemente no estar habilitadas), se usa la instrucci�n ipconfig de la
	*	cmd. La ip real ser� aquella que tenga asociada una puerta de enlace.
	* - No considera situaciones en las que el equipo tenga varias ip, todas ellas con puerta de enlace asociada.
	* - El m�todo funciona aunque la cmd est� en ingl�s (las palabras usadas en la b�squeda son independientes del idioma).
	*/

	//Variables ipv4 y puerta de enlace
	std::string p_enlace{ "" };
	//Buffer para la lectura l�nea a l�nea
	char buffer[MAX_LONG_BUFF];

	//Ejecuta ipconfig y saca el resultado a un fichero temp.txt
	system(COMANDO_IPCONFIG);
	//Abre el fichero con el contenido de ipconfig en modo lectura
	std::ifstream ifs{ RUTA_IPCONFIG };

	//Lee l�nea a l�nea el contenido de temp.txt y lo almacena en buffer
	while (ifs.getline(buffer, sizeof(buffer))) {
		//Convierte la el buffer en string
		std::string sbuffer{ buffer };
		//�La palabra clave "IPv4" (string independiente del idioma) est� dentro de la l�nea le�da?
		if (sbuffer.find("IPv4") != std::string::npos) {
			//Lee hasta encontrar ": " y asigna lo que haya a partir de dicho punto en ipv4
			ipv4 = sbuffer.substr(sbuffer.find(": ") + 2);

			//Lee la l�nea relativa a la m�scara de subred (no interesa)
			ifs.getline(buffer, sizeof(buffer));
			//Lee la l�nea relativa a la puerta de enlace
			ifs.getline(buffer, sizeof(buffer));
			sbuffer = buffer;

			//Almacena la direcci�n de la puerta de enlace en p_enlace
			p_enlace = sbuffer.substr(sbuffer.find(": ") + 2);

			//Si p_enlace no es una cadena vac�a, sale del bucle (ipv4 buscada)
			if (p_enlace != "")
				break;
		}
	}
	if (p_enlace == "") {
		std::cout << "Direccion ipv4 no encontrada" << std::endl;
		ipv4 = "";
	}
}

bool Servidor::conectar() {
	//NULL: almacena en host_info todas las direcciones de red almacenadas en el equipo 
	//AI_PASSIVE: indica que vamos a hacer una llamada a bind()
	sck = new Socket{ AI_PASSIVE };
	comunicacion_sck = new Socket;

	//Creaci�n de la conexi�n
	sck->creaSocket(NULL);
	sck->vincula();
	sck->escucha();
	sck->aceptaConexion(*comunicacion_sck);

	//Solo se hace una conexi�n: no es necesario aceptar m�s conexiones
	delete sck;
	return true;
}

void Servidor::desconectar() {
	comunicacion_sck->desconecta();

	//Conexi�n cerrada: elimina el socket para la comunicaci�n
	delete comunicacion_sck;
}