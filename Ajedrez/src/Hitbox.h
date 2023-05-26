#ifndef BOUNDARYBOX_H
#define BOUNDARYBOX_H

#include "Plane.h"

class Hitbox
{
private:
	Plane ceiling;
	Plane floor;
	Plane left_wall;
	Plane right_wall;
	Plane front_wall;
	Plane back_wall;

	float height, width, depth;
	Point position;

public:
	/* CONSTRUCTOR */
	Hitbox(void) { }
	Hitbox(const float width, const float height, const float depth, const Point& position);
	Hitbox& operator = (const Hitbox& rhs);

	/* GETTERS */
	float  getHeight   (void) const { return this->height; }
	float  getWidth    (void) const { return this->width; }
	float  getDepth    (void) const { return this->depth; }
	Plane& getCeiling  (void) { return this->ceiling; }
	Plane& getFloor    (void) { return this->floor; }
	Plane& getRightWall(void) { return this->right_wall; }
	Plane& getLeftWall (void) { return this->left_wall; }
	Plane& getFrontWall(void) { return this->front_wall; }
	Plane& getBackWall (void) { return this->back_wall; }
	Point& getPosition (void) { return this->position; }

	/* SETTERS */
	void setPosition(const Point& position) { this->position = position; updateWalls(); }

	/* OTHER */
	void updateWalls(void);

	/* DRAWING */
	void render(void);
};

#endif