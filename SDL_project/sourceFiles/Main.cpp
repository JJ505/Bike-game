#include <View.h>
#include <GameModel.h>
#include <Controller.h>


//TODO
/**
	draw enemy or some event to show up on screen
	have player health diminshed for bad response time to quiktime
	animate events for varying quiktime levels
	could add score 
	add multiple enemies(probably at most two)
	add randomized enemies 
	//quiktime will most likely be a int instead of bool
	//quiktime will also have to be attached to enemy and random keys
**/

int main(int argc, char* args[])
{
	View* view = new View();
	GameModel* gameModel = new GameModel();
	Controller* controller = new Controller(view, gameModel);
	controller->startGame();

	return 0;
}