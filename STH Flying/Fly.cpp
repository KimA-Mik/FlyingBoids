#include "Fly.h"

Fly::Fly() {

}
Fly::~Fly() {

}

void Fly::Render(SDL_Renderer* Renderer) {

}
void Fly::Move(Uint32 ElapsedTime) {

}
void Fly::Free() {

}

void Fly::CheckCollisions(const std::vector<ObjStats> List, Uint32 ElapsedTime, SDL_Renderer* renderer)
{
	double Step = ElapsedTime / 1000.f;
	const double dAng = 0.05f;
	int XCoord = (xPos + Img->getWidth() / 2), SrX = 0;
	int YCoord = (yPos + Img->getHeight() / 2), SrY = 0;
	double SrArifm = 0.0f;
	int ArifmCount = 0;
	for (auto Object : List) {
		double Dist = sqrt((XCoord - Object.X) * (XCoord - Object.X) + (YCoord - Object.Y) * (YCoord - Object.Y));
		//double kDist = 1 / Dist;
		//double kDist = 1468 - Dist;
		double DiffAng = Object.Angle - Angle;
		//Angle += DiffAng * kDist * Step;
		
		//Правило 1 - принимать направление соседей
		if (Dist < 100){
			if (DiffAng > 165 && DiffAng < 195) {
				Vel = 100;
			}
			else
				Angle += DiffAng * Step / 2;
		}
		if (Dist < 150) {
			SrArifm += Object.Angle;
			SrX += Object.X;
			SrY += Object.Y;
			ArifmCount++;
		}
	}

	//правило  2 - направляться к скоплению собратьев
	if (ArifmCount) {
		SrArifm /= ArifmCount;
		SrX /= ArifmCount;
		SrY /= ArifmCount;
		SDL_Point velVect = { XCoord - prevX,YCoord - prevY };
		SDL_Point targVect = { SrX - prevX,SrY - prevY };
		int ProizvVec = velVect.x * targVect.x + velVect.y * targVect.y;
		double ProizvAbsVec = sqrt(velVect.x * velVect.x + velVect.y * velVect.y) * sqrt(targVect.x * targVect.x + targVect.y * targVect.y);
		if (ProizvAbsVec != 0) {
			double CosPhi = ProizvVec / (int)ProizvAbsVec;
			double dAng = acos(CosPhi) * 180. / M_PI;;
			//Angle += (SrArifm - Angle) * Step;
			if (dAng > 165 && dAng < 195) {
				Vel = 100;

			}
			else 
				Angle += dAng * Step;
		}
	}

	

	//правило 3 - уклоняться от столкновений (пока плохо)
	int LeftCount = 0;
	int RightCount = 0;
	//делаем рейкаст, влево от угла обзора

	//SDL_SetRenderDrawColor(renderer, 194, 54, 22, 255);
	for (double RayAng = Angle - 25; RayAng < Angle; RayAng += 2) {
		//if (RayAng < 0)
			//RayAng = 360 - RayAng;
		//10 точек вперед
		for (int i = -5; i < 61; i += 10){
			int x = XCoord + i * cos(RayAng * M_PI / 180.);
			int y = YCoord + i * sin(RayAng * M_PI / 180.);
			//SDL_RenderDrawPoint(renderer, x, y);

			for (auto Object : List) {
				if (abs(x - Object.X) < 20 && abs(y - Object.Y) < 20)
					LeftCount++;
			}
		}
	}
	//вправо
	for (double RayAng = Angle + 25; RayAng > Angle; RayAng -= 2) {
		//if (RayAng > 360)
			//RayAng = RayAng - 360;
		for (int i = -5; i < 61; i += 10) {
			int x = XCoord + i * cos(RayAng * M_PI / 180.);
			int y = YCoord + i * sin(RayAng * M_PI / 180.);
			//SDL_RenderDrawPoint(renderer, x, y);
			for (auto Object : List) {
				if (abs(x - Object.X) < 20 && abs(y - Object.Y) < 20)
					RightCount++;
			}
		}
	}

	if (RightCount < LeftCount)
		Angle += Step * LeftCount * 2;
	if (RightCount > LeftCount)
		Angle -= Step * RightCount * 2;
	

	
}

Bird::Bird(SDL_Renderer* Renderer, int x, int y, double Ang){
	xPos = x;
	yPos = y;
	prevX = xPos;
	prevY = yPos;
	Angle = Ang;
	Img = new Texture;
	int RND = rand() % 7;
	switch (RND)
	{
	case 0:
		Img->loadFromFile(Renderer, "Assets/BlueBird.png");
		break;
	case 1:
		Img->loadFromFile(Renderer, "Assets/DarkBird.png");
		break;
	
	case 2:
		Img->loadFromFile(Renderer, "Assets/GreenBird.png");
		break;
	
	case 3:
		Img->loadFromFile(Renderer, "Assets/PaleBlueBird.png");
		break;
	
	case 4:
		Img->loadFromFile(Renderer, "Assets/PurpleBird.png");
		break;
	
	case 5:
		Img->loadFromFile(Renderer, "Assets/RedBird.png");
		break;
	
	case 6:
		Img->loadFromFile(Renderer, "Assets/YellowBird.png");
		break;
	}
}

Bird::~Bird(){
	Free();
}

void Bird::Move(Uint32 ElapsedTime){
	
	if (Angle < 0)
		Angle = 360 - Angle;

	if (Angle > 360)
		Angle = Angle - 360;

	
	
	double Step = ElapsedTime / 1000.f;
	//std::cout << "Step is" << Step << std::endl;
	prevX = xPos;
	prevY = yPos;
 	xPos += Vel * cos(Angle * M_PI / 180.) * Step;
	yPos += Vel * sin(Angle * M_PI / 180.) * Step;

	if (Vel < 200)
		Vel = 200;


	if (xPos > ScreenWidth)
		xPos = -Img->getWidth();
	if (xPos + Img->getWidth() < 0)
		xPos = ScreenWidth;

	if (yPos > ScreenHeight)
		yPos = -Img->getHeight();
	if (yPos + Img->getHeight() < 0)
		yPos = ScreenHeight;

}


void Bird::Render(SDL_Renderer* Renderer){
	ImgCenter.x = 10;
	ImgCenter.y = 15;

	Img->render(Renderer, (int)xPos, (int)yPos, (SDL_Rect*)nullptr, Angle, &ImgCenter);
	
	//Angle -= 0.1;
}



void Bird::Free(){
	if (Img)
		Img->free();
}

