#include <Enemy.h>
Enemy::Enemy(int x, int y)
{
	this->x = x;
	this->y = y;

}

int Enemy::getX() {
	return x;
}

int Enemy::getY() {
	return y;
}

void Enemy::setX(int x)
{
	this->x = x;
}
void Enemy::moveEnemyForward(int movementSpeed) {
	this->x += movementSpeed;
}