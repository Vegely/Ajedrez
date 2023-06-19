#include "Entity.h"

/* CONSTRUCTOR */
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
	//std::cout << "Entity " << getName() << " created." << std::endl;
}

Entity::Entity(const Point& position, const std::string& name) :
	position(position),
	velocity({ 0, 0, 0 }),
	acceleration({ 0, 0, 0 }),
	name(name)
{
	//std::cout << "Entity " << getName() << " created." << std::endl;
}

Entity::Entity(const Entity& e) :
	position(e.position),
	velocity(e.velocity),
	acceleration(e.acceleration),
	name(e.name)
{
	//std::cout << "Entity " << getName() << " created from copy." << std::endl;
}

/* DESTRUCTOR */
Entity::~Entity(void)
{
	//std::cout << "Entity " << getName() << " destroyed." << std::endl;
}

/* GETTERS */
Point Entity::getPosition(void) const
{
	//std::cout << "Got position " << this->position << "." << std::endl;
	return this->position;
}

void Entity::getPosition(Point* pos)
{
	//std::cout << "Got position " << this->position << "." << std::endl;
	*pos = this->position;
}

Point Entity::getVelocity(void) const
{
	//std::cout << "Got velocity " << this->velocity << "." << std::endl;
	return this->velocity;
}

void Entity::getVelocity(Point* pos)
{
	std::cout << "Got velocity " << this->velocity << "." << std::endl;
	*pos = this->velocity;
}

Point Entity::getAcceleration(void) const
{
	std::cout << "Got acceleration " << this->acceleration << "." << std::endl;
	return this->acceleration;
}

void Entity::getAcceleration(Point* pos)
{
	std::cout << "Got acceleration " << this->acceleration << "." << std::endl;
	*pos = this->acceleration;
}

std::string Entity::getName(void) const
{
	return this->name;
}

/* SETTERS */
void Entity::setPosition(const Point& pt)
{
	//std::cout << "Position of entity " << this->name << " set to " << pt << "." << std::endl;
	this->position = pt;
}

void Entity::setPosition(const float x, const float y, const float z)
{
	Point pt = { x, y, z };
	//std::cout << "Position of entity " << this->name << " set to " << pt << "." << std::endl;
	this->position = pt;
}

void Entity::setVelocity(const Point& pt)
{
	//std::cout << "Velocity of entity " << this->name << " set to " << pt << "." << std::endl;
	this->velocity = pt;
}

void Entity::setVelocity(const float x, const float y, const float z)
{
	Point pt = { x, y, z };
	//std::cout << "Velocity of entity " << this->name << " set to " << pt << "." << std::endl;
	this->velocity = pt;
}

void Entity::setAcceleration(const Point& pt)
{
	std::cout << "Acceleration of entity " << this->name << " set to " << pt << "." << std::endl;
	this->acceleration = pt;
}

void Entity::setAcceleration(const float x, const float y, const float z)
{
	Point pt = { x, y, z };
	std::cout << "Acceleration of entity " << this->name << " set to " << pt << "." << std::endl;
	this->acceleration = pt;
}

void Entity::setName(const std::string& new_name)
{
	this->name = new_name;
}

/* MOVEMENTS */
void Entity::move(const Point& vel)
{
	std::cout << "Velocity of " << this->name << " set to " << vel << "." << std::endl;
	this->velocity = vel;
}

void Entity::endMove(int key)
{
	if (this->velocity != Point::zero)
		this->setVelocity(Point::zero);

	//std::cout << "Entity key released." << std::endl;
}

void Entity::warp(const Point& pt)
{
	setPosition(pt);
}

/* MOVEMENT */
void Entity::movement(const float time)
{
	this->position = this->position + this->velocity * time + this->acceleration * (0.5f * time * time);
	this->velocity = this->velocity + this->acceleration * time;
}

/* PRINTERS */
std::ostream& Entity::printParameters(std::ostream& str) const
{
	str << "Data for entity: " << getName() << std::endl;
	str << "Position: " << this->position << std::endl;
	str << "Velocity: " << this->velocity << std::endl;
	str << "Acceleration: " << this->acceleration << std::endl;

	return str;
}

std::ostream& Entity::printParameters(const Entity& e, std::ostream& str)
{
	return e.printParameters(str);
}

std::ostream& Entity::printPosition(std::ostream& str) const
{
	str << "Position for entity: " << getName() << std::endl;
	str << this->position << std::endl << std::endl;
	return str;
}

std::ostream& Entity::printPosition(const Entity& e, std::ostream& str)
{
	return e.printPosition(str);
}

std::ostream& Entity::printVelocity(std::ostream& str) const
{
	str << "Velocity for entity: " << getName() << std::endl;
	str << this->velocity << std::endl << std::endl;
	return str;
}

std::ostream& Entity::printVelocity(const Entity& e, std::ostream& str)
{
	return e.printVelocity(str);
}

std::ostream& Entity::printAcceleration(std::ostream& str) const
{
	str << "Acceleration for entity: " << getName() << std::endl;
	str << this->acceleration << std::endl << std::endl;
	return str;
}

std::ostream& Entity::printAcceleration(const Entity& e, std::ostream& str)
{
	return e.printAcceleration(str);
}