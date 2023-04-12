#pragma once
#include <SDL2/SDL.h>
#include "Texture.h"
#include <ctime>
#include <iostream>
#include <vector>
#include <math.h>

struct ObjStats
{
	int X;
	int Y;
	double Angle;
};

class Fly{
protected:
	SDL_Point ImgCenter;

	double Angle;
	double xPos, yPos;
	double prevX, prevY;
	int ScreenWidth, ScreenHeight;

	double Fov = 90;

	double Vel = 200;
	Texture* Img = nullptr;

public:


	virtual void Render(SDL_Renderer* Renderer);
	virtual void Move(Uint32 ElapsedTime);
	
	
	void SetScreenParams(int Width, int Height){
		ScreenWidth = Width;
		ScreenHeight = Height;
	}
	
	double Map(double n, double start1, double stop1, double start2, double stop2)
	{
		return ((n - start1) / (stop1 - start1)) * (stop2 - start2) + start2;
	}

	ObjStats GetStats() {
		ObjStats Res = { (int)(xPos + Img->getWidth() / 2),(int)(yPos + Img->getHeight() / 2),Angle };
		return  Res;
	}

	void CheckCollisions(const std::vector<ObjStats>& List, Uint32 ElapsedTime, SDL_Renderer* renderer);

};

class Bird : public Fly
{
private:
	

public:
	Bird(int x, int y, double Ang, Texture* texture);
	
	void Render(SDL_Renderer* Renderer) override;
	void Move(Uint32 ElapsedTime) override;
};

