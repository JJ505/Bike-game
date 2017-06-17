#pragma once
//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#ifndef TEXTURE_H
#define TEXTURE_H
class Texture
{
public:
	//Initializes variables
	Texture();

	//Deallocates memory
	~Texture();

	//Loads image at specified path
	bool loadFromFile(std::string path, SDL_Renderer* gRenderer);

	//Deallocates texture
	void free();

	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = NULL, SDL_Renderer* gRenderer = NULL);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
};
#endif