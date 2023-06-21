#include "Entity.h"

Entity::Entity(void) :
	position({ 0 }),
	velocity({ 0 }),
	acceleration({ 0 }),
	name("")
{

}

Entity::Entity(const std::string& name) :
	position({0, 0, 0}), 
	velocity({ 0, 0, 0 }),
	acceleration({ 0, 0, 0 }),
	name(name)
{

}

Entity::Entity(const Point& position, const std::string& name) :
	position(position),
	velocity({ 0, 0, 0 }),
	acceleration({ 0, 0, 0 }),
	name(name)
{

}

Entity::Entity(const Entity& e) :
	position(e.position),
	velocity(e.velocity),
	acceleration(e.acceleration),
	name(e.name)
{

}

void Entity::movement(const float time)
{
	this->position = this->position + this->velocity * time + this->acceleration * (0.5f * time * time);
	this->velocity = this->velocity + this->acceleration * time;
}