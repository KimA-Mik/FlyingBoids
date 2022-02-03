#include "Texture.h"

Texture::Texture(){
	mTexture = nullptr;
	mWidth = 0;
	mHeight = 0;
}

Texture::~Texture(){
	free();
}

bool Texture::loadFromFile(SDL_Renderer* Renderer, std::string path){
	free();

	SDL_Texture* newTexture = nullptr;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	else{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		newTexture = SDL_CreateTextureFromSurface(Renderer, loadedSurface);
		if (newTexture == nullptr)
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		else{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}

	mTexture = newTexture;
	return mTexture != nullptr;
}

bool Texture::loadFromRenderedText(SDL_Renderer* Renderer, TTF_Font* Font, std::string textureText, SDL_Color textColor)
{
	free();

	SDL_Surface* textSurface = TTF_RenderUTF8_Solid(Font, textureText.c_str(), textColor);
	if (textSurface == nullptr)
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	
	else{
		mTexture = SDL_CreateTextureFromSurface(Renderer, textSurface);
		if (mTexture == nullptr)
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());

		else{
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}

	return mTexture != nullptr;
}

void Texture::free(){
	if (mTexture != nullptr){
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
		mWidth = 0;
		mHeight = 0;
	}
}

void Texture::render(SDL_Renderer* Renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	if (clip != nullptr){
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(Renderer, mTexture, clip, &renderQuad, angle, center, flip);
}

