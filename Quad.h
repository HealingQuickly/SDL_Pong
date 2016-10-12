#pragma once

#include <SDL.h>

class Quad
{
public:
	static const int PADDLE_WIDTH = 10;
	static const int PADDLE_HEIGHT = 80;
	static const int PADDLE_MOVE_SPEED = 10;

	Quad(int x, int y);
	void defineQuad(int w, int h);
	void forceQuad(int vX, int vY);
	void changeQuadSpeed(int speed);
	SDL_Rect* getCollider() { return &mCollider; }

	int mX, mY;
	int mW, mH;
	int mVelocityX, mVelocityY;
	int mSpeed;

private:
	SDL_Rect mCollider;
};

