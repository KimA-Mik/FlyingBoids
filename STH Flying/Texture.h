#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

class Texture{
public:
	Texture();
	~Texture();

	bool loadFromFile(SDL_Renderer* Renderer, std::string path);
	bool loadFromRenderedText(SDL_Renderer* Renderer, TTF_Font* Font, std::string textureText, SDL_Color textColor);

	void free();

	void setColor(Uint8 red, Uint8 green, Uint8 blue)	{ SDL_SetTextureColorMod(mTexture, red, green, blue); }
	void setBlendMode(SDL_BlendMode blending)			{ SDL_SetTextureBlendMode(mTexture, blending); }
	void setAlpha(Uint8 alpha)							{ SDL_SetTextureAlphaMod(mTexture, alpha); }

	void render(SDL_Renderer* Renderer, int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

	int getWidth() { return mWidth; }
	int getHeight() { return mHeight; }

private:
	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;
};
