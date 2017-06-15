#pragma once



enum Entity
{
	PLAYER = 1,
	ENEMY = 2
};

class View
{
public: 
	View();

	int getScreenWidth();
	int getScreenHeight();

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

	//render the entity at position
	bool updateEntityPosition(int x, int y, int entity);

	//render the quicktime letter
	bool renderQuickTimeLetter(int quickLetter, int x, int y);

	//render pause screen
	bool renderPauseScreen();
};

