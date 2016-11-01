#pragma once

#include "GameState.h"

class EndingPong : public GameState
{
public:
	EndingPong(SDL_Renderer* renderer, int screenWidth, int screenHeight);
	~EndingPong();

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
};

