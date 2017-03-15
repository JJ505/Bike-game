#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <Player.h>
#include <Enemy.h>
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