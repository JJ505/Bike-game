#include <View.h>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <Ltexture.h>
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
LTexture gPausedTexture;
LTexture gGameOverTexture;
LTexture gVictoryTexture;

//textures for quicktime events
LTexture gGoodQuikTexture;
LTexture gBadQuikTexture;
LTexture gUntimelyQuikTexture;
LTexture gStdQuikTexture;

//letters for quicktime events
LTexture gLetterQ;
LTexture gLetterE;

View::View() {

}

int View::getScreenWidth()
{
	return SCREEN_WIDTH;
}

int View::getScreenHeight()
{
	return SCREEN_HEIGHT;
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
		gWindow = SDL_CreateWindow( "Racer Xtreme", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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
		printf( "Failed to load player texture image!\n" );
		success = false;
	}

	//load bad guy texture
	if (!gBadGuyTexture.loadFromFile("resources/badguy.png", gRenderer))
	{
		printf("Failed to load enemy image");
		success = false;
	}
	//load paused texture
	if (!gPausedTexture.loadFromFile("resources/paused.png", gRenderer))
	{
		printf("Failed to load paused image");
		success = false;
	}
	if (!gGameOverTexture.loadFromFile("resources/gameOver.png", gRenderer))
	{
		printf("Failed to load gameOVer image");
		success = false;
	}
	if (!gVictoryTexture.loadFromFile("resources/victory.png", gRenderer))
	{
		printf("Failed to load victory image");
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
	if (!gBadQuikTexture.loadFromFile("resources/badBackgroundQuickTime.png", gRenderer))
	{
		printf("Failed to load badquiktime texture image!\n");
		success = false;
	}
	if (!gGoodQuikTexture.loadFromFile("resources/goodBackgroundQuickTime.png", gRenderer))
	{
		printf("Failed to load goodquiktime texture image!\n");
		success = false;
	}
	if (!gStdQuikTexture.loadFromFile("resources/backgroundQuickTime.png", gRenderer))
	{
		printf("Failed to load stdquiktime texture image!\n");
		success = false;
	}
	if (!gUntimelyQuikTexture.loadFromFile("resources/untimelyBackgroundQuickTime.png", gRenderer))
	{
		printf("Failed to load untimelyquiktime texture image!\n");
		success = false;
	}
	if (!gLetterQ.loadFromFile("resources/Q_BUTTON.png", gRenderer))
	{
		printf("Failed to load qbutton texture image!\n");
		success = false;
	}
	if (!gLetterE.loadFromFile("resources/E_BUTTON.png", gRenderer))
	{
		printf("Failed to load ebutton texture image!\n");
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

	++frame;
	if (frame / 30 >= ROAD_FRAMES)
	{
		frame = 0;
	}

	return frame;
}

//need function to update given character to their position
bool View::updateEntityPosition(int x, int y, int member)
{
	if (member == PLAYER)
	{
		gBikeTexture.render(x, y, NULL, gRenderer);
	}
	else if (member == ENEMY)
	{
		gBadGuyTexture.render(x, y, NULL, gRenderer);
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

//TODO later will have to better call these constants
const int STD_QUIK_TEXTURE = 0;
const int GOOD_QUIK_TEXTURE = 1;
const int BAD_QUIK_TEXTURE = 2;
const int UNTIMELY_QUIK_TEXTURE = 3;

//render the quicktime buttons
bool View::renderQuicktime(int quikTexture, int x, int y)
{
	if (quikTexture == STD_QUIK_TEXTURE) {
		gStdQuikTexture.render(x, y, NULL, gRenderer);
	}
	else if (quikTexture == GOOD_QUIK_TEXTURE) {
		gGoodQuikTexture.render(x, y, NULL, gRenderer);
	}
	else if (quikTexture == BAD_QUIK_TEXTURE) {
		gBadQuikTexture.render(x, y, NULL, gRenderer);
	}
	else if (quikTexture == UNTIMELY_QUIK_TEXTURE) {
		gUntimelyQuikTexture.render(x, y, NULL, gRenderer);
	}
	else
	{
		return false;
	}
	//SDL_RenderPresent(gRenderer);
	return true;
}

//contants for letters
const int Q_LETTER = 0;
const int E_LETTER = 1;
bool View::renderQuickTimeLetter(int quickLetter, int x, int y)
{
	if (quickLetter == Q_LETTER) {
		gLetterQ.render(x, y, NULL, gRenderer);
	}
	else if (quickLetter == E_LETTER) {
		gLetterE.render(x, y, NULL, gRenderer);
	}
	else
	{
		return false;
	}
	return true;
}

void View::renderPauseScreen()
{
	gPausedTexture.render(50, 50, NULL, gRenderer);
}

void View::renderGameOverScreen()
{
	gGameOverTexture.render(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 80, NULL, gRenderer);
}

void View::renderVictoryScreen()
{
	gVictoryTexture.render(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 80, NULL, gRenderer);
}