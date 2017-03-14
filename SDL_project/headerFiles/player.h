#pragma once
#include <Ltexture.h>
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
	//have key press events for when enemy comes near player?
};