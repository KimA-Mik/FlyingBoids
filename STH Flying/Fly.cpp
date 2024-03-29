#include "Fly.h"

void Fly::Render(SDL_Renderer* Renderer) {

}
void Fly::Move(Uint32 ElapsedTime) {

}
																				//Debug renderer
void Fly::CheckCollisions(const std::vector<ObjStats>& List, Uint32 ElapsedTime, SDL_Renderer* renderer)
{
	double Step = ElapsedTime / 1000.f;
	double XCoord = (xPos + Img->getWidth() / 2), SrX = 0;
	double YCoord = (yPos + Img->getHeight() / 2), SrY = 0;
	double SrArifm = 0.0f;
	int ArifmCount = 0;
	for (const auto& Object : List) {
		double Dist = sqrt((XCoord - Object.X) * (XCoord - Object.X) + (YCoord - Object.Y) * (YCoord - Object.Y));
		//double kDist = 1 / Dist;
		//double kDist = 1468 - Dist;
		double DiffAng = Object.Angle - Angle;
		//Angle += DiffAng * kDist * Step;
		
		//Rule 1 - take direction of its neighbours
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

	//Rule  2 - stick to big groups
	if (ArifmCount) {
		SrArifm /= ArifmCount;
		SrX /= ArifmCount;
		SrY /= ArifmCount;
		dPoint velVect = { XCoord - prevX,YCoord - prevY };
		dPoint targVect = { SrX - prevX,SrY - prevY };
		int ProizvVec = velVect.x * targVect.x + velVect.y * targVect.y;
		double ProizvAbsVec = sqrt(velVect.x * velVect.x + velVect.y * velVect.y) * sqrt(targVect.x * targVect.x + targVect.y * targVect.y);
		if ((int)ProizvAbsVec != 0) {
			double CosPhi = ProizvVec / ProizvAbsVec;
			double dAng = acos(CosPhi) * 180. / M_PI;
			//Angle += (SrArifm - Angle) * Step;
			if (dAng > 165 && dAng < 195) {
				Vel = 100;

			}
			else 
				Angle += dAng * Step;
		}
	}

	

	//Rule 3 - avoid collisions (bad for now)
	int LeftCount = 0;
	int RightCount = 0;

	//SDL_SetRenderDrawColor(renderer, 194, 54, 22, 255);
	for (double RayAng = Angle - 25; RayAng < Angle; RayAng += 2) {
		//if (RayAng < 0)
			//RayAng = 360 - RayAng;
		for (int i = -5; i < 61; i += 10){
			int x = XCoord + i * cos(RayAng * M_PI / 180.0);
			int y = YCoord + i * sin(RayAng * M_PI / 180.0);
			// SDL_RenderDrawPoint(renderer, x, y);

			for (const auto& Object : List) {
				if (abs(x - Object.X) < 20 && abs(y - Object.Y) < 20)
					LeftCount++;
			}
		}
	}
	for (double RayAng = Angle + 25; RayAng > Angle; RayAng -= 2) {
		//if (RayAng > 360)
			//RayAng = RayAng - 360;
		for (int i = -5; i < 61; i += 10) {
			int x = XCoord + i * cos(RayAng * M_PI / 180.0);
			int y = YCoord + i * sin(RayAng * M_PI / 180.0);
			// SDL_RenderDrawPoint(renderer, x, y);
			for (const auto& Object : List) {
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

Bird::Bird(int x, int y, double Ang, Texture* texture){
	xPos = x;
	yPos = y;
	prevX = xPos;
	prevY = yPos;
	Angle = Ang;
	Img = texture;
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
}