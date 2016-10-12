#include "Quad.h"

Quad::Quad(int x, int y): mX(x), mY(y), mW(0), mH(0), mVelocityX(0), mVelocityY(0), mSpeed(PADDLE_MOVE_SPEED)
{
	defineQuad(PADDLE_WIDTH, PADDLE_HEIGHT);
}

void Quad::defineQuad(int w, int h)
{
	mW = w;
	mH = h;
	mCollider.x = mX;
	mCollider.y = mY;
	mCollider.w = w;
	mCollider.h = h;
}

void Quad::forceQuad(int vX, int vY)
{
	mVelocityX = vX;
	mVelocityY = vY;
}

void Quad::changeQuadSpeed(int speed)
{
	mSpeed = speed;
}