#include "core.h"

int main(int argc, char* argv[])
{
	Setup* core = new Setup;

	int frameDelay = 1000 / 15; // second number is fps

	while (core->running())
	{
		int frameStart = SDL_GetTicks();

		core->listen();
		core->update();
		core->render();

		int frameEnd = SDL_GetTicks() - frameStart;
		
		if (frameDelay > frameEnd)
			SDL_Delay(frameDelay - frameEnd);
		
	}

	delete core;

	return 0;
}