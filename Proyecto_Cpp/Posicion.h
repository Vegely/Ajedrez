#ifndef _POSICION__H_
#define _POSICION__H_

//Clase para hacer las comparaciones y modificaciones de casillas más sencillas
struct Posicion
{
	char x, y;

	explicit Posicion(char x = 0, char y = 0) : x(x), y(y) {}

	inline Posicion& operator- ()  {x = -x; y = -y; return *this; }
	inline Posicion& operator+= (const Posicion& rhs) { x += rhs.x; y += rhs.y; return *this; }
	inline Posicion& operator-= (Posicion rhs) { *this += ( - rhs); return *this; }
	inline Posicion& operator*= (const int& rhs) { x *= rhs; y *= rhs; return *this; }
};

inline Posicion& operator+ (Posicion lhs, const Posicion& rhs) { return lhs += rhs; }
inline Posicion& operator- (Posicion lhs, const Posicion& rhs) { return lhs -= rhs; }
inline Posicion& operator* (Posicion lhs, const int& rhs) { return lhs *= rhs; }
inline Posicion& operator* (const int& lhs, Posicion rhs) { return rhs *= lhs; }

inline bool operator== (const Posicion& lhs, const Posicion& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
inline bool operator!= (const Posicion& lhs, const Posicion& rhs) { return !(lhs == rhs); }
inline bool operator< (const Posicion& lhs, const Posicion& rhs) { return lhs.x < rhs.x&& lhs.y < rhs.y; }
inline bool operator> (const Posicion& lhs, const Posicion& rhs) { return rhs < lhs; }
inline bool operator<= (const Posicion& lhs, const Posicion& rhs) { return lhs.x <= rhs.x && lhs.y <= rhs.y; }
inline bool operator>= (const Posicion& lhs, const Posicion& rhs) { return rhs <= lhs; }

#endif