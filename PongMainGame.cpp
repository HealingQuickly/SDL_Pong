#include "PongMainGame.h"

#include <vector>

PongMainGame::PongMainGame()
{
	
}

bool PongMainGame::initSystem()
{
	mStateID = GameState::STATE_PONG;
	mNextState = GameState::STATE_NULL;
	mSDLPong = SDLEngine::SDLEngine(SCREEN_WIDTH, SCREEN_HEIGHT);
	return mSDLPong.initSDL();
}

void PongMainGame::closeSystem()
{
	delete mCurrentState;
	mSDLPong.closeSDL();
}

void PongMainGame::change_State()
{
	//If the state needs to be changed
	if (mNextState != GameState::STATE_NULL)
	{
		//Delete the current state
		if (mNextState != GameState::STATE_EXIT)
		{
			delete mCurrentState;
		}

		//Change the state
		switch (mNextState)
		{
		case GameState::STATE_INTRO:
			mCurrentState = new IntroPong(mSDLPong.getRenderer(), SCREEN_WIDTH, SCREEN_HEIGHT);
			break;
		case GameState::STATE_TITLE:
			mCurrentState = new TitlePong(mSDLPong.getRenderer(), SCREEN_WIDTH, SCREEN_HEIGHT);
			break;
		case GameState::STATE_PONG:
			mCurrentState = new GamePong(mSDLPong.getRenderer(), SCREEN_WIDTH, SCREEN_HEIGHT);
			break;
		case GameState::STATE_ENDING:
			mCurrentState = new EndingPong(mSDLPong.getRenderer(), SCREEN_WIDTH, SCREEN_HEIGHT);
			break;
		}

		//Change the current state ID
		mStateID = mNextState;

		//NULL the next state ID
		mNextState = GameState::STATE_NULL;
	}
}

void PongMainGame::gameLoop()
{
	mCurrentState = new IntroPong(mSDLPong.getRenderer(), SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_Event e;

	while (mStateID != GameState::STATE_EXIT)
	{
		// handle input first
		mCurrentState->handle_events(e, mNextState);

		// then handle logic/collisions
		mCurrentState->logic(mNextState);

		// before rendering everything, try to change the state
		change_State();
		
		// Render all objects from state machine
		mCurrentState->render();

		//Update screen (universal for all game states)
		SDL_RenderPresent(mSDLPong.getRenderer());
	}
}