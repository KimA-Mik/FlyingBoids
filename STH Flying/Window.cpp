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
	mWindow = SDL_CreateWindow(Name.c_str(), XPos, YPos, WWidth, WHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (mWindow != nullptr)
	{
		mMouseFocus = true;
		mKeyboardFocus = true;
		mWidth = WWidth;
		mHeight = WHeight;

		mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (mRenderer == nullptr)
		{
			printf ("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			SDL_DestroyWindow(mWindow);
			mWindow = nullptr;
		}
		else
		{
			SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

			mWindowID = SDL_GetWindowID(mWindow);

			mShown = true;
		}
	}
	else
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
	}
	mTimer.start();
	srand(time(NULL));

	Textures[0].loadFromFile(mRenderer, "Assets/BlueBird.png");
	Textures[1].loadFromFile(mRenderer, "Assets/DarkBird.png");
	Textures[2].loadFromFile(mRenderer, "Assets/GreenBird.png");
	Textures[3].loadFromFile(mRenderer, "Assets/PaleBlueBird.png");
	Textures[5].loadFromFile(mRenderer, "Assets/RedBird.png");
	Textures[4].loadFromFile(mRenderer, "Assets/PurpleBird.png");
	Textures[6].loadFromFile(mRenderer, "Assets/YellowBird.png");

	for (int i = 0; i < 125; i++) {
		int X = rand() % mWidth;
		int Y = rand() % mHeight;
		float Ang = rand() % 360 + 180;
		//float Ang = 45;
		Texture* randTexture = &Textures[rand() % Textures.size()];
		Objects.push_back(std::make_unique<Bird>(X, Y, Ang, randTexture));
		Objects[i]->SetScreenParams(mWidth, mHeight);

		StatsList.push_back(Objects[i]->GetStats());
	}	

	return mWindow != nullptr && mRenderer != nullptr;
}

void Window::handleEvent(SDL_Event& e)
{
	int w, h;
	//If an event was detected for this window
	if (e.type == SDL_WINDOWEVENT && LastEventTime != e.window.timestamp)
	{
		switch (e.window.event)
		{
			//Window appeared
		case SDL_WINDOWEVENT_SHOWN:
			mShown = true;
			break;

			//Window disappeared
		case SDL_WINDOWEVENT_HIDDEN:
			//Freezes Linux
			//mMinimized = true;
			mShown = false;
			break;

			//Get new dimensions and repaint
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			updateWindowSize(e.window.data1, e.window.data2);
			break;

			//Repaint on expose
		case SDL_WINDOWEVENT_EXPOSED:
			SDL_RenderPresent(mRenderer);
			break;

			//Mouse enter
		case SDL_WINDOWEVENT_ENTER:
			mMouseFocus = true;
			break;

			//Mouse exit
		case SDL_WINDOWEVENT_LEAVE:
			mMouseFocus = false;
			break;

			//Keyboard focus gained
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			mKeyboardFocus = true;
			break;

			//Keyboard focus lost
		case SDL_WINDOWEVENT_FOCUS_LOST:
			mKeyboardFocus = false;
			break;

			//Window minimized
		case SDL_WINDOWEVENT_MINIMIZED:
			mMinimized = true;
			break;

			//Window maxized
		case SDL_WINDOWEVENT_MAXIMIZED:
			// SDL_GL_GetDrawableSize(mWindow, &w, &h);
			SDL_GetWindowSize(mWindow, &w, &h);
			updateWindowSize(w, h);
			mMinimized = false;
			break;

			//Window restored
		case SDL_WINDOWEVENT_RESTORED:
			// SDL_GL_GetDrawableSize(mWindow, &w, &h);
			SDL_GetWindowSize(mWindow, &w, &h);
			updateWindowSize(w, h);
			mMinimized = false;
			break;

			//Hide on close
		case SDL_WINDOWEVENT_CLOSE:
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
	double fps = 1000.0 / (double)ElapsedTime;
	Title << "Awesome boids    FPS: " << (int)fps;
	SDL_SetWindowTitle(mWindow, Title .str().c_str());
	PrevTime = mTimer.getTicks();
	
	if (!mMinimized)
	{
		SDL_SetRenderDrawColor(mRenderer, 245, 246, 250, 255);
		SDL_RenderClear(mRenderer);	
		
		for (long unsigned int i = 0; i < Objects.size(); i++) {
			StatsList[i] = Objects[i]->GetStats();
			Objects[i]->CheckCollisions(StatsList, ElapsedTime, mRenderer);
			Objects[i]->Move(ElapsedTime);
			Objects[i]->Render(mRenderer);
		}

		SDL_RenderPresent(mRenderer);
	}
}

void Window::updateWindowSize(int width, int height)
{
	mWidth = width;
	mHeight = height;

	for (auto& object : Objects)
		object->SetScreenParams(mWidth, mHeight);
			SDL_RenderPresent(mRenderer);
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

