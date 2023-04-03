#include "cliente.h"

int Cliente::enviarAServidor(std::string s) {
	return sck->envia(s);
}

int Cliente::recibirDeServidor(std::string& s) {
	return sck->recibe(s);
}

void Cliente::ipDir() {
	std::string direccion_ip = "192.168.0.25\n192.168.182.1\n192.168.8.1\n192.168.0.21";
	std::string cmd = "";
	std::istringstream iss(direccion_ip);
	char buffer[MAX_LONG_BUFF];
	int porcentaje = 0;
	bool ip_valida = 0;

	while (std::getline(iss, ip)) {
		//Construye el comando para system y manda la respuesta ping a temp.txt
		cmd = "ping " + ip + " > temp.txt";
		system(cmd.c_str());
		std::fstream fs("temp.txt");
		while (fs.getline(buffer, sizeof(buffer))) {
			std::stringstream ss;
			std::string token;
			ss << buffer;
			ss >> token;
			if (token == "Respuesta") {
				std::string respuesta;
				ss >> token >> token >> respuesta;
				if (respuesta == "Host") {
					break;
				}
				else {
					ip_valida = 1;
					break;
				}
			}
		}
		if (ip_valida == 1) {
			fs.close();
			break;
		}
	}
	std::cout << ip;
}

void Cliente::conectarCliente() {
	//IP del equipo al que se conecta ("127.0.0.1" --> localhost)
	//NULL: no se especifican opciones en host_info
	sck = new Socket{ NULL };

	ipDir();
	sck->creaSocket(ip.c_str());


	sck->conectarAServidor();
}

void Cliente::desconectarCliente() {
	sck->desconecta();

	//Conexión cerrada: elimina el socket para la comunicación
	delete sck;
}
