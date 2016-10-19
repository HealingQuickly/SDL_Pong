#include "CPUInput.h"

CPUInput::CPUInput() : averageYofPongs(0)
{
	
}

void CPUInput::updateInput(Quad* self, SDL_Event* e)
{
	if (self->mY + self->mH + OFFSET <= averageYofPongs)
	{
		// cpu needs to move down
		self->mVelocityY = self->mSpeed;
	}
	else if (self->mY - OFFSET > averageYofPongs)
	{
		self->mVelocityY = -self->mSpeed;
	}
}

void CPUInput::knowThePongs(const std::vector<Quad*>& pongs)
{
	int sum = 0;
	unsigned int size = pongs.size();
	for (unsigned int i = 0; i < size; i++)
	{
		sum += pongs[i]->mY;
	}
	averageYofPongs = (size == 0) ? 0 : sum / size;
}