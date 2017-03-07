#include <View.h>
#include <GameModel.h>
#include <Controller.h>


int main(int argc, char* args[])
{
	View* view = new View();
	GameModel* gameModel = new GameModel();
	Controller* controller = new Controller(view, gameModel);
	controller->startGame();

	return 0;
}