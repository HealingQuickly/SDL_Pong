#pragma once

#include "GameState.h"

#include <vector>
#include <algorithm>

#include "SDLTexture.h"
#include "SDLBitmapFont.h"

#include "Quad.h"
#include "PhysicsComponents.h"
#include "GraphicComponents.h"
#include "PlayerInput.h"
#include "CPUInput.h"

class GamePong : public GameState
{
public:
	GamePong(SDL_Renderer* renderer, int screenWidth, int screenHeight);
	~GamePong();

	//Init and Wrap up
	void initGameState();
	void closeGameState();

	//Main loop functions
	void handle_events(SDL_Event& event, int& nextState);
	void logic(int& nextState);
	void render();

private:
	//Inner functions that serve the game logic. Is there a place for these functions?
	void loadMedia();
	void generateNewPong(int initX, int initY, int width, int height, int velocityX, int velocityY);

	void updatePaddleMovement(Quad* paddle);
	void updatePongMovement(Quad** pong); //Need to modify the pongs so pass in pointer to pointer

	bool checkHittingPaddle(Quad* paddle, Quad* pong);
	void hitPaddle(Quad* pong);

	//Get the reference of the renderer
	SDL_Renderer* mRenderer = NULL;

	int mScreenWidth;
	int mScreenHeight;


	//Assets used for this game
	Quad* playerPaddle = NULL;
	Quad* cpuPaddle = NULL;
	std::vector<Quad*> mPongs;

	PhysicsComponents* mPhysicsComponent = NULL;
	GraphicComponents* mGraphicsComponent = NULL;
	PlayerInput* playerInput = NULL;
	CPUInput* cpuInput = NULL;

	//Scene texts textures
	SDLTexture mBitmapTexture;
	SDLBitmapFont mBitmapFont;
	//Keeping score for both sides
	int mLeftScore = 0;
	int mRightScore = 0;
};

