#ifndef _Rey__H_
#define	_Rey__H_

	class Rey
	{
	public:
		Rey();
		~Rey();

	private:
		int valor;
		bool color;
		int posicion[2];
		int puede_comer[8][8];
		int puede_defender[8][8];
		int amenazada[8][8];
	};

#endif // !_Rey__H_ //