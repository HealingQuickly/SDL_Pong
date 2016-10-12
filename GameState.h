#pragma once

#include <SDL.h>
class GameState
{
public:
	//Game states
	enum GameStates
	{
		STATE_NULL,
		STATE_INTRO,
		STATE_TITLE,
		STATE_PONG,
		STATE_EXIT,
	};

	virtual void handle_events(SDL_Event& event, int& nextState) = 0;
	virtual void logic(int& nextState) = 0;
	virtual void render() = 0;
	void set_next_state(int newState, int& nextState)
	{
		//If the user doesn't want to exit
		if (nextState != STATE_EXIT)
		{
			//Set the next state
			nextState = newState;
		}
	}

	virtual ~GameState() {};
};

