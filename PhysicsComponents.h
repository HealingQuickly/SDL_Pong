#pragma once

#include "Quad.h"

class PhysicsComponents
{
public:
	enum WindowSides
	{
		NONE,
		UP,
		DOWN,
		LEFT,
		RIGHT,
	};

	PhysicsComponents(int screenWidth, int screenHeight);

	void updateMovement(Quad* quad);
	bool checkCollision(SDL_Rect* a, SDL_Rect* b);
	int checkCollisionWithWindow(Quad* quad); // return value indicates the sides of the screen that a quad hits
	
private:
	int mScreenWidth;
	int mScreenHeight;
};