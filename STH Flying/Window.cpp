#include "Window.h"
Window::Window(){
	mWindow = nullptr;
	mRenderer = nullptr;

	mMouseFocus = false;
	mKeyboardFocus = false;
	mFullScreen = false;
	mShown = false;
	mWindowID = -1;

	mWidth = 0;
	mHeight = 0;

}

Window::~Window(){
	free();
}

bool Window::init(std::string Name, int WWidth, int WHeight, int XPos, int YPos){
	//Create window
	mWindow = SDL_CreateWindow(Name.c_str(), XPos, YPos, WWidth, WHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (mWindow != nullptr)
	{
		mMouseFocus = true;
		mKeyboardFocus = true;
		mWidth = WWidth;
		mHeight = WHeight;

		//Создаем рендерер
		mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (mRenderer == nullptr)
		{
			printf ("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			SDL_DestroyWindow(mWindow);
			mWindow = nullptr;
		}
		else
		{
			//Предваритльно определяем цвет
			SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

			//Записываем ID
			mWindowID = SDL_GetWindowID(mWindow);

			//Помечаем открытым
			mShown = true;

			
		}
	}
	else
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
	}
	mTimer.start();
	srand(time(NULL));
	for (int i = 0; i < 100; i++) {
		int X = rand() % mWidth;
		int Y = rand() % mHeight;
		float Ang = rand() % 360 + 180;
		//float Ang = 45;
		Objects.push_back(std::make_unique<Bird>(mRenderer, X, Y, Ang));
		Objects[i]->SetScreenParams(mWidth, mHeight);


		StatsList.push_back(Objects[i]->GetStats());

	}



	return mWindow != nullptr && mRenderer != nullptr;
}

void Window::handleEvent(SDL_Event& e)
{
	
	//If an event was detected for this window
	if (e.type == SDL_WINDOWEVENT /*&& e.window.windowID == mWindowID*/ && LastEventTime != e.window.timestamp)
	{
		//Caption update flag
		bool updateCaption = false;

		switch (e.window.event)
		{
			//Window appeared
		case SDL_WINDOWEVENT_SHOWN:
			SDL_Log("SDL_WINDOWEVENT_SHOWN\n");
			mShown = true;
			break;

			//Window disappeared
		case SDL_WINDOWEVENT_HIDDEN:
			SDL_Log("SDL_WINDOWEVENT_HIDDEN\n");
			mShown = false;
			break;

			//Get new dimensions and repaint
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			SDL_Log("SDL_WINDOWEVENT_SIZE_CHANGED\n");
			mWidth = e.window.data1;
			mHeight = e.window.data2;
			for (int i = 0; i < Objects.size(); i++) 
				Objects[i]->SetScreenParams(mWidth, mHeight);
			SDL_RenderPresent(mRenderer);
			break;

			//Repaint on expose
		case SDL_WINDOWEVENT_EXPOSED:
			SDL_Log("SDL_WINDOWEVENT_EXPOSED\n");
			SDL_RenderPresent(mRenderer);
			break;

			//Mouse enter
		case SDL_WINDOWEVENT_ENTER:
			SDL_Log("SDL_WINDOWEVENT_ENTER\n");
			mMouseFocus = true;
			updateCaption = true;
			break;

			//Mouse exit
		case SDL_WINDOWEVENT_LEAVE:
			SDL_Log("SDL_WINDOWEVENT_LEAVE\n");
			mMouseFocus = false;
			updateCaption = true;
			break;

			//Keyboard focus gained
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			SDL_Log("SDL_WINDOWEVENT_FOCUS_GAINED\n");
			mKeyboardFocus = true;
			updateCaption = true;
			break;

			//Keyboard focus lost
		case SDL_WINDOWEVENT_FOCUS_LOST:
			SDL_Log("SDL_WINDOWEVENT_FOCUS_LOST\n");
			mKeyboardFocus = false;
			updateCaption = true;
			break;

			//Window minimized
		case SDL_WINDOWEVENT_MINIMIZED:
			SDL_Log("SDL_WINDOWEVENT_MINIMIZED\n");
			mMinimized = true;
			break;

			//Window maxized
		case SDL_WINDOWEVENT_MAXIMIZED:
			SDL_Log("SDL_WINDOWEVENT_MAXIMIZED\n");
			mMinimized = false;
			break;

			//Window restored
		case SDL_WINDOWEVENT_RESTORED:
			SDL_Log("SDL_WINDOWEVENT_RESTORED\n");
			mMinimized = false;
			break;

			//Hide on close
		case SDL_WINDOWEVENT_CLOSE:
			SDL_Log("SDL_WINDOWEVENT_CLOSE\n");
			mShown = false;
			SDL_HideWindow(mWindow);
			break;

		}

		LastEventTime = e.window.timestamp;
		
	}
}

void Window::focus()
{
	//Restore window if needed
	if (!mShown)
	{
		SDL_ShowWindow(mWindow);
	}

	//Move window forward
	SDL_RaiseWindow(mWindow);
}

void Window::render()
{
	ElapsedTime = mTimer.getTicks() - PrevTime;
	std::stringstream Title;
	Title << "Awesome boids    FPS: " << 1000.f / ElapsedTime;
	SDL_SetWindowTitle(mWindow, Title .str().c_str());
	PrevTime = mTimer.getTicks();
	
	if (!mMinimized)
	{
		//Clear screen
		SDL_SetRenderDrawColor(mRenderer, 245, 246, 250, 255);
		SDL_RenderClear(mRenderer);
		
		for (int i = 0; i < Objects.size(); i++)
			StatsList[i] = Objects[i]->GetStats();
		
		for (int i = 0; i < Objects.size(); i++) {
			Objects[i]->CheckCollisions(StatsList, ElapsedTime, mRenderer);
			Objects[i]->Move(ElapsedTime);
			Objects[i]->Render(mRenderer);
		}

		//Update screen
		SDL_RenderPresent(mRenderer);
	}
}

void Window::free()
{
	if (mWindow != nullptr)
		SDL_DestroyWindow(mWindow);
	
	mMouseFocus = false;
	mKeyboardFocus = false;
	mWidth = 0;
	mHeight = 0;
}

