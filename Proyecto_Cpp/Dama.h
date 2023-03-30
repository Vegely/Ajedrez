class Dama
{
public:
	Dama();
	~Dama();

private:
	int valor;
	bool color;
	int posicion[2];
	int** puede_comer;
	int** puede_defender;
	int** amenazada;
};

