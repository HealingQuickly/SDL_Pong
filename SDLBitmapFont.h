#pragma once
#include "SDLTexture.h"

class SDLBitmapFont
{
public:
	SDLBitmapFont();

	//Generates the font
	bool buildFont(SDLTexture *bitmap);

	//Shows the text
	void renderText(SDL_Renderer* renderer, int x, int y, std::string text);

private:
	//The font texture
	SDLTexture* mBitmap;

	//The individual characters in the surface
	SDL_Rect mChars[256];

	//Spacing Variables
	int mNewLine, mSpace;
};

