#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
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
    //���������� ��������� �����
    bool IsRunning = true;

    //2 ���� ����� ���������
    Window window;

};

