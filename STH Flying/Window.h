#pragma once
#include <SDL2/SDL.h>
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

	//�������� ������ ����
	bool init(std::string Name, int WWidth = 640, int WHeight = 480, int XPos = SDL_WINDOWPOS_UNDEFINED, int YPos = SDL_WINDOWPOS_UNDEFINED);

	//��������� ������� ����
	void handleEvent(SDL_Event& e);

	//��������� ����� �� ����
	void focus();

	//������������ ������ � ����
	void render();

	//������� ������ �� ���������� ����������
	void free();

	//������� ����
	int getWidth()			{ return mWidth; }
	int getHeight()			{ return mHeight; }

	//�������� ����
	bool hasMouseFocus()	{ return mMouseFocus; }
	bool hasKeyboardFocus()	{ return mKeyboardFocus; }
	bool isMinimized()		{ return mMinimized; }
	bool isShown()			{ return mShown; }


private:
	//������ ������ ����
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
