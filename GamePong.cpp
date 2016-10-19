#include "GamePong.h"

GamePong::GamePong(SDL_Renderer* renderer, int screenWidth, int screenHeight) : mRenderer(renderer), mScreenWidth(screenWidth), mScreenHeight(screenHeight)
{
	initGameState();
	loadMedia();
}


GamePong::~GamePong()
{
	closeGameState();
}



// Init game objects here
void GamePong::initGameState()
{
	playerPaddle = new Quad(100, 10);
	cpuPaddle = new Quad(mScreenWidth - playerPaddle->mW - 100, 10);
	generateNewPong(mScreenWidth / 2, 2, 10, 10, -2, 3);
	generateNewPong(mScreenWidth / 2, 20, 10, 10, 3, 1);
	generateNewPong(mScreenWidth / 2, 20, 10, 10, -3, 4);
	generateNewPong(mScreenWidth / 2, 50, 10, 10, -2, 1);
	generateNewPong(mScreenWidth / 2, 100, 10, 10, -2, 2);

	mPhysicsComponent = new PhysicsComponents(mScreenWidth, mScreenHeight);
	mGraphicsComponent = new GraphicComponents();
	playerInput = new PlayerInput();
	cpuInput = new CPUInput(); // cpu Input needs to know the pongs to follow/block them

	// change the cpu paddle's speed
	cpuPaddle->changeQuadSpeed(3);
}

void GamePong::closeGameState()
{
	mRenderer = NULL;

	delete playerPaddle;
	delete cpuPaddle;
	for (unsigned int i = 0; i < mPongs.size(); i++)
	{
		delete mPongs[i];
		mPongs[i] = NULL;
	}
	delete mPhysicsComponent;
	delete mGraphicsComponent;
	delete playerInput;
	delete cpuInput;

	playerPaddle = NULL;
	cpuPaddle = NULL;
	mPhysicsComponent = NULL;
	mGraphicsComponent = NULL;
	playerInput = NULL;
	cpuInput = NULL;
	mRenderer = NULL;

	mBitmapTexture.free();
}

void GamePong::handle_events(SDL_Event& event, int& nextState)
{
	while (SDL_PollEvent(&event))
	{
		//If the user has Xed out the window
		if (event.type == SDL_QUIT)
		{
			//Quit the program
			set_next_state(STATE_EXIT, nextState);
		}
		playerInput->updateInput(playerPaddle, &event);
	}
	cpuInput->knowThePongs(mPongs); // CPU Input needs to know the pongs so that it can react accordingly
	cpuInput->updateInput(cpuPaddle);
}

// only for the use of std::remove_if
bool pongIsNull(Quad* pong)
{
	if (pong == NULL)
		return true;
	return false;
}
void GamePong::logic(int& nextState)
{
	//Check collision between pongs and two paddles
	for (unsigned int i = 0; i < mPongs.size(); i++)
	{
		if (checkHittingPaddle(playerPaddle, mPongs[i]) || checkHittingPaddle(cpuPaddle, mPongs[i]))
		{
			//Handle hit paddle event
			hitPaddle(mPongs[i]);
		}
	}

	//Update paddle movement with up and down boundary
	updatePaddleMovement(playerPaddle);
	updatePaddleMovement(cpuPaddle);

	//Update the pongs movement and check for left/right outbound for winning condition
	for (unsigned int i = 0; i < mPongs.size(); i++)
	{
		if (mPongs[i] != NULL)
		{
			updatePongMovement(&mPongs[i]);
		}
	}

	//To clear up the outbound pong (the ones deleted and set to NULL)
	mPongs.erase(std::remove_if(mPongs.begin(), mPongs.end(), pongIsNull), mPongs.end());
}

void GamePong::render()
{
	//Clear screen with black color
	SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(mRenderer);

	//Render Scores in first to be in background
	mBitmapFont.renderText(mRenderer, 5, 5, std::to_string(mLeftScore));
	mBitmapFont.renderText(mRenderer, 775, 5, std::to_string(mRightScore));

	//Render objects
	mGraphicsComponent->updateRender(playerPaddle, mRenderer);
	mGraphicsComponent->updateRender(cpuPaddle, mRenderer);
	for (unsigned int i = 0; i < mPongs.size(); i++)
	{
		mGraphicsComponent->updateRender(mPongs[i], mRenderer);
	}
}





//Private inner functions that serve the game logic. Is there a place for these functions?
void GamePong::loadMedia()
{
	//Load font texture
	if (!mBitmapTexture.loadFromFile(mRenderer, "Assets/lazyfont2.png"))
	{
		printf("Failed to load corner texture!\n");
		return;
	}
	else
	{
		//Build font from texture
		mBitmapFont.buildFont(&mBitmapTexture);
	}
}

void GamePong::generateNewPong(int initX, int initY, int width, int height, int velocityX, int velocityY)
{
	Quad* newPong = new Quad(initX, initY);
	newPong->defineQuad(width, height);
	newPong->forceQuad(velocityX, velocityY);
	mPongs.push_back(newPong);
}


void GamePong::updatePaddleMovement(Quad* paddle)
{
	mPhysicsComponent->updateMovement(paddle);
	if (paddle->mY < 0 || paddle->mY + paddle->mH > mScreenHeight)
	{
		//Move back
		paddle->mY -= paddle->mVelocityY;
		paddle->getCollider()->y = paddle->mY;
	}
}

void GamePong::updatePongMovement(Quad** pong)
{
	mPhysicsComponent->updateMovement(*pong);
	//Right player wins by one pong
	if ((*pong)->mX < 0)
	{
		delete *pong;
		*pong = NULL;
		mRightScore++;
	}
	else if ((*pong)->mX + (*pong)->mW > mScreenWidth)
		//Left player wins by one pong
	{
		delete (*pong);
		(*pong) = NULL;
		mLeftScore++;
	}
	else if ((*pong)->mY < 0 || (*pong)->mY + (*pong)->mH > mScreenHeight)
		//Pong hit the up/down side of screen, bounce!
	{
		(*pong)->mY -= (*pong)->mVelocityY;
		(*pong)->getCollider()->y = (*pong)->mY;
		(*pong)->mVelocityY = 0 - (*pong)->mVelocityY;
	}
}

// two paddles calling this function to detect collision with all possible pongs
bool GamePong::checkHittingPaddle(Quad* paddle, Quad* pong)
{
	if (mPhysicsComponent->checkCollision(paddle->getCollider(), pong->getCollider()))
	{
		//Set status for having collision with paddle
		//For now, return true to handle hit paddles for it to handle
		return true;
		//Handle pong hit paddle now
		//By calling hitPaddle()
	}
	//Default
	return false;
}

//When checkHittingPaddle is true, this is called to handle
void GamePong::hitPaddle(Quad* pong)
{
	//Reverse the velocity horizontally
	pong->mX -= pong->mVelocityX; //Move back the collided part
	pong->getCollider()->x = pong->mX; //The collider follows
	pong->mVelocityX = 0 - pong->mVelocityX; //Reverse velocity horizontally
}