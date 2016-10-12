#include "PlayerInput.h"



PlayerInput::PlayerInput()
{
}

void PlayerInput::updateInput(Quad* quad, SDL_Event* e)
{
	//If a key was pressed
	if (e->type == SDL_KEYDOWN && e->key.repeat == 0)
	{
		//Adjust the velocity
		switch (e->key.keysym.sym)
		{
		case SDLK_w: quad->mVelocityY -= quad->PADDLE_MOVE_SPEED; break;
		case SDLK_s: quad->mVelocityY += quad->PADDLE_MOVE_SPEED; break;
		}
	}
	//If a key was released
	else if (e->type == SDL_KEYUP && e->key.repeat == 0)
	{
		//Adjust the velocity
		switch (e->key.keysym.sym)
		{
		case SDLK_w: quad->mVelocityY += quad->PADDLE_MOVE_SPEED; break;
		case SDLK_s: quad->mVelocityY -= quad->PADDLE_MOVE_SPEED; break;
		}
	}
}