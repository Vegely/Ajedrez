#include "Caja.h"
#include "freeglut.h"
#include "ETSIDI.h"

constexpr const char* RUTA_COLOR_JUGADOR = "pantallas/seleccion color.png";
constexpr const char* RUTA_SERVIDOR = "pantallas/servidor.png";
constexpr const char* RUTA_CLIENTE = "pantallas/cliente.png";
constexpr const char* RUTA_GUARDAR = "pantallas/guardar.png";
constexpr const char* RUTA_ROL_RED = "pantallas/rol red.png";
constexpr const char* RUTA_PAUSA = "pantallas/pausa.png";
constexpr const char* RUTA_MODO_DE_JUEGO = "pantallas/modo de juego.png";
constexpr const char* RUTA_JUEGO_LOCAL = "pantallas/juego local.png";
constexpr const char* RUTA_INICIO = "pantallas/inicio.png";
constexpr const char* RUTA_FIN_DE_PARTIDA = "pantallas/fin de la partida.png";
constexpr const char* RUTA_FALLO_CONEXION = "pantallas/fallo de conexion.png";
constexpr const char* RUTA_CARGAR_PARTIDA = "pantallas/cargar partida pag intermedia.png";
constexpr const char* RUTA_RANKINGS = "pantallas/rankings pag intermedia.png";

constexpr const char* RUTA_FUENTES = "fuentes/SourceSerifPro-Bold.ttf";

constexpr int TAM_FRASE = 10;
constexpr int TABULADOR = 9;
constexpr int SUPRIMIR = 127;
constexpr const char* JIA = "IA";

enum class Guardar { BLANCAS, NEGRAS, PARTIDA, NONE };

struct PantallaBase {
	std::string ruta;
	PantallaBase(std::string ruta) : ruta(ruta) {}
};

struct PantallaColorJugador :public PantallaBase
{
	Caja negro{ -4.45, 9.9, 4.0, 5.9 };
	Caja blanco{ -4.45,4.9,4.0,1.0 };
	Caja atras{ 25.4,-2.3,29.8,-6.3 };

	PantallaColorJugador():PantallaBase(RUTA_COLOR_JUGADOR){}

	void dibuja() { glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(ruta.c_str()).id); }
};

struct PantallaFalloConexion :public PantallaBase {
	Caja aceptar{ -5.0, 7.3, 4.6, 3.5 };

	PantallaFalloConexion():PantallaBase(RUTA_FALLO_CONEXION) {}

	void dibuja()  { glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(ruta.c_str()).id); /*aceptar.dibuja();*/ }
};

struct PantallaFinPartida :public PantallaBase {
	Caja guardar_y_salir{ -8.5, 9.9, 8.1, 5.9 };
	Caja salir_sin_guardar{ -9.7, 4.9, 9.3, 1.0 };
	PantallaFinPartida(): PantallaBase(RUTA_FIN_DE_PARTIDA){}
	void dibuja()  { glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(ruta.c_str()).id); /*guardar_y_salir.dibuja(); salir_sin_guardar.dibuja();*/ }
};

struct PantallaCliente :public PantallaBase {
	Caja cliente{ -9.5, 10.0, 9.3, 6.0 };
	Caja atras{ 25.4,-2.3,29.8,-6.3 };
	PantallaCliente(): PantallaBase(RUTA_CLIENTE){}

	void dibuja()  { glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(ruta.c_str()).id); /*cliente.dibuja(); atras.dibuja();*/ }
};

struct PantallaPausa :public PantallaBase {
	Caja guardar_y_salir{ -8.5, 9.9, 8.1, 5.9 };
	Caja salir_sin_guardar{ -9.7, 4.9, 9.3, 1.0 };
	PantallaPausa():PantallaBase(RUTA_PAUSA){}
	void dibuja()  { glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(ruta.c_str()).id); /*guardar_y_salir.dibuja(); salir_sin_guardar.dibuja();*/ }
};

struct PantallaServidor :public PantallaBase {
	Caja servidor{ -9.6, 9.9, 9.3, 6.0 };
	Caja atras{ 25.4,-2.3,29.8,-6.3 };
	PantallaServidor(): PantallaBase(RUTA_SERVIDOR){}
	void dibuja()  { glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(ruta.c_str()).id); /*servidor.dibuja(); atras.dibuja();*/ }
};

