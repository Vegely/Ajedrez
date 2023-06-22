#include "Socket.h"

Socket::Socket(int flags, int familia,
	int tipo_socket, int protocolo) {

	red_info = new addrinfo;
	//Pone el bloque de memoria donde est� red_info a 0 (necesario inicializar a 0)
	ZeroMemory(red_info, sizeof(*red_info));
	//Almacena en red_info la informaci�n sobre el tipo de conexi�n
	red_info->ai_family = familia;
	red_info->ai_socktype = tipo_socket;
	red_info->ai_protocol = protocolo;
	red_info->ai_flags = flags;
}

void Socket::creaSocket(const char* direccion) {
	int error_creacion;

	//Obtiene informaci�n sobre la direcciones registradas en el ordenador 
	error_creacion = getaddrinfo(direccion, PUERTO_PREDETERMINADO, red_info, &host_info);

	//Comprobaci�n de errores
	if (error_creacion != 0) {
		std::cout << "Error en la obtencion de la direccion: " << error_creacion << std::endl;
		WSACleanup();
	}

	//Crea un socket en el servidor con la informaci�n de conexi�n del host
	//Acepta peticiones de conexi�n
	sck = socket(host_info->ai_family, host_info->ai_socktype, host_info->ai_protocol);

	//Comprobaci�n de errores
	if (sck == INVALID_SOCKET) {
		std::cout << "Error en la creacion del socket: " << WSAGetLastError();
		freeaddrinfo(host_info);
	}
}

void Socket::vincula() {
	int error_vinculacion;

	//Asocia el programa con el socket creado
	error_vinculacion = bind(sck, host_info->ai_addr, (int)(host_info->ai_addrlen));

	//Comprobaci�n de errores
	if (error_vinculacion == SOCKET_ERROR) {
		std::cout << "Error en la vinculacion: " << WSAGetLastError();
		freeaddrinfo(host_info);
		closesocket(sck);
		WSACleanup();
	}
	//Ya no hace falta la informaci�n sobre la conexi�n (el socket ya est� creado y vinculado)
	freeaddrinfo(host_info);
}

void Socket::escucha() {
	int error_escucha;

	//Avisa al SO de que comience a atender conexiones
	error_escucha = listen(sck, SOMAXCONN);

	//Comprobaci�n de errores
	if (error_escucha == SOCKET_ERROR) {
		std::cout << "Error al atender la conexion: " << error_escucha << std::endl;
		closesocket(sck);
		WSACleanup();
	}
}

void Socket::aceptaConexion(Socket& sck_aux) {
	//Indica al SO que acepte conexiones de clientes si las hay
	//Devuelve un socket a trav�s del cual se va a realizar la conexi�n
	//Si se tratara con varios clientes, se mandar�a este socket a un hilo diferente
	sck_aux.sck = accept(sck, nullptr, nullptr);

	//Comprobaci�n de errores
	if (sck_aux.sck == INVALID_SOCKET) {
		std::cout << "Error al aceptar la conexion " << std::endl;
		closesocket(sck);
		WSACleanup();
	}

	//No es necesario aceptar m�s conexiones: se cierra el socket
	closesocket(sck);
}

bool Socket::conectarAServidor() {
	int error_conexion;

	//Establece una conexi�n entre los sockets del cliente y servidor 
	//�Ojo! "host_info" es una lista enlazada, habr�a que iterar para realizar la conexi�n
	error_conexion = connect(sck, host_info->ai_addr, (int)host_info->ai_addrlen);

	//Comprobaci�n de errores
	if (error_conexion == SOCKET_ERROR) {
		std::cout << "No se pudo conectar al servidor: " << error_conexion << std::endl;
		closesocket(sck);
		WSACleanup();
		return false;
	}

	//Ya no es necesario host_info
	freeaddrinfo(host_info);
	return true;
}

int Socket::envia(std::string s) {
	int bytes_enviados;

	//Env�a una cadena de caracteres (const char*)
	bytes_enviados = send(sck, s.c_str(), s.length(), 0);

	//Comprobaci�n de errores
	if (bytes_enviados == SOCKET_ERROR) {
		std::cout << "Error al enviar el mensaje: " << WSAGetLastError() << std::endl;
		closesocket(sck);
		WSACleanup();
		return bytes_enviados;
	}
	//Correcto si bytes_enviado >= 0
	return bytes_enviados;
}

int Socket::recibe(std::string& s) {
	int bytes_recibidos;
	char buffer[MAX_LONG_BUFF];

	//Recibe informaci�n del cliente y devuelve n�mero de bytes recibidos
	//Longitud del mensaje limitada (gusanos)
	bytes_recibidos = recv(sck, buffer, (int)sizeof(buffer), 0);

	//Si recibe informaci�n, la incluye en la cadena y devuelve los bytes recibidos
	if (bytes_recibidos > 0) {
		for (int i = 0; i < bytes_recibidos; i++) {
			s += buffer[i];
		}
		s += '\0';
		return bytes_recibidos;
	}
	//Si recibe 0, el cliente ha cerrado la conexi�n
	else if (bytes_recibidos == 0) {
		std::cout << "Conexion cerrada " << std::endl;
		return bytes_recibidos;
	}
	//Error al recibir la informaci�n
	else {
		std::cout << "Error al recibir el mensaje: " << WSAGetLastError() << std::endl;
		return -1;
	}

}

void Socket::desconecta() {
	int error_desconexion;

	//Termina la conexi�n
	error_desconexion = shutdown(sck, SD_SEND);

	//Comprobaci�n de errores
	if (error_desconexion == SOCKET_ERROR) {
		std::cout << "Error en la desconexion: " << WSAGetLastError() << std::endl;
		closesocket(sck);
		WSACleanup();

	}

	//Cierra el socket
	closesocket(sck);
	WSACleanup();
}

void inicializaWinSock() {
	WSADATA sck_info; //Contiene informaci�n para la implementaci�n de sockets
	int error_inicializacion_ws;

	//Argumentos: (versi�n, puntero a estructura WSADATA)
	error_inicializacion_ws = WSAStartup(MAKEWORD(2, 2), &sck_info);

	//Comprobaci�n de errores
	if (error_inicializacion_ws != 0)
		std::cout << "Error en la inicializacion de WinSock: " << error_inicializacion_ws << std::endl;
}