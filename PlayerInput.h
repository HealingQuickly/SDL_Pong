#pragma once
#include "InputComponents.h"

class PlayerInput : public InputComponents
{
public:
	PlayerInput();

	virtual void updateInput(Quad* quad, SDL_Event* e);
};

