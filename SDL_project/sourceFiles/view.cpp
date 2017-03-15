/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <View.h>

//add header files of other class objects made and include in here
//practice first with taking out ltexture class
//Screen dimension constants
const int SCREEN_WIDTH = 1100;
const int SCREEN_HEIGHT = 700;


//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

const int ROAD_FRAMES = 2;
//Scene Sprites
SDL_Rect gSpriteClips[ROAD_FRAMES];

//Scene textures
LTexture gBikeTexture;
LTexture gRoadTexture;
LTexture gFarBackgroundTexture;
LTexture gBadGuyTexture;

//textures for quicktime events
LTexture gGoodQuikTexture;
LTexture gBadQuikTexture;
LTexture gUntimelyQuikTexture;
LTexture gStdQuikTexture;

View::View() {

}

bool View::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsyncd renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool View::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load Bike' texture
	if( !gBikeTexture.loadFromFile( "resources/bike.png" , gRenderer) )
	{
		printf( "Failed to load Bike' texture image!\n" );
		success = false;
	}

	//load bad guy texture
	if (!gBadGuyTexture.loadFromFile("resources/badguy.png", gRenderer))
	{
		printf("Failed to load badguy image");
		success = false;
	}
	
	//Load background texture
	if( !gRoadTexture.loadFromFile( "resources/road.png" , gRenderer) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}
	else
	{
		//sets top image of sprite road
		gSpriteClips[0].x = 0;
		gSpriteClips[0].y = 0;
		gSpriteClips[0].w = 1100;
		gSpriteClips[0].h = 700;

		//sets bottom image of sprite road
		gSpriteClips[1].x = 1100;
		gSpriteClips[1].y = 0;
		gSpriteClips[1].w = 1100;
		gSpriteClips[1].h = 700;

	}
	if (!gFarBackgroundTexture.loadFromFile("resources/akiraBack.png", gRenderer))
	{
		printf("Failed to load farbackground texture image!\n");
		success = false;
	}


	//loads quicktime textures
	if (!gBadQuikTexture.loadFromFile("resources/badquiktime.png", gRenderer))
	{
		printf("Failed to load badquiktime texture image!\n");
		success = false;
	}
	if (!gGoodQuikTexture.loadFromFile("resources/goodquiktime.png", gRenderer))
	{
		printf("Failed to load goodquiktime texture image!\n");
		success = false;
	}
	if (!gStdQuikTexture.loadFromFile("resources/stdquiktime.png", gRenderer))
	{
		printf("Failed to load stdquiktime texture image!\n");
		success = false;
	}
	if (!gUntimelyQuikTexture.loadFromFile("resources/untimelyquiktime.png", gRenderer))
	{
		printf("Failed to load untimelyquiktime texture image!\n");
		success = false;
	}

	return success;
}

void View::close()
{
	//Free loaded images
	gBikeTexture.free();
	gRoadTexture.free();
	gFarBackgroundTexture.free();

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
//change this to render, and the main game loop will call these commands when necessary
//render returns the frame that was last renderered
int View::render(int frame)
{
	//Clear screen
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	//Render far background to screen
	gFarBackgroundTexture.render(0, 0, NULL, gRenderer);

	//Render background texture to screen
	//slows down animation of road by rendering one of the two frames each 30 frames
	SDL_Rect* currentClip = &gSpriteClips[frame / 30];
	gRoadTexture.render((SCREEN_WIDTH - currentClip->w) / 2, (SCREEN_HEIGHT - currentClip->h) / 2, currentClip, gRenderer);

	//Render Bike' to the screen
	//gBikeTexture.render(240, 190, NULL, gRenderer);

	//gBadGuyTexture.render(140, 230, NULL, gRenderer);
	//Update screen
	//SDL_RenderPresent(gRenderer);

	++frame;
	if (frame / 30 >= ROAD_FRAMES)
	{
		frame = 0;
	}

	//Free resources and close SDL
	//close();

	return frame;

}

//need function to update given character to their position
bool View::updateEntityPosition(int x, int y, int entity)
{
	if (entity == PLAYER)
	{
		printf("rendering player\n");
		gBikeTexture.render(240, 190, NULL, gRenderer);
	}
	else if (entity == ENEMY)
	{
		printf("rendering bad guy\n");
		gBadGuyTexture.render(140, 230, NULL, gRenderer);
	}
	else
	{
		return false;
	}
	return true;

}

bool View::updateRender()
{
	SDL_RenderPresent(gRenderer);
	return true;
}

//later will have to better call these constants
const int STD_QUIK_TEXTURE = 0;
const int GOOD_QUIK_TEXTURE = 1;
const int BAD_QUIK_TEXTURE = 2;
const int UNTIMELY_QUIK_TEXTURE = 3;
//render the quicktime buttons
bool View::renderQuicktime(int quikTexture)
{
	if (quikTexture == STD_QUIK_TEXTURE) {
		gStdQuikTexture.render(250, 200, NULL, gRenderer);
	}
	else if (quikTexture == GOOD_QUIK_TEXTURE) {
		gGoodQuikTexture.render(250, 200, NULL, gRenderer);
	}
	else if (quikTexture == BAD_QUIK_TEXTURE) {
		gBadQuikTexture.render(250, 200, NULL, gRenderer);
	}
	else if (quikTexture == UNTIMELY_QUIK_TEXTURE) {
		gUntimelyQuikTexture.render(250, 200, NULL, gRenderer);
	}
	else
	{
		return false;
	}
	//SDL_RenderPresent(gRenderer);
	return true;
}