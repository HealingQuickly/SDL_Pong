#include "GamePong.h"

GamePong::GamePong(SDL_Renderer* renderer, int screenWidth, int screenHeight) : mRenderer(renderer), mScreenWidth(screenWidth), mScreenHeight(screenHeight)
{
	initGameState();
}


GamePong::~GamePong()
{
	closeGameState();
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
	cpuInput->updateInput(cpuPaddle);
}

void GamePong::logic(int& nextState)
{
	//Move the objects
	// movement happens in the last, before rendering
	moveQuad->updateMovement(playerPaddle);
	moveQuad->updateMovement(cpuPaddle);
	for (unsigned int i = 0; i < pongs.size(); i++)
	{
		moveQuad->updateMovement(pongs[i]);
	}

	//Handle collisions/logics after movements
	// for every pongs, each of them have to check hitting the paddles
	for (unsigned int i = 0; i < pongs.size(); i++)
	{
		moveQuad->hittingPaddle(playerPaddle, pongs[i]); // pongs hitting paddle q (player)
		moveQuad->hittingPaddle(cpuPaddle, pongs[i]); // pongs hitting paddle p (cpu)
	}

	//TO-DO
	// winning condition here, need to be changed!!!
	if (moveQuad->hittingWindow(mScreenWidth, mScreenHeight, pongs))
	{
		set_next_state(STATE_EXIT, nextState);
	}
}

void GamePong::render()
{
	//Clear screen with black color
	SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(mRenderer);

	//Render objects
	renderQuad->updateRender(playerPaddle, mRenderer);
	renderQuad->updateRender(cpuPaddle, mRenderer);
	for (unsigned int i = 0; i < pongs.size(); i++)
	{
		renderQuad->updateRender(pongs[i], mRenderer);
	}
}

void GamePong::initGameState()
{
	playerPaddle = new Quad(100, 10);
	cpuPaddle = new Quad(mScreenWidth - playerPaddle->mW - 100, 10);
	pong = new Quad(mScreenWidth / 2, 0);
	// give the pong some initial momentum
	pong->defineQuad(10, 10);
	pong->forceQuad(-2, 2);

	//store all the pongs for collision test
	pongs.push_back(pong);

	moveQuad = new PhysicsComponents(mScreenWidth, mScreenHeight);
	renderQuad = new GraphicComponents();
	playerInput = new PlayerInput();
	cpuInput = new CPUInput(pong);

	// change the cpu paddle's speed
	cpuPaddle->changeQuadSpeed(4);
}

void GamePong::closeGameState()
{
	delete playerPaddle;
	delete cpuPaddle;
	for (unsigned int i = 0; i < pongs.size(); i++)
	{
		delete pongs[i];
	}
	delete moveQuad;
	delete renderQuad;
	delete playerInput;
	cpuInput->closeCPUInput();
	delete cpuInput;
	mRenderer = NULL;
}