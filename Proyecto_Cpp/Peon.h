#ifndef _Peon__H_
#define	_Peon__H_

	class Peon
	{
	public:
		Peon();
		~Peon();

	private:
		int valor;
		bool color;
		int posicion[2];
		int puede_comer[8][8];
		int puede_defender[8][8];
		int amenazada[8][8];
	};

#endif // !_Peon__H_ //