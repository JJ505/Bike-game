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
	gBikeTexture.render(240, 190, NULL, gRenderer);

	//Update screen
	SDL_RenderPresent(gRenderer);

	++frame;
	//printf("frame is %d\n frame / 30 is %d", frame, frame/30);
	if (frame / 30 >= ROAD_FRAMES)
	{
		frame = 0;
	}

	//Free resources and close SDL
	//close();

	return frame;

}
/**
int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
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
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					
				}

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render far background to screen
				gFarBackgroundTexture.render(0, 0, NULL, gRenderer);

				//Render background texture to screen
				//slows down animation of road by rendering one of the two frames each 30 frames
				SDL_Rect* currentClip = &gSpriteClips[frame / 30];
				gRoadTexture.render((SCREEN_WIDTH - currentClip->w) / 2, (SCREEN_HEIGHT - currentClip->h) / 2, currentClip, gRenderer);

				//Render Bike' to the screen
				gBikeTexture.render( 240, 190 , NULL, gRenderer);

				//Update screen
				SDL_RenderPresent( gRenderer );

				++frame;
				//printf("frame is %d\n frame / 30 is %d", frame, frame/30);
				if (frame / 30 >= ROAD_FRAMES)
				{
					frame = 0;
				}
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
**/