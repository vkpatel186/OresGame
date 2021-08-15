#pragma once
#include"SDL.h"
#include "SDL_image.h"
#include "OresGame.h"

class TextureManager
{
public:
    static SDL_Texture* LoadTexture(const char* file_name);
};

