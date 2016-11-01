#include "TitlePong.h"



TitlePong::TitlePong(SDL_Renderer* renderer, int screenWidth, int screenHeight) : mRenderer(renderer), mScreenWidth(screenWidth), mScreenHeight(screenHeight)
{
	loadMedia();
}


TitlePong::~TitlePong()
{

	mRenderer = NULL;

	mBitmapTexture.free();
}

void TitlePong::handle_events(SDL_Event& event, int& nextState)
{
	while (SDL_PollEvent(&event))
	{
		//If the user has Xed out the window
		if (event.type == SDL_QUIT)
		{
			//Quit the program
			set_next_state(STATE_EXIT, nextState);
		}
		//If the user pressed enter
		else if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_RETURN))
		{
			//Move to the title screen
			set_next_state(STATE_PONG, nextState);
		}
	}
}

void TitlePong::logic(int& nextState)
{

}

void TitlePong::render()
{
	//Clear screen with white color
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(mRenderer);

	//Display title instructions with bitmap font
	mBitmapFont.renderText(mRenderer, mScreenWidth / 2 - 100, mScreenHeight / 32, "Instructions");
	mBitmapFont.renderText(mRenderer, mScreenWidth / 2 - 250, mScreenHeight / 18, "Fly pongs over the opponent paddle to score");
	mBitmapFont.renderText(mRenderer, 5, mScreenHeight / 8, "Player 1 Control:");
	mBitmapFont.renderText(mRenderer, 5, mScreenHeight / 5, "Move paddle up - W");
	mBitmapFont.renderText(mRenderer, 5, mScreenHeight / 4, "Move paddle down - S");
}

void TitlePong::loadMedia()
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