#pragma once
class Ranking
{
private:
public:
	//Constructor
	Ranking();

	//Solo hay 1 ranking --> No se puede copiar ni asignar
	Ranking(const Ranking&) = delete;
	Ranking& operator=(const Ranking&) = delete;
};

