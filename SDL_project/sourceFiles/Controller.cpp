#include <Controller.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

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
			
			//quicktime actions
			bool quickTime = false;
			bool badQuickTime = false;
			int quickTimeReaction = 0;
			int quicktimeButton = -1;
			bool pressedCorrectButton = false;
			bool gamePaused = false;

			bool gameOver = false;
			bool playerVictory = false;

			//time values
			Uint32 pausedTime = 0;
			//Event handler
			SDL_Event e;

			//current animation frame
			int frame = 0;

			//While application is running
			while (!quit)
			{
				Entity* player = gameModel->getPlayer();
				Entity* enemy = gameModel->getEnemy();
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
					{
						//paused game
						gamePaused = true;
						Uint32 pausedStartTime = SDL_GetTicks();

						SDL_Event p;
						while (gamePaused)
						{
							while (SDL_PollEvent(&p) != 0)
							{
								if (p.type == SDL_QUIT)
								{
									quit = true;
									gamePaused = false;
								}
								if (p.type == SDL_KEYDOWN && p.key.keysym.sym == SDLK_ESCAPE)
								{
									//unpause game
									gamePaused = false;
									pausedTime = SDL_GetTicks() - pausedStartTime;

								}
							}
							//draw paused letters in the middle of the screen
							view->renderPauseScreen();
							view->updateRender();
						}
					}

					//only set the bools of what occurs. after some amount of time award the distances
					if (quickTime && e.type == SDL_KEYDOWN)
					{
						//signal gameModel when quiktime button clicked with timing
						//gamemodel will update the player in negative or positive manner
						if (quicktimeButton == 0 && e.key.keysym.sym == SDLK_q)
						{
							pressedCorrectButton = true;

						}
						else if (quicktimeButton == 1 && e.key.keysym.sym == SDLK_e)
						{
							pressedCorrectButton = true;
						}
						else
						{
							pressedCorrectButton = false;
						}
						if (pressedCorrectButton)
						{
							if (gameModel->fireQuickTime(SDL_GetTicks())) {
								quickRenderValue = GOOD_QUIK_TEXTURE;
								quickTimeReaction = 1;
							}
							else if (!quickTimeReaction)
							{
								quickRenderValue = UNTIMELY_QUIK_TEXTURE;
								quickTimeReaction = 2;
							}
						}
						
					}
				}
				//reset reaction bools
				int timeLimit = 1700;
				if (quickTime)
				{
					//if the quicktime has finished
					if (SDL_GetTicks() - initiatedQuickTime - pausedTime > timeLimit)
					{
						quickTime = false;
						badQuickTime = false;
						pressedCorrectButton = false;
						quickRenderValue = NO_QUIK_TEXTURE;
						switch (quickTimeReaction) {
						case 1:
							player->moveEntityForward(50);
							break;
						case 2:
							enemy->moveEntityForward(60);
							break;
						case 3:
							enemy->moveEntityForward(75);
							break;
						default:
							break;
						}
						quickTimeReaction = 0;
						quicktimeButton = -1;
					}
					//or if the time has not finished then a bad quicktime needs to be recorded
					else if (SDL_GetTicks() - initiatedQuickTime - pausedTime > 1200)
					{
						if (!quickTimeReaction)
						{
							badQuickTime = true;
							printf("decidedly Too late\n");
							quickRenderValue = BAD_QUIK_TEXTURE;
							quickTimeReaction = 3;
						}
					}
				}
				
				//notifies gameModel to possibly spawn quick time event
				if (gameModel->spawnQuickTime())
				{
					//set quicktime event to be true(happening)
					quickTime = true;
					pausedTime = 0;
					//get random quicktime event
					quicktimeButton = rand() % QUICK_BUTTON_TEXTURES;
					quickRenderValue = STD_QUIK_TEXTURE;

					//show image of event firing
					initiatedQuickTime = SDL_GetTicks();
				}


				//renders the image and returns the frame number rendered
				frame = view->render(frame);
				
				//renders the updated positions of player and enemy
				view->updateEntityPosition(player->getX(), player->getY(), PLAYER_ENTITY);
				view->updateEntityPosition(enemy->getX(), enemy->getY(), ENEMY_ENTITY);
				view->renderQuicktime(quickRenderValue, player->getX()+50, player->getY()+30);
				view->renderQuickTimeLetter(quicktimeButton, player->getX() + 50, player->getY() + 30);
				
				//checks if game is over
				gameOver = gameModel->checkForGameOver(view->getScreenWidth());
				//checks if player victory
				playerVictory = gameModel->checkForPlayerVictory();
				while (gameOver)
				{
					//press r to restart
					SDL_Event t;

					while (SDL_PollEvent(&t) != 0)
					{
						if (t.type == SDL_QUIT)
						{
							quit = true;
							gameOver = false;
						}
						if (t.key.keysym.sym == SDLK_r && t.type == SDL_KEYDOWN)
						{
							//reset game
							gameOver = false;
							gameModel->resetPlayerAndEnemy();

						}
					}
					if (playerVictory)
					{
						//show victory screen
						view->renderVictoryScreen();
					}
					else
					{
						//show defeat screen
						view->renderGameOverScreen();
					}
					gameModel->resetVictory();
					
					view->updateRender();
				}

				view->updateRender();
			}
		}
	}
	view->close();
	
}