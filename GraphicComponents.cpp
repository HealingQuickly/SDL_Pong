#include "GraphicComponents.h"



GraphicComponents::GraphicComponents()
{
}

void GraphicComponents::updateRender(Quad* quad, SDL_Renderer* renderer)
{
	//Render red filled quad
	SDL_Rect fillRect = { quad->mX, quad->mY, quad->mW, quad->mH };
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(renderer, &fillRect);
}