#pragma once
#include <View.h>
#include <GameModel.h>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

class Controller
{
public:
	Controller(View* view, GameModel* gameModel);
	
	void startGame();

};