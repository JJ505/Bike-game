#pragma once
#include <View.h>
#include <GameModel.h>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

const int STD_QUIK_TEXTURE = 0;
const int GOOD_QUIK_TEXTURE = 1;
const int BAD_QUIK_TEXTURE = 2;
const int UNTIMELY_QUIK_TEXTURE = 3;
const int NO_QUIK_TEXTURE = 4;

const int PLAYER_ENTITY = 1;
const int ENEMY_ENTITY = 2;
class Controller
{
public:
	Controller(View* view, GameModel* gameModel);
	
	void startGame();

};