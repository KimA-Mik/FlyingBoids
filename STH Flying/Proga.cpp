#include "Proga.h"

Proga::Proga()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		IsRunning = false;
	}
	else {
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
			printf("Warning: Linear texture filtering not enabled!");

		if (!window.init("Lovushka Jocker'a", 1280, 720)) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			IsRunning = false;
		}
		else {
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags)) {
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				IsRunning = false;
			}

			if (TTF_Init() == -1) {
				printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
				IsRunning = false;
			}
		}
	}
}

Proga::~Proga()
{
	window.free();

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}


int Proga::Koldunstvo()
{

	SDL_Event e;
	while (IsRunning)
	{
		while (SDL_PollEvent(&e) != 0){
			if (e.type == SDL_QUIT){
				IsRunning = false;
			}
			window.handleEvent(e);
		}
		window.render();
		
		if (!window.isShown())
			IsRunning = false;

	}
	return 0;
}
