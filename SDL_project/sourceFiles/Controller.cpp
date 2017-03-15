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
			bool pressedQuickTime = false;
			bool badQuickTime = false;
			//Event handler
			SDL_Event e;

			//current animation frame
			int frame = 0;

			//While application is running
			while (!quit)
			{
				Player* player = gameModel->getPlayer();
				Enemy* enemy = gameModel->getEnemy();
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
						pressedQuickTime = true;
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
				//no reaction
				if (quickTime && SDL_GetTicks() - initiatedQuickTime > 1700)
				{
					pressedQuickTime = false;
					quickTime = false;
					badQuickTime = false;
					quickRenderValue = NO_QUIK_TEXTURE;
				}
				//too late reaction
				else if (!badQuickTime && !pressedQuickTime && quickTime && SDL_GetTicks() - initiatedQuickTime > 1200)
				{
					badQuickTime = true;
					printf("decidedly Too late\n");
					quickRenderValue = BAD_QUIK_TEXTURE;
					player->damagePlayerHealth(10);
				}

				//notifies gameModel to possible spawnEnemies
				if (gameModel->spawnQuickTime())
				{
					//there may be multiple quicktime events?
					quickTime = true;
					quickRenderValue = STD_QUIK_TEXTURE;

					//show image of event firing
					initiatedQuickTime = SDL_GetTicks();
				}
				//renders the image and returns the frame number rendered
				frame = view->render(frame);
				//renders the updated positions of player and enemy
				view->updateEntityPosition(player->getX(), player->getY(), PLAYER_ENTITY);
				view->updateEntityPosition(enemy->getX(), enemy->getY(), ENEMY_ENTITY);
				view->renderQuicktime(quickRenderValue, enemy->getX()+50, enemy->getY()+30);
				view->updateRender();
			}
		}
	}
	view->close();
	
}