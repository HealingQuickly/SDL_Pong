#pragma once

#include "GameState.h"

#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "SDLTexture.h"

class IntroPong : public GameState
{
public:
	static const int DISPLAY_OFFSET = 50;

	IntroPong(SDL_Renderer* renderer, int screenWidth, int screenHeight);
	~IntroPong();

	//Main loop functions
	void handle_events(SDL_Event& event, int& nextState);
	void logic(int& nextState);
	void render();


private:
	void loadMedia();

	int mScreenWidth;
	int mScreenHeight;

	TTF_Font *mFont = NULL;
	SDLTexture mTextTexture;
	SDLTexture mEnterTexture;
	SDLTexture mMusicCredit;

	Uint8 alpha = 255;
	Uint8 alphaOffset = 0;

	//The music that will be played
	Mix_Music *mMusic = NULL;

	//Get the reference of the renderer
	SDL_Renderer* mRenderer = NULL;
};

