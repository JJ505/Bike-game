#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <Ltexture.h>

//#include <Controller.h>

class View
{
public: 
	View();

	int render(int frame);

	//Starts up SDL and creates window
	bool init();

	//Frees media and shuts down SDL
	void close();

	//Loads media
	bool loadMedia();

	//renders quicktime events to renderer
	bool renderQuicktime(int quikTexture);
	
	//wrapper method to update grender
	bool updateRender();

	bool updateEntityPosition(int x, int y, int entity);
};

enum Entity
{
	player = 1,
	badguy = 2
};