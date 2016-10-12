#pragma once

#include "GameState.h"

#include <vector>

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
	//Get the reference of the renderer
	SDL_Renderer* mRenderer = NULL;

	int mScreenWidth;
	int mScreenHeight;

	Quad* playerPaddle = NULL;
	Quad* cpuPaddle = NULL;
	Quad* pong = NULL;
	std::vector<Quad*> pongs;

	PhysicsComponents* moveQuad = NULL;
	GraphicComponents* renderQuad = NULL;
	PlayerInput* playerInput = NULL;
	CPUInput* cpuInput = NULL;
};

