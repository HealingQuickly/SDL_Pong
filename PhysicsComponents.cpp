#include "PhysicsComponents.h"

PhysicsComponents::PhysicsComponents(int screenWidth, int screenHeight)
{
	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;
}

void PhysicsComponents::updateMovement(Quad* quad)
{
	//Move the dot left or right
	quad->mX += quad->mVelocityX;
	quad->getCollider()->x = quad->mX;

	//Move the quad up or down
	quad->mY += quad->mVelocityY;
	quad->getCollider()->y = quad->mY;
}

bool PhysicsComponents::checkCollision(SDL_Rect* a, SDL_Rect* b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a->x;
	rightA = a->x + a->w;
	topA = a->y;
	bottomA = a->y + a->h;

	//Calculate the sides of rect B
	leftB = b->x;
	rightB = b->x + b->w;
	topB = b->y;
	bottomB = b->y + b->h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}

int PhysicsComponents::checkCollisionWithWindow(Quad* quad)
{
	int pongL, pongR, pongU, pongD;
	pongL = quad->mX;
	pongR = quad->mX + quad->mW;
	pongU = quad->mY;
	pongD = quad->mY + quad->mH;

	if (pongU < 0)
	{
		return WindowSides::UP;
	}
	else if (pongD > mScreenHeight)
	{
		return WindowSides::DOWN;
	}
	else if (pongL < 0)
	{
		return WindowSides::LEFT;
	}
	else if (pongR > mScreenWidth)
	{
		return WindowSides::RIGHT;
	}

	return WindowSides::NONE;
}