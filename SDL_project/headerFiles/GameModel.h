#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

class GameModel {
public:
	GameModel();
	//randomly spawn enemies
	bool spawnEnemies();
	bool fireQuickTime(Uint32 pressedTime);
};