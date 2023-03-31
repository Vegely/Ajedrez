#ifndef _Pieza__H_
#define	_Pieza__H_

#include <vector>
#include <ostream>

struct Punto {
	unsigned char x, y;
};


class Pieza
{
private:
	const unsigned char valor;
	const bool color;
	int posicion[2];						
	std::vector<Pieza> puede_comer;			//Piezas que puede comer
	std::vector<Pieza> esta_protegiendo;	//Piezas de su propio equipo con las que colisiona en el movimiento
	std::vector<Pieza> amenazas;			//Piezas que amenazan a la nuestra
	std::vector<Punto> puede_mover;			//Lugares disponibles para mover

	void actualizarPuedaComer();
	void actualizarEstaProtegiendo();
	void actualizarAmenazas();

public:
	friend std::ostream& operator<<(std::ostream& o, const Pieza& p);

	Pieza();
	~Pieza();

	void mover() {}							//Mueve la pieza
};

std::ostream& operator<<(std::ostream& o, const Pieza& p);

#endif // !_Pieza__H_ //