#pragma once

#include "GameState.h"

#include "SDLTexture.h"
#include "SDLBitmapFont.h"

class TitlePong : public GameState
{
public:
	TitlePong(SDL_Renderer* renderer, int screenWidth, int screenHeight);
	~TitlePong();

	//Main loop functions
	void handle_events(SDL_Event& event, int& nextState);
	void logic(int& nextState);
	void render();

private:
	void loadMedia();

	//Get the reference of the renderer
	SDL_Renderer* mRenderer = NULL;

	int mScreenWidth;
	int mScreenHeight;

	//Scene texts textures
	SDLTexture mBitmapTexture;
	SDLBitmapFont mBitmapFont;
};

