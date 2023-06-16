#pragma once

struct ConfiguracionDeJuego
{
	enum class FormasDeInteraccion { LOCAL, IA };
	FormasDeInteraccion config[2];

	FormasDeInteraccion operator[] (int i) const { return config[i]; }
	FormasDeInteraccion& operator[] (int i) { return config[i]; }
};