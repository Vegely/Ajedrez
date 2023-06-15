#include "Caja.h"
struct pantallaColorJugador
{
	Caja negro{ -4.45, 9.9, 4.0, 5.9 };
	Caja blanco{ -4.45,4.9,4.0,1.0 };
	Caja atras{ 25.4,-2.3,29.8,-6.3 };

	void dibuja()
	{
		negro.dibuja();
		blanco.dibuja();
		atras.dibuja();
	}
};

struct pantallaFalloConexion {
	Caja aceptar{ -5.0, 7.3, 4.6, 3.5 };

	void dibuja() { aceptar.dibuja(); }
};

struct pantallaFinPartida {
	Caja guardar_y_salir{ -8.5, 9.9, 8.1, 5.9 };
	Caja salir_sin_guardar{ -9.7, 4.9, 9.3, 1.0 };

	void dibuja() { guardar_y_salir.dibuja(); salir_sin_guardar.dibuja(); }
};

struct pantallaCliente {
	Caja cliente{ -9.5, 10.0, 9.3, 6.0 };
	Caja atras{ 25.4,-2.3,29.8,-6.3 };

	void dibuja() { cliente.dibuja(); atras.dibuja(); }
};

struct pantallaPausa {
	Caja guardar_y_salir{ -8.5, 9.9, 8.1, 5.9 };
	Caja salir_sin_guardar{ -9.7, 4.9, 9.3, 1.0 };

	void dibuja() { guardar_y_salir.dibuja(); salir_sin_guardar.dibuja(); }
};

struct pantallaServidor {
	Caja servidor{ -9.6, 9.9, 9.3, 6.0 };
	Caja atras{ 25.4,-2.3,29.8,-6.3 };

	void dibuja() { servidor.dibuja(); atras.dibuja(); }
};

struct pantallaCargarPartida {
	Caja atras{ 25.4,-2.3,29.8,-6.3 };
	Caja siguiente{ 20.0,-2.3,24.5,-6.3 };
	Caja anterior{ -24.3,-2.3,-19.9,-6.3 };

	void dibuja() { atras.dibuja(); siguiente.dibuja(); anterior.dibuja(); }
};

struct pantallaRankings {
	Caja atras{ 25.4,-2.3,29.8,-6.3 };
	Caja siguiente{ 20.0,-2.3,24.5,-6.3 };
	Caja anterior{ -24.3,-2.3,-19.9,-6.3 };

	void dibuja() { atras.dibuja(); siguiente.dibuja(); anterior.dibuja(); }
};

struct pantallaElegirRol
{
	Caja servidor{ -4.65f, 9.9f, 4.2f, 5.9f };
	Caja cliente{ -4.45,4.9,4.0,0.9 };
	Caja atras{ 25.4,-2.3,29.7,-6.3 };
	void dibuja()
	{
		servidor.dibuja();
		cliente.dibuja();
		atras.dibuja();
	}
};
struct pantallaInicio
{
	Caja nuevaPartida{ -16.65f, 9.9f, -1.0, 5.9f };
	Caja cargarPartida{ 1.0, 9.9,16.65,5.9 };
	Caja mostrarRankings{ -9.45,4.9,9.45,0.9 };
	Caja salir{ -3.15,-0.1,3.25,-4.0 };
	void dibuja()
	{
		nuevaPartida.dibuja();
		cargarPartida.dibuja();
		mostrarRankings.dibuja();
		salir.dibuja();
	}
};

struct pantallaJugadorLocal
{
	Caja jugadorIA{ -7.65f, 9.9f, 7.2f, 5.9f };
	Caja dosJugadores{ -6.65,4.9,6.2,0.9 };
	Caja IAIA{ -4.35,-0.1,4.25,-4.0 };
	Caja atras{ 25.4,-2.3,29.7,-6.3 };
	void dibuja()
	{
		jugadorIA.dibuja();
		dosJugadores.dibuja();
		atras.dibuja();
		IAIA.dibuja();
	}
};

struct pantallaModoDeJuego
{
	Caja local{ -6.65f, 9.9f, 6.45f, 5.9f };
	Caja red{ -7.1,4.9,7.1,0.9 };
	Caja salir{ -3,-0.1,3.2,-4.0 };
	void dibuja()
	{
		local.dibuja();
		red.dibuja();
		salir.dibuja();
	}
};
struct UI {
	
	pantallaElegirRol per;
	pantallaInicio pin;
	pantallaJugadorLocal pjl;
	pantallaModoDeJuego pmj;
	pantallaColorJugador pcj;
	pantallaFalloConexion pfc;
	pantallaFinPartida pfp;
	pantallaCliente pc;
	pantallaPausa pp;
	pantallaServidor ps;
	pantallaCargarPartida pcp;
	pantallaRankings pr;
};

