#pragma once
#ifndef PLAYER_H
#define PLAYER_H

class Player 
{
private:
	int x;
	int y;
	int health;
public:

	Player::Player(int x, int y);
	int getX();
	int getY();
	int damagePlayerHealth(int reduction);
	int getHealth();
	void movePlayerForward(int movementSpeed);
	void setX(int x);
	//have key press events for when enemy comes near player?
};
#endif