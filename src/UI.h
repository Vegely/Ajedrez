#include "Caja.h"

struct UI {
	struct pantallaColorJugador
	{
		Caja negro{ -10.0f, 2.0f, -4.0f, 1.0f };
		Caja blanco{ -2.0,2.0,0.0,1.0 };
		Caja atras{ 1.0,2.0,3.0,1.0 };

		void dibuja()
		{
			negro.dibuja();
			blanco.dibuja();
			atras.dibuja();
		}
	};

	pantallaColorJugador pcj;

};

