#include "CPUInput.h"
#include <random>
#include <time.h>

CPUInput::CPUInput(Quad* pong)
{
	mPong = pong;
	srand(time(0));
	smartNess = rand() % 3 - 1;
}

void CPUInput::updateInput(Quad* self, SDL_Event* e)
{
	//keep track of pong's Y position
	knowThePongs();

	if (self->mY + self->mH <= pongY - OFFSET)
	{
		// cpu needs to move down
		self->mVelocityY = self->mSpeed + smartNess;
	}
	else if (self->mY > pongY + OFFSET)
	{
		self->mVelocityY = -self->mSpeed - smartNess;
	}
}

void CPUInput::knowThePongs()
{
	pongX = mPong->mX;
	pongY = mPong->mY;
}

void CPUInput::closeCPUInput()
{
	mPong = NULL;
}