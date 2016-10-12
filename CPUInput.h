#pragma once

#include "InputComponents.h"

class CPUInput : public InputComponents
{
public:
	const static int OFFSET = 20;

	CPUInput(Quad* pong);
	virtual void updateInput(Quad* self, SDL_Event* e = NULL);
	void closeCPUInput();

private:
	void knowThePongs();
	Quad* mPong = NULL;

	int pongX, pongY;
	int smartNess;
};

