#include "Hitbox.h"

Hitbox::Hitbox(const float width, const float height, const float depth, const Point& position) :
	   ceiling(width, depth),
	     floor(width, depth),
	 left_wall(depth, height),
	right_wall(depth, height),
	front_wall(width, height),
	 back_wall(width, height),
	    height(height),
	     width(width),
	     depth(depth),
	  position(position)
{
	updateWalls();
}

Hitbox& Hitbox::operator = (const Hitbox& rhs)
{ 
	this->ceiling	 = rhs.ceiling;
	this->floor		 = rhs.floor;
	this->left_wall  = rhs.left_wall;
	this->right_wall = rhs.right_wall;
	this->front_wall = rhs.front_wall;
	this->back_wall	 = rhs.back_wall;
	this->height	 = rhs.height;
	this->width		 = rhs.width;
	this->depth		 = rhs.depth;
	this->position	 = rhs.position;
	return *this;
}

void Hitbox::updateWalls(void) // Tener en cuenta que los planos se generan en el plano x-z.
{
	   ceiling.setPosition({ this->position.x,			   this->position.y + height,     this->position.z });
	     floor.setPosition({ this->position.x,			   this->position.y,		      this->position.z });
	 left_wall.setPosition({ this->position.x - width / 2, this->position.y + height / 2, this->position.z });
	right_wall.setPosition({ this->position.x + width / 2, this->position.y + height / 2, this->position.z });
	front_wall.setPosition({ this->position.x,  		   this->position.y + height / 2, this->position.z + depth / 2 });
	 back_wall.setPosition({ this->position.x,  		   this->position.y + height / 2, this->position.z - depth / 2 });

	   ceiling.updateCorners();
	     floor.updateCorners();
	 left_wall.updateCorners();
	right_wall.updateCorners();
	front_wall.updateCorners();
	 back_wall.updateCorners();

	 left_wall.rotate('z',  90.0f);
	right_wall.rotate('z', -90.0f);
	 left_wall.rotate('x',  90.0f);
	right_wall.rotate('x', -90.0f);
	front_wall.rotate('x',  90.0f);
	 back_wall.rotate('x', -90.0f);
}

void Hitbox::render(void)
{
	   ceiling.render();
	     floor.render();
	 left_wall.render();
	right_wall.render();
	front_wall.render();
	 back_wall.render();
}