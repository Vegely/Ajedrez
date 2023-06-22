#ifndef COORDINADORAJEDREZ_H
#define COORDINADORAJEDREZ_H

#include "MotorDeJuego.h"
#include "Mundo.h"
#include <thread>
#include "UI.h"
#include "Cliente.h"
#include "Servidor.h"
#include "Ranking.h"
#include "Partida.h"

#define H_MAX 25.0f
#define H_MIN -10.0f
#define W_MAX 31.5f
#define W_MIN -31.5f

constexpr const char* IA_IA = "iaia";
constexpr const char* LOCAL_IA = "localia";
constexpr const char* LOCAL_LOCAL = "locallocal";

enum Estado { INICIO, JUEGO, FIN, RANKING, CARGAR, MODO_LOCAL, MODO_RED, MODO, COLOR, SERVIDOR, CLIENTE, FALLO_CONEXION, PAUSA, COLOR_SERVIDOR, GUARDAR, INICIALIZAR_PARTIDA, CERRAR_PARTIDA};

class CoordinadorAjedrez
{
	friend class menuInicial;
	friend void hiloRed(CoordinadorAjedrez* ajedrez);

private:
	Mundo motorGrafico;
	Ranking ranking;
	ElementoRed* p_elementoRed = nullptr;
	Partida partida;

	ConfiguracionDeJuego config;

	std::thread* p_hilo_elementoRed = nullptr;
	std::thread* p_hiloMotorLogico = nullptr;

	/* ESTADO DEL JUEGO */
	Estado estado;

	/* MOTOR GRAFICO */
	Mundo mundoGrafico;

	/* VARIABLES DE GESTIÓN DE INICIALIZACIÓN Y FINALIZACIÓN */
	bool flagDeSeguridadInit = true;
	bool enPartida = false;
	bool redAbierta = false;

	DatosFinal datosFinal;

	void abrirRed();
	void cerrarHiloRed();

	void cerrarPartida();
	
public:
	/* FORMA CAN�NICA */
	CoordinadorAjedrez(void);

	/* FUNCIONES PARA CALLBACKS */
	void init(void);
	void Draw(void);
	void Timer(float value);
	void Keypress(unsigned char key);
	void Keylift (unsigned char key);
	void SpecialKeypress(int key);
	void Click(int button, int state, int x, int y);

	void renderPantallaFinal(const std::string& filepath);
};

void threadMotor(bool* p_stop, Mundo* p_motorGrafico, const ConfiguracionDeJuego* p_config, Partida* p_partida, ElementoRed* p_elementoRed, DatosFinal* p_datosFinal);
void hiloRed(CoordinadorAjedrez* p_ajedrez);

float aCoordenadasGlutX(float p);
float aCoordenadasGlutY(float p);

void parametrosTexturasMEstados();

void debugAxis(void);

#endif