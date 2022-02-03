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

		if (!Window.init("Lovushka Jocker'a", 1280, 720)) {
			printf("Windows could not be created! SDL Error: %s\n", SDL_GetError());
			IsRunning = false;
		}
		else {
			//Загрузка PNG
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags)) {
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				IsRunning = false;
			}

			//SDL_ttf
			if (TTF_Init() == -1) {
				printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
				IsRunning = false;
			}
		}
	}
}

Proga::~Proga()
{
	//Уничтожаем окна
	Window.free();

	//Закрываем SDL
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}


int Proga::Koldunstvo()
{

	SDL_Event e;
	//основной цикл
	while (IsRunning)
	{
		while (SDL_PollEvent(&e) != 0){
			//Запрос на выход
			if (e.type == SDL_QUIT){
				IsRunning = false;
			}
		}
		SDL_Event* ePoint = &e;
		Window.handleEvent(e);
		Window.render();
		
		if (!Window.isShown())
			IsRunning = false;

	}
	return 0;
}
