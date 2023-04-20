#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

//friend de la clase partida/tablero  o como se llame para acceder a sus atributos privados


constexpr int NPOS = -1;
constexpr int MAX_BUFF = 250;

class Registro
{
private:
	const char* nombre_registro = "registro.txt";
	std::vector<int> no_finalizadas;
	int id_ultima_partida = NPOS;
	int numero_partidas = NPOS;
	
	void inicializaRegistro();
	void actualizaRegistro() const;

public:
	//Constructor
	Registro();
	//Solamente hay 1 registro --> No se puede copiar ni asignar
	Registro(const Registro&) = delete; 
	Registro& operator= (const Registro&) = delete;

};

