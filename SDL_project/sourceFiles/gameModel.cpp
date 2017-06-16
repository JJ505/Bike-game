//all the game logic and model of the game here
//lets have quick time events!
#include <GameModel.h>
#include <SDL_image.h>
#include <string>
int spawnedEnemies;
Uint32 timeSinceLastSpawn = 0;

//Player* player;
GameModel::GameModel()
{
	spawnedEnemies = 0;
	//eventually show quicktime events and have them rotate
	player = new Player(240, 190);
	enemy = new Enemy(140, 330);
	victory = false;
}

Player* GameModel::getPlayer()
{
	return player;
}

Enemy* GameModel::getEnemy()
{
	return enemy;
}

bool GameModel::resetPlayerAndEnemy()
{
	player->setX(240);
	enemy->setX(140);
	return true;
}

bool GameModel::spawnQuickTime() {
	//spawn if its been longer than 5 seconds since last event
	//also possible random chance to spawn
	//event is something is drawn on screen, if not pressed in time then damage player
	
	if (SDL_GetTicks() - timeSinceLastSpawn > 5000) {
		printf("time since last spawned %d\n", timeSinceLastSpawn);
		timeSinceLastSpawn = SDL_GetTicks();
		printf("time since last spawned is now %d\n", timeSinceLastSpawn);
		return true;
	}
	//return true if enemies is spawned
	//return false if no emeies spawned.
	return false;
}
//takes in the pressed time of when the quick time event was pressed
//also adjusts health of player
bool GameModel::fireQuickTime(Uint32 pressedTime)
{
	//if approximately pressed within one second
	if (pressedTime - timeSinceLastSpawn > 0 && pressedTime - timeSinceLastSpawn < 500) 
	{
		//update player experience or something positive
		printf("great job pressed correctly\n");
		return true;
	}
	printf("a little too late\n");
	//else negatively impact player
	return false;
}

//returns true if game over and false if not
bool GameModel::checkForGameOver(int viewScreenWidth)
{
	if (player->getX() >= viewScreenWidth - 200)
	{
		victory = true;
		return true;
	}
	else if (enemy->getX() >= viewScreenWidth - 200)
	{
		return true;
	}
	return false;
}

bool GameModel::checkForPlayerVictory()
{
	return victory;
}

