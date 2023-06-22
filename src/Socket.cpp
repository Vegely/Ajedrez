#include "Socket.h"

Socket::Socket(int flags, int familia,
	int tipo_socket, int protocolo) {

	red_info = new addrinfo;
	//Pone el bloque de memoria donde está red_info a 0 (necesario inicializar a 0)
	ZeroMemory(red_info, sizeof(*red_info));
	//Almacena en red_info la información sobre el tipo de conexión
	red_info->ai_family = familia;
	red_info->ai_socktype = tipo_socket;
	red_info->ai_protocol = protocolo;
	red_info->ai_flags = flags;
}

void Socket::creaSocket(const char* direccion) {
	int error_creacion;

	//Obtiene información sobre la direcciones registradas en el ordenador 
	error_creacion = getaddrinfo(direccion, PUERTO_PREDETERMINADO, red_info, &host_info);

	//Comprobación de errores
	if (error_creacion != 0) {
		std::cout << "Error en la obtencion de la direccion: " << error_creacion << std::endl;
		WSACleanup();
	}

	//Crea un socket en el servidor con la información de conexión del host
	//Acepta peticiones de conexión
	sck = socket(host_info->ai_family, host_info->ai_socktype, host_info->ai_protocol);

	//Comprobación de errores
	if (sck == INVALID_SOCKET) {
		std::cout << "Error en la creacion del socket: " << WSAGetLastError();
		freeaddrinfo(host_info);
	}
}

void Socket::vincula() {
	int error_vinculacion;

	//Asocia el programa con el socket creado
	error_vinculacion = bind(sck, host_info->ai_addr, (int)(host_info->ai_addrlen));

	//Comprobación de errores
	if (error_vinculacion == SOCKET_ERROR) {
		std::cout << "Error en la vinculacion: " << WSAGetLastError();
		freeaddrinfo(host_info);
		closesocket(sck);
		WSACleanup();
	}
	//Ya no hace falta la información sobre la conexión (el socket ya está creado y vinculado)
	freeaddrinfo(host_info);
}

void Socket::escucha() {
	int error_escucha;

	//Avisa al SO de que comience a atender conexiones
	error_escucha = listen(sck, SOMAXCONN);

	//Comprobación de errores
	if (error_escucha == SOCKET_ERROR) {
		std::cout << "Error al atender la conexion: " << error_escucha << std::endl;
		closesocket(sck);
		WSACleanup();
	}
}

void Socket::aceptaConexion(Socket& sck_aux) {
	//Indica al SO que acepte conexiones de clientes si las hay
	//Devuelve un socket a través del cual se va a realizar la conexión
	//Si se tratara con varios clientes, se mandaría este socket a un hilo diferente
	sck_aux.sck = accept(sck, nullptr, nullptr);

	//Comprobación de errores
	if (sck_aux.sck == INVALID_SOCKET) {
		std::cout << "Error al aceptar la conexion " << std::endl;
		closesocket(sck);
		WSACleanup();
	}

	//No es necesario aceptar más conexiones: se cierra el socket
	closesocket(sck);
}

bool Socket::conectarAServidor() {
	int error_conexion;

	//Establece una conexión entre los sockets del cliente y servidor 
	//¡Ojo! "host_info" es una lista enlazada, habría que iterar para realizar la conexión
	error_conexion = connect(sck, host_info->ai_addr, (int)host_info->ai_addrlen);

	//Comprobación de errores
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

	//Envía una cadena de caracteres (const char*)
	bytes_enviados = send(sck, s.c_str(), s.length(), 0);

	//Comprobación de errores
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

	//Recibe información del cliente y devuelve número de bytes recibidos
	//Longitud del mensaje limitada (gusanos)
	bytes_recibidos = recv(sck, buffer, (int)sizeof(buffer), 0);

	//Si recibe información, la incluye en la cadena y devuelve los bytes recibidos
	if (bytes_recibidos > 0) {
		for (int i = 0; i < bytes_recibidos; i++) {
			s += buffer[i];
		}
		s += '\0';
		return bytes_recibidos;
	}
	//Si recibe 0, el cliente ha cerrado la conexión
	else if (bytes_recibidos == 0) {
		std::cout << "Conexion cerrada " << std::endl;
		return bytes_recibidos;
	}
	//Error al recibir la información
	else {
		std::cout << "Error al recibir el mensaje: " << WSAGetLastError() << std::endl;
		return -1;
	}

}

void Socket::desconecta() {
	int error_desconexion;

	//Termina la conexión
	error_desconexion = shutdown(sck, SD_SEND);

	//Comprobación de errores
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
	WSADATA sck_info; //Contiene información para la implementación de sockets
	int error_inicializacion_ws;

	//Argumentos: (versión, puntero a estructura WSADATA)
	error_inicializacion_ws = WSAStartup(MAKEWORD(2, 2), &sck_info);

	//Comprobación de errores
	if (error_inicializacion_ws != 0)
		std::cout << "Error en la inicializacion de WinSock: " << error_inicializacion_ws << std::endl;
}