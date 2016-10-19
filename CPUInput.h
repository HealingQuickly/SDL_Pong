#pragma once

#include "InputComponents.h"
#include <vector>

class CPUInput : public InputComponents
{
public:
	const static int OFFSET = 20;

	CPUInput();
	void updateInput(Quad* self, SDL_Event* e = NULL);
	void knowThePongs(const std::vector<Quad*>& pongs);

private:
	int averageYofPongs;
};

