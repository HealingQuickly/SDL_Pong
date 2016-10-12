#include "PhysicsComponents.h"

#include <cmath>
#include <stdio.h>

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

	//If the dot went too far to the left or right
	if ((quad->mX < 0) || (quad->mX + quad->mW > mScreenWidth))
	{
		//Move back
		quad->mX -= quad->mVelocityX;
		quad->getCollider()->x = quad->mX;
	}

	//Move the dot up or down
	quad->mY += quad->mVelocityY;
	quad->getCollider()->y = quad->mY;

	//If the dot went too far up or down
	if ((quad->mY < 0) || (quad->mY + quad->mH > mScreenHeight))
	{
		//Move back
		quad->mY -= quad->mVelocityY;
		quad->getCollider()->y = quad->mY;
	}
}

// two paddles calling this function to detect collision with all possible pongs
void PhysicsComponents::hittingPaddle(Quad* paddle, Quad* pong)
{
	if (checkCollision(paddle->getCollider(), pong->getCollider()))
	{
		//Move back and set collider as well
		pong->mX -= pong->mVelocityX;
		pong->getCollider()->x = pong->mX;
		pong->mY -= pong->mVelocityY;
		pong->getCollider()->y = pong->mY;

		//Reverse the velocity horizontally
		pong->mVelocityX = 0 - pong->mVelocityX;
	}
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

bool PhysicsComponents::hittingWindow(int screenWidth, int screenHeight, std::vector<Quad*> pongs)
{
	int pongL, pongR, pongU, pongD;
	for (unsigned int i = 0; i < pongs.size(); i++)
	{
		pongL = pongs[i]->mX;
		pongR = pongs[i]->mX + pongs[i]->mW;
		pongU = pongs[i]->mY;
		pongD = pongs[i]->mY + pongs[i]->mH;

		// if pong is touching left or right side of the screen

		// left player loses
		if (pongL <= 0)
		{
			return true;
		}
		// right player loses
		if (pongR >= screenWidth)
		{
			return true;
		}

		// if pong is touching top or bottom side of the screen
		//reverse pong's Y velocity
		if (pongU <= 0 || pongD >= screenHeight)
		{
			pongs[i]->mVelocityY = 0 - pongs[i]->mVelocityY;
		}
	}
	return false;
}