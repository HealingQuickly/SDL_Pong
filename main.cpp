#include "PongMainGame.h"

int main(int argc, char* argv[])
{
	PongMainGame pong;

	if (!pong.initSystem())
	{
		printf("Failed to init SDL and create the game...\n");
	}
	else
	{
		pong.gameLoop();
	}

	pong.closeSystem();

	return 0;
}