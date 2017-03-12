#include <Controller.h>


View* view;
GameModel* gameModel;
Controller::Controller(View* _view, GameModel* _gameModel)
{
	view = _view;
	gameModel = _gameModel;
	
}


void Controller::startGame() {
	Uint32 initiatedQuickTime = 0;
	int quickRenderValue = NO_QUIK_TEXTURE;
	if (!view->init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!view->loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;
			bool quickTime = false;
			//Event handler
			SDL_Event e;

			//current animation frame
			int frame = 0;

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					if (quickTime && e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_q)
					{
						quickTime = false;
						//signal gameModel when quiktime buttone clicked with timing
						//gamemodel will update the player in negative or positive manner
						if (gameModel->fireQuickTime(SDL_GetTicks())) {
							quickRenderValue = GOOD_QUIK_TEXTURE;
							
						}
						else
						{
							quickRenderValue = UNTIMELY_QUIK_TEXTURE;
						}
					}
				}
				if (SDL_GetTicks() - initiatedQuickTime > 1700) {
					quickTime = false;
					quickRenderValue = NO_QUIK_TEXTURE;
					//show screen flash red?
				}
				else if (quickTime && SDL_GetTicks() - initiatedQuickTime > 1200) {
					printf("decidedly Too late\n");
					quickRenderValue = BAD_QUIK_TEXTURE;
				}

				//notifies gameModel to possible spawnEnemies
				if (gameModel->spawnEnemies())
				{
					//there may be multiple quicktime events?
					quickTime = true;
					quickRenderValue = STD_QUIK_TEXTURE;

					//show image of event firing
					initiatedQuickTime = SDL_GetTicks();
					//the view will also be updated to show a key on the screen
				}
				//renders the image and returns the frame number rendered
				frame = view->render(frame);
				view->renderQuicktime(quickRenderValue);
				view->updateRender();
			}
		}
	}
	view->close();
	
}