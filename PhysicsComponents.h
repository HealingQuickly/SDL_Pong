#pragma once

#include "Quad.h"
#include <vector>

class PhysicsComponents
{
public:
	PhysicsComponents(int screenWidth, int screenHeight);

	void updateMovement(Quad* quad);
	void hittingPaddle(Quad* paddle, Quad* pong);
	bool checkCollision(SDL_Rect* a, SDL_Rect* b);
	bool hittingWindow(int screenWidth, int screenHeight, std::vector<Quad*> pongs);
	
private:
	int mScreenWidth;
	int mScreenHeight;
};