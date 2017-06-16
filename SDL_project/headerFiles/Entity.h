#pragma once
#ifndef ENTITY_H
#define ENTITY_H
class Entity {

protected:
	int x;
	int y;

public:
	Entity::Entity(int x, int y);
	int getX();
	int getY();
	void moveEntityForward(int movementSpeed);
	void setX(int x);

};
#endif