#ifndef CAMERA_H
#define CAMERA_H

#include "Globals.h"

class Camera
{
private:
	Point position;
	Point speed;
	Point look_at;
	Rotation rotation;

public:
	/* CONSTRUCTOR */
	Camera(void) = delete;
	Camera(const Point& position);
	Camera(const Point& position, const Point& look_at);

	/* DESTRUCTOR */
	virtual ~Camera(void);

	/* GETTERS */
	Point getPosition(void) const;
	Point getSpeed(void) const;
	Point getLookAt(void) const;

	/* SETTERS */
	void setPosition(const Point& pos);
	void setSpeed(const Point& sp);
	void setLookAt(const Point& pt);

	/* MOVEMENT (OnTimer) */
	void movement(const float time);

	/* PRINTERS */
	std::ostream& printPosition(std::ostream& str) const;
	std::ostream& printLookAt(std::ostream& str) const;

	/* CAMERA UPDATE (for resetting and adjusting camera position and/or rotation) */
	void update(void);
};

#endif // !CAMERA_H