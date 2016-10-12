#pragma once

#include "SDLEngine.h"

#include "GamePong.h"
#include "IntroPong.h"

#include "Quad.h"
#include "PhysicsComponents.h"
#include "GraphicComponents.h"
#include "PlayerInput.h"
#include "CPUInput.h"

class PongMainGame
{
public:
	//Define screen resolution individually for each game here
	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 600;

	PongMainGame();

	bool initSystem();
	void closeSystem();

	void gameLoop();
	void change_State();

private:
	SDLEngine mSDLPong;

	int mStateID;
	int mNextState;
	GameState* mCurrentState;
};