struct PantallaCargarPartida :public PantallaBase {
	Caja atras{ 25.4,-2.3,29.8,-6.3 };
	Caja siguiente{ 20.0,-2.3,24.5,-6.3 };
	Caja anterior{ -24.3,-2.3,-19.9,-6.3 };
	PantallaCargarPartida(): PantallaBase(RUTA_CARGAR_PARTIDA){}

	void dibuja()  { glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(ruta.c_str()).id); /*atras.dibuja(); siguiente.dibuja(); anterior.dibuja();*/ }
};

struct PantallaRankings :public PantallaBase {
	Caja atras{ 25.4,-2.3,29.8,-6.3 };
	Caja siguiente{ 20.0,-2.3,24.5,-6.3 };
	Caja anterior{ -24.3,-2.3,-19.9,-6.3 };
	PantallaRankings(): PantallaBase(RUTA_RANKINGS){}
	void dibuja()  { glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(ruta.c_str()).id); /*atras.dibuja(); siguiente.dibuja(); anterior.dibuja();*/ }
};

struct PantallaElegirRol :public PantallaBase
{
	Caja servidor{ -4.65f, 9.9f, 4.2f, 5.9f };
	Caja cliente{ -4.45,4.9,4.0,0.9 };
	Caja atras{ 25.4,-2.3,29.7,-6.3 };
	PantallaElegirRol(): PantallaBase(RUTA_ROL_RED){}
	void dibuja() 
	{
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(ruta.c_str()).id);
		/*servidor.dibuja();
		cliente.dibuja();
		atras.dibuja();*/
	}
};
struct PantallaInicio :public PantallaBase
{
	Caja nuevaPartida{ -16.65f, 9.9f, -1.0, 5.9f };
	Caja cargarPartida{ 1.0, 9.9,16.65,5.9 };
	Caja mostrarRankings{ -9.45,4.9,9.45,0.9 };
	Caja salir{ -3.15,-0.1,3.25,-4.0 };

	PantallaInicio(): PantallaBase(RUTA_INICIO){}
	
	void dibuja();
};

struct PantallaJugadorLocal :public PantallaBase
{
	Caja jugadorIA{ -7.65f, 9.9f, 7.2f, 5.9f };
	Caja dosJugadores{ -6.65,4.9,6.2,0.9 };
	Caja IAIA{ -4.35,-0.1,4.25,-4.0 };
	Caja atras{ 25.4,-2.3,29.7,-6.3 };
	PantallaJugadorLocal():PantallaBase(RUTA_JUEGO_LOCAL){}
	void dibuja()
	{
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(ruta.c_str()).id);
		/*jugadorIA.dibuja();
		dosJugadores.dibuja();
		atras.dibuja();
		IAIA.dibuja();*/
	}
	//Estado click(int button, int state, float x, float y) override;
};

struct PantallaModoDeJuego :public PantallaBase
{
	Caja local{ -6.65f, 9.9f, 6.45f, 5.9f };
	Caja red{ -7.1,4.9,7.1,0.9 };
	Caja salir{ -3,-0.1,3.2,-4.0 };
	PantallaModoDeJuego(): PantallaBase(RUTA_MODO_DE_JUEGO){}
	void dibuja()
	{
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(ruta.c_str()).id);
		/*local.dibuja();
		red.dibuja();
		salir.dibuja();*/
	}
};

struct PantallaGuardar : public PantallaBase {

	Guardar estado = Guardar::NONE;
	std::string snombre_partida = "";
	std::string sblancas = "";
	std::string snegras = "";
	std::string smodo = "";
	bool existe = 0;

	Caja nombre_partida{ -25.8f, 10.2f, 25.8f, 6.3f };
	Caja blancas{ -25.8,1.3f,-0.3,-2.7f };
	Caja negras{ 0.7,1.3,25.4,-2.7 };

	PantallaGuardar(): PantallaBase(RUTA_GUARDAR){}

	void dibuja() { glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(ruta.c_str()).id); }

	void escrituraGlut();
};


