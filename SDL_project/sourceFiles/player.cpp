#include <Player.h>
#include <string>

Player::Player(int x, int y)
{
	this->x = x;
	this->y = y;
	this->health = 100;

}

int Player::getX() {
	return x;
}

int Player::getY() {
	return y;
}

int Player::damagePlayerHealth(int reduction)
{
	this->health -= reduction;
	printf("reduced health to %d\n", this->health);
	return 1;
}
