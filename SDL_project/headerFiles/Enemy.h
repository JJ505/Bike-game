#pragma once
#ifndef ENEMY_H
#define ENEMY_H
class Enemy
{
private:
	int x;
	int y;
public:

	Enemy::Enemy(int x, int y);
	int getX();
	int getY();
	void moveEnemyForward(int movementSpeed);
	void setX(int x);
	//have key press events for when enemy comes near player?
};
#endif