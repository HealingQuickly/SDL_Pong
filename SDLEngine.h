#pragma once

#include <stdio.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

class SDLEngine
{
public:
	SDLEngine(); // default SDLEngine constructor
	SDLEngine(int screenWidth, int screenHeight);

	bool initSDL();
	void closeSDL();

	int getScreenWidth() const { return mScreenWidth; }
	int getScreenHeight() const { return mScreenHeight; }
	SDL_Renderer* getRenderer() const { return mRenderer; }

private:
	SDL_Window* mWindow = NULL;
	SDL_Renderer* mRenderer = NULL;

	int mScreenWidth = 0;
	int mScreenHeight = 0;
};