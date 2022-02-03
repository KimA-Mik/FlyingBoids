#pragma once

#include <SDL.h>
#include <iostream>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Window.h"
#include "Texture.h"
#include <string>
#include <math.h>
#include <ctime>

class Proga
{
public:
    Proga();
    ~Proga();
    int Koldunstvo();
private:
    //Переменная основного цикла
    bool IsRunning = true;

    //2 окна нашей программы
    Window Window;

};

