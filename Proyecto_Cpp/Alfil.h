#ifndef _Alfil__H_
#define	_Alfil__H_

	class Alfil
	{
	public:
		Alfil();
		~Alfil();
	
	private:
		int valor;
		bool color;
		int posicion[2];
		int puede_comer[8][8];
		int puede_defender[8][8];
		int amenazada[8][8];
	};

#endif // !_Alfil__H_ //