#pragma once

#include "Quad.h"
#include <SDL.h>

class InputComponents
{
public:
	InputComponents() {};

	virtual void updateInput(Quad* self, SDL_Event* e = NULL) = 0;
};

