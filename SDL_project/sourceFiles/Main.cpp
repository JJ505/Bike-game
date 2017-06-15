#include <View.h>
#include <GameModel.h>
#include <Controller.h>


//TODO
/**
	
	add win condition/animation
	implement main menu screen
	fix so pause pasues game time as well;

	animation
	eventually have player be a little animated
	add some lighting effects?
	make road look nicer

	possible additions
	===========================
	add a minimap that shows the characters and progress on map?
	make map big with multiple portions and backgrounds
	show a calculation of the projected outcome of the match with probability?
	make the enemy gain a base + catchup distance
	
	have effects or some animation to keep track of bonuses
	have a bonus streak
	have more than just the "q" quicktime button
	add obstacles that will be jumped over or destroyed


**/

int main(int argc, char* args[])
{
	View* view = new View();
	GameModel* gameModel = new GameModel();
	Controller* controller = new Controller(view, gameModel);
	controller->startGame();

	return 0;
}