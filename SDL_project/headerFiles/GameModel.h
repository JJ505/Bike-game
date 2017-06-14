#pragma once

#include <Player.h>
#include <Enemy.h>
#include <SDL.h>
class GameModel {
private:
	Player* player;
	Enemy* enemy;
public:
	GameModel();
	//randomly spawn enemies
	bool spawnQuickTime();
	bool fireQuickTime(Uint32 pressedTime);
	
	//getters for player and enemy
	Player* getPlayer();
	Enemy* getEnemy();

};