#pragma once

#include <SDL.h>

#include "Quad.h"

class GraphicComponents
{
public:
	GraphicComponents();

	void updateRender(Quad* quad, SDL_Renderer* renderer);
};

