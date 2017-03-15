#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <Ltexture.h>


enum Entity
{
	PLAYER = 1,
	ENEMY = 2
};

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
	bool renderQuicktime(int quikTexture, int x, int y);
	
	//wrapper method to update grender
	bool updateRender();

	bool updateEntityPosition(int x, int y, int entity);
};

