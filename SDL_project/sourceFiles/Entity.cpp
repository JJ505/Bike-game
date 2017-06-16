#include <Entity.h>
#include <string>

Entity::Entity(int x, int y)
{
	this->x = x;
	this->y = y;
}

int Entity::getX() {
	return x;
}

int Entity::getY() {
	return y;
}

void Entity::setX(int x)
{
	this->x = x;
}

void Entity::moveEntityForward(int movementSpeed) {
	this->x += movementSpeed;

}
