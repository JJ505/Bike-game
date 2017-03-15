#pragma once
class Enemy
{
private:
	int x;
	int y;
public:

	Enemy::Enemy(int x, int y);

	int getX();

	int getY();
	//have key press events for when enemy comes near player?
};
