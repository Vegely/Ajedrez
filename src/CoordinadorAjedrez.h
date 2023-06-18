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

enum Estado { INICIO, JUEGO, FIN, RANKING, CARGAR, MODO_LOCAL, MODO_RED, MODO, COLOR, SERVIDOR, CLIENTE, FALLO_CONEXION, PAUSA, COLOR_SERVIDOR, GUARDAR};

void threadMotor(MotorDeJuego* motorLogico, Mundo* motorGrafico, const ConfiguracionDeJuego* p_configuracion, DatosFinal* p_datosFinal);

class CoordinadorAjedrez
{
	friend class menuInicial;

public:
	Mundo motorGrafico;
	Ranking ranking;
	Cliente* cliente = nullptr;
	Servidor* servidor = nullptr;
	Partida partida;

	bool inicializarPartida;

	std::thread* hilo_servidor = nullptr;
	std::thread* hilo_cliente = nullptr;

private:
	/* ESTADO DEL JUEGO */
	Estado estado;
	/* MOTORES L�GICO Y GR�FICO */
	Mundo mundoGrafico;
	MotorDeJuego motorLogico;
	std::thread* motor = nullptr;
	/* VARIABLES DE GESTIÓN DE INICIALIZACIÓN Y FINALIZACIÓN */
	bool flagDeSeguridadInit = true;
	DatosFinal datosFinal;
	
public:
	/* FORMA CAN�NICA */
	CoordinadorAjedrez(void);

	/* FUNCIONES PARA CALLBACKS */
	void initGraficos(void) { mundoGrafico.init(); flagDeSeguridadInit = false; }
	void Draw(void);
	void Timer(int value);
	void Keypress(unsigned char key);
	void Keylift (unsigned char key);
	void SpecialKeypress(int key);
	void Click(int button, int state, int x, int y);

	friend void hiloServidor(CoordinadorAjedrez* ajedrez);
	friend void hiloCliente(CoordinadorAjedrez* ajedrez);
};

void threadMotor(MotorDeJuego* motorLogico, Mundo* motorGrafico, const ConfiguracionDeJuego* p_configuracion, DatosFinal* p_datosFinal);
void hiloServidor(CoordinadorAjedrez* ajedrez);
void hiloCliente(CoordinadorAjedrez* ajedrez);

float aCoordenadasGlutX(float p);

float aCoordenadasGlutY(float p);

void parametrosTexturasMEstados();

#endif