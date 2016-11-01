#include "EndingPong.h"



EndingPong::EndingPong(SDL_Renderer* renderer, int screenWidth, int screenHeight) : mRenderer(renderer), mScreenWidth(screenWidth), mScreenHeight(screenHeight)
{
}


EndingPong::~EndingPong()
{
	mRenderer = NULL;
}

void EndingPong::handle_events(SDL_Event& event, int& nextState)
{

}

void EndingPong::logic(int& nextState)
{

}

void EndingPong::render()
{

}

void EndingPong::loadMedia()
{

}