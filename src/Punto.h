#ifndef _PUNTO__H_
#define _PUNTO__H_

#include <iostream>
class Punto
{
public:
	float x = 0, y = 0;

	inline Punto& operator- () { x = -x; y = -y; return *this; }
	inline Punto& operator+= (const Punto& rhs) { x += rhs.x; y += rhs.y; return *this; }
	inline Punto& operator-= (Punto rhs) { *this += (-rhs); return *this; }
	inline Punto& operator*= (const int& rhs) { x *= rhs; y *= rhs; return *this; }
};

inline Punto operator+ (Punto lhs, const Punto& rhs) { return lhs += rhs; }
inline Punto operator- (Punto lhs, const Punto& rhs) { return lhs -= rhs; }
inline Punto operator* (Punto lhs, const int& rhs) { return lhs *= rhs; }
inline Punto operator* (const int& lhs, Punto rhs) { return rhs *= lhs; }

inline bool operator== (const Punto& lhs, const Punto& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
inline bool operator!= (const Punto& lhs, const Punto& rhs) { return !(lhs == rhs); }
inline bool operator< (const  Punto& lhs, const Punto& rhs) { return lhs.x < rhs.x && lhs.y < rhs.y; }
inline bool operator> (const  Punto& lhs, const Punto& rhs) { return rhs < lhs; }
inline bool operator<= (const Punto& lhs, const Punto& rhs) { return lhs.x <= rhs.x && lhs.y <= rhs.y; }
inline bool operator>= (const Punto& lhs, const Punto& rhs) { return rhs <= lhs; }
inline double distancia(const Punto p1, const Punto p2) { return sqrtf((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)); }

#endif // !_PUNTO__H_