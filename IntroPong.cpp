#include "IntroPong.h"



IntroPong::IntroPong(SDL_Renderer* renderer, int screenWidth, int screenHeight) : mRenderer(renderer), mScreenWidth(screenWidth), mScreenHeight(screenHeight)
{
	loadMedia();
}


IntroPong::~IntroPong()
{
	TTF_CloseFont(mFont);
	mFont = NULL;

	mTextTexture.free();
	mEnterTexture.free();
	mMusicCredit.free();

	//Free the music
	Mix_FreeMusic(mMusic);
	mMusic = NULL;

	mRenderer = NULL;
}

void IntroPong::handle_events(SDL_Event& event, int& nextState)
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
			set_next_state(STATE_TITLE, nextState);
		}
	}
}

void IntroPong::logic(int& nextState)
{
	//If there is no music playing
	if (Mix_PlayingMusic() == 0)
	{
		//Play the music
		Mix_PlayMusic(mMusic, -1);
	}
}

void IntroPong::render()
{
	//Clear screen with white color
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(mRenderer);

	mTextTexture.render(mRenderer, (mScreenWidth - mTextTexture.getWidth()) / 2, (mScreenHeight - mTextTexture.getHeight()) / 2 - DISPLAY_OFFSET);

	//Set alpha for "Press Enter" to make it blink
	if (alphaOffset >= 255)
	{
		alphaOffset = 0 - alphaOffset;
	}
	alphaOffset += 4;
	mEnterTexture.setAlpha(alpha - alphaOffset);
	mEnterTexture.render(mRenderer, (mScreenWidth - mEnterTexture.getWidth()) / 2, (mScreenHeight - mTextTexture.getHeight()) / 2 + DISPLAY_OFFSET);

	mMusicCredit.render(mRenderer, (mScreenWidth - mMusicCredit.getWidth()), (mScreenHeight - mMusicCredit.getHeight()));
}

void IntroPong::loadMedia()
{
	//Open the font
	mFont = TTF_OpenFont("Assets/lazy.ttf", 28);
	if (mFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		return;
	}
	else
	{
		//Render text
		SDL_Color textColor = { 0, 0, 0 };
		if (!mTextTexture.loadFromRenderedText(mRenderer, mFont, "The 21st century Pong made by Ian Nie", textColor))
		{
			printf("Failed to render text texture!\n");
			return;
		}
		if (!mEnterTexture.loadFromRenderedText(mRenderer, mFont, "Press Enter", textColor))
		{
			printf("Failed to render text texture!\n");
			return;
		}
		else
		{
			//Set standard alpha blending
			mEnterTexture.setBlendMode(SDL_BLENDMODE_BLEND);
		}
		if (!mMusicCredit.loadFromRenderedText(mRenderer, mFont, "Music by Edward Truong", textColor))
		{
			printf("Failed to render text texture!\n");
			return;
		}
	}

	//Load music
	mMusic = Mix_LoadMUS("Assets/Future.wav");
	if (mMusic == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		return;
	}
}