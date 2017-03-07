#include <Controller.h>


View* view;
GameModel* gameModel;
Controller::Controller(View* _view, GameModel* _gameModel)
{
	view = _view;
	gameModel = _gameModel;

	
}


void Controller::startGame() {
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

				}//renders the image and returns the frame number rendered
				 //may change this
				frame = view->render(frame);
			}
		}
	}
	view->close();
	
}