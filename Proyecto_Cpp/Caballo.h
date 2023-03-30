#ifndef _Caballo__H_
#define	_Caballo__H_

	class Caballo
	{
	public:
		Caballo();
		~Caballo();

	private:
		int valor;
		bool color;
		int posicion[2];
		int puede_comer[8][8];
		int puede_defender[8][8];
		int amenazada[8][8];
	};

#endif // !_Caballo__H_ //
