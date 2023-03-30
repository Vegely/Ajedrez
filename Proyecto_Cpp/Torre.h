#ifndef _Torre__H_
#define	_Torre__H_

	class Torre
	{
	public:
		Torre();
		~Torre();

	private:
		int valor;
		bool color;
		int posicion[2];
		int puede_comer[8][8];
		int puede_defender[8][8];
		int amenazada[8][8];
	};

#endif // !_Torre__H_ //