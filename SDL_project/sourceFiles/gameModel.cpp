//all the game logic and model of the game here
//lets have quick time events!
#include <GameModel.h>

int spawnedEnemies;
Uint32 timeSinceLastSpawn = 0;
GameModel::GameModel()
{
	spawnedEnemies = 0;
	//eventually show quicktime events and have them rotate

}

bool GameModel::spawnEnemies() {
	if (SDL_GetTicks() - timeSinceLastSpawn > 5000) {
		printf("time since last spawned %d\n", timeSinceLastSpawn);
		timeSinceLastSpawn = SDL_GetTicks();
		printf("time since last spawned is now %d\n", timeSinceLastSpawn);
		return true;
	}
	//if spawned
	//if not enough enemies and time since last spawn 
	//is long like 10-20 sec, then randomize the spawn chance and spawn
	//otherwise if longer than 30 sec then spawn process anyways
	//return true if enemies is spawned
	//return false if no emeies spawned.
	return false;
}
//takes in the pressed time of when the quick time event was pressed
//also adjusts health of player
bool GameModel::fireQuickTime(Uint32 pressedTime)
{
	//if approximately pressed within one second
	if (pressedTime - timeSinceLastSpawn > 0 && pressedTime - timeSinceLastSpawn < 1000) 
	{
		//update player experience or something positive
		printf("great job pressed correctly\n");
		return true;
	}
	printf("way too late bro\n");
	//else negatively impact player
	return false;
}



