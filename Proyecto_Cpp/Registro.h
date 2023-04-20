#pragma once

constexpr int PARTIDA_NO_ENCONTRADA = -1;

class Registro
{
private:
	int* no_finalizadas = nullptr;
	int id_ultima_partida = PARTIDA_NO_ENCONTRADA;



public:
	//Constructor
	Registro();
	//Solamente hay 1 registro --> No se puede copiar ni asignar
	Registro(const Registro&) = delete; 
	Registro& operator= (const Registro&) = delete;

	
};

