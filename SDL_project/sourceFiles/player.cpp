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

void Player::setX(int x)
{
	this->x = x;
}

void Player::movePlayerForward(int movementSpeed) {
	this->x += movementSpeed;

}

int Player::damagePlayerHealth(int reduction)
{
	this->health -= reduction;
	printf("reduced health to %d\n", this->health);
	return 1;
}

int Player::getHealth()
{
	return this->health;
}
