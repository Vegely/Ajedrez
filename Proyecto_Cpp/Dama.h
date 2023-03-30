#ifndef _Dama__H_
#define	_Dama__H_

	class Dama
	{
	public:
		Dama();
		~Dama();

	private:
		int valor;
		bool color;
		int posicion[2];
		int puede_comer[8][8];
		int puede_defender[8][8];
		int amenazada[8][8];
	};

#endif // !_Dama__H_ //