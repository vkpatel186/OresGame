#pragma once
#include <functional>
#include "TextureManager.h"
#include "OresGame.h"
#include"SDL.h"
#include "SDL_image.h"
#include "ComponentManager.h"

class ProgressTexture:public Component
{
public:
    void init(SDL_Rect data);
    virtual void update();
    virtual void render();
    void updatePercentage(int percentage);

private:
    int _maxWidth;
    int _percentage;
    SDL_Texture* _outLine;
    SDL_Texture* _progress;
    SDL_Rect _progressRect;
};

