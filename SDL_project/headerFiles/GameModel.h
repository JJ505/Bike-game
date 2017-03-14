#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <Player.h>

class GameModel {
private:
	Player* player;

public:
	GameModel();
	//randomly spawn enemies
	bool spawnEnemies();
	bool fireQuickTime(Uint32 pressedTime);
	Player* getPlayer();
};