#pragma once

#include <Player.h>
#include <Enemy.h>
#include <SDL.h>

#ifndef GAMEMODEL_H
#define GAMEMODEL_H
class GameModel {
private:
	Player* player;
	Enemy* enemy;
	bool victory;

public:
	GameModel();
	//randomly spawn enemies
	bool spawnQuickTime();
	bool fireQuickTime(Uint32 pressedTime);
	
	//getters for player and enemy
	Player* getPlayer();
	Enemy* getEnemy();

	//reset player and enemy to original positions
	bool resetPlayerAndEnemy();

	//check for game over
	bool checkForGameOver(int viewScreenWidth);

	//check for player victory
	bool checkForPlayerVictory();

};
#endif