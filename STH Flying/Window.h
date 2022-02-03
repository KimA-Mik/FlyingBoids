#pragma once
#include <SDL.h>
#include <iostream>
#include <memory>
#include "Fly.h"
#include "Timer.h"
#include <vector>
#include <sstream>


class Window{
public:
	Window();
	~Window();

	//Создание самого окна
	bool init(std::string Name, int WWidth = 640, int WHeight = 480, int XPos = SDL_WINDOWPOS_UNDEFINED, int YPos = SDL_WINDOWPOS_UNDEFINED);

	//Обработка событий окна
	void handleEvent(SDL_Event& e);

	//Переводит фокус на окно
	void focus();

	//Отрисовывает данные в окно
	void render();

	//Очищает данные по внутренним указателям
	void free();

	//Размеры окна
	int getWidth()			{ return mWidth; }
	int getHeight()			{ return mHeight; }

	//Парамеры окна
	bool hasMouseFocus()	{ return mMouseFocus; }
	bool hasKeyboardFocus()	{ return mKeyboardFocus; }
	bool isMinimized()		{ return mMinimized; }
	bool isShown()			{ return mShown; }


private:
	//Данные самого окна
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	int mWindowID;

	int mWidth;
	int mHeight;

	bool mMouseFocus;
	bool mKeyboardFocus;
	bool mFullScreen;
	bool mMinimized;
	bool mShown;

	Timer mTimer;
	Uint32 ElapsedTime = 0;
	Uint32 PrevTime = 0;
	Uint32 PrevFrame = 0;

	Uint32 LastEventTime = 0;

	std::vector<std::unique_ptr<Fly>> Objects;
	std::vector<ObjStats> StatsList;

};
