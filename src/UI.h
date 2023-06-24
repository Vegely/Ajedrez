#ifndef _UI__H_
#define _UI__H_

#include "Caja.h"
#include "freeglut.h"
#include <ETSIDI.h>
#include "MotorDeJuego.h"

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

constexpr const char* RUTA_JAQUE_MATE_BLANCAS = "pantallas/jaque_mate_blancas.png";
constexpr const char* RUTA_JAQUE_MATE_NEGRAS = "pantallas/jaque_mate_negras.png";
constexpr const char* RUTA_REY_AHOGADO = "pantallas/rey_ahogado.png";
constexpr const char* RUTA_MATERIAL_INSUFICIENTE = "pantallas/material_insuficiente.png";
constexpr const char* RUTA_PASIVIDAD = "pantallas/pasividad.png";
constexpr const char* RUTA_REPETICION = "pantallas/repeticion.png";

constexpr int TAM_FRASE = 10;
constexpr int TABULADOR = 9;
constexpr int SUPRIMIR = 127;
constexpr int ESCAPE = 27;
constexpr int PARTIDAS_POR_HOJA = 5;
constexpr int TAM_MAX_IP = 15;
constexpr const char* JIA = "IA";
constexpr const char* CONECTANDO = "Conectando...";

enum class Guardar { BLANCAS, NEGRAS, PARTIDA, NONE };

struct PantallaBase
{
protected:
	ETSIDI::GLTexture textura;
	std::string ruta;
	PantallaBase(const std::string& ruta) : textura(*(new ETSIDI::GLTexture)), ruta(ruta) { }

public:
	void init(void) { textura = ETSIDI::getTexture(ruta.c_str()); }
	virtual void dibuja() { glBindTexture(GL_TEXTURE_2D, textura.id); }
	
};

struct PantallaColorJugador : public PantallaBase
{
	Caja negro{ -4.45, 9.9, 4.0, 5.9 };
	Caja blanco{ -4.45,4.9,4.0,1.0 };
	Caja atras{ 25.4,-2.3,29.8,-6.3 };

	PantallaColorJugador() : PantallaBase(RUTA_COLOR_JUGADOR){}
};

struct PantallaFalloConexion : public PantallaBase {
	Caja aceptar{ -5.0, 7.3, 4.6, 3.5 };

	PantallaFalloConexion() : PantallaBase(RUTA_FALLO_CONEXION) {}
};

struct PantallaFinPartida : public PantallaBase {
	Caja guardar_y_salir{ -8.5, 9.9, 8.1, 5.9 };
	Caja salir_sin_guardar{ -9.7, 4.9, 9.3, 1.0 };
	PantallaFinPartida() : PantallaBase(RUTA_FIN_DE_PARTIDA){}
};


struct PantallaCliente : public PantallaBase {
	std::string ip = "";

	Caja cliente{ -9.5, 10.0, 9.3, 6.0 };
	Caja atras{ 25.4,-2.3,29.8,-6.3 };

	PantallaCliente() : PantallaBase(RUTA_CLIENTE){}

};

struct PantallaPausa : public PantallaBase {
	Caja guardar_y_salir{ -8.5, 9.9, 8.1, 5.9 };
	Caja salir_sin_guardar{ -9.7, 4.9, 9.3, 1.0 };
	PantallaPausa() : PantallaBase(RUTA_PAUSA){}
};

struct PantallaServidor : public PantallaBase {
	Caja servidor{ -9.6, 9.9, 9.3, 6.0 };
	Caja atras{ 25.4,-2.3,29.8,-6.3 };
	PantallaServidor() : PantallaBase(RUTA_SERVIDOR){}
};

struct PantallaCargarPartida : public PantallaBase {
	int pagina_actual = 0;
	int npaginas = 0;

	std::string p1_nombre = "";
	std::string p2_nombre = "";
	std::string p3_nombre = "";
	std::string p4_nombre = "";
	std::string p5_nombre = "";

	Caja atras{ 25.4,-2.3,29.8,-6.3 };
	Caja siguiente{ 20.0,-2.3,24.5,-6.3 };
	Caja anterior{ -24.3,-2.3,-19.9,-6.3 };
	Caja partida1{ -19.0, 9.0,19.0, 7.0 };
	Caja partida2{ -19.0, 6.0,19.0,4.0 };
	Caja partida3{ -19.0, 2.5,19.0,0.5 };
	Caja partida4{ -19.0, -0.5,19.0,-2.5 };
	Caja partida5{ -19.0, -3.5,19.0 ,-5.5 };


	PantallaCargarPartida() : PantallaBase(RUTA_CARGAR_PARTIDA) {}

	void escrituraGlut();
	void rellenaNombre(int i, std::string str);
	void paginaSiguiente() { if (pagina_actual >= npaginas)return; pagina_actual++; }
	void paginaAnterior() { if (pagina_actual <= 0)return; pagina_actual--; }
};

struct PantallaRankings : public PantallaBase {
	Caja atras{ 25.4,-2.3,29.8,-6.3 };
	Caja siguiente{ 20.0,-2.3,24.5,-6.3 };
	Caja anterior{ -24.3,-2.3,-19.9,-6.3 };
	PantallaRankings() : PantallaBase(RUTA_RANKINGS){}
};

struct PantallaElegirRol : public PantallaBase
{
	Caja servidor{ -4.65f, 9.9f, 4.2f, 5.9f };
	Caja cliente{ -4.45,4.9,4.0,0.9 };
	Caja atras{ 25.4,-2.3,29.7,-6.3 };
	PantallaElegirRol() : PantallaBase(RUTA_ROL_RED){}
};

struct PantallaInicio : public PantallaBase
{
	Caja nuevaPartida{ -16.65f, 9.9f, -1.0, 5.9f };
	Caja cargarPartida{ 1.0, 9.9,16.65,5.9 };
	Caja mostrarRankings{ -9.45,4.9,9.45,0.9 };
	Caja salir{ -3.15,-0.1,3.25,-4.0 };
	PantallaInicio() : PantallaBase(RUTA_INICIO){}
};

struct PantallaJugadorLocal : public PantallaBase
{
	Caja jugadorIA{ -7.65f, 9.9f, 7.2f, 5.9f };
	Caja dosJugadores{ -6.65,4.9,6.2,0.9 };
	Caja IAIA{ -4.35,-0.1,4.25,-4.0 };
	Caja atras{ 25.4,-2.3,29.7,-6.3 };
	PantallaJugadorLocal() : PantallaBase(RUTA_JUEGO_LOCAL){}
};

struct PantallaModoDeJuego : public PantallaBase
{
	Caja local{ -6.65f, 9.9f, 6.45f, 5.9f };
	Caja red{ -7.1,4.9,7.1,0.9 };
	Caja atras{ 25.4,-2.3,29.7,-6.3 };
	PantallaModoDeJuego() : PantallaBase(RUTA_MODO_DE_JUEGO){}
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

	PantallaGuardar() : PantallaBase(RUTA_GUARDAR){}
	void reset() { snombre_partida = ""; sblancas = ""; snegras = ""; smodo = ""; existe = 0; estado = Guardar::NONE; }
	void escrituraGlut();
};

#endif 