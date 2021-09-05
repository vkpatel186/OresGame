#pragma once
#include "ComponentManager.h"
#include"SDL.h"
#include "SDL_image.h"
#include<string>
struct Font
{
    std::string fontPath;
    int fontSize;
};

class Text : public Component
{
public:
    void init(SDL_Color color, SDL_Rect rect, Font fontDetails, std::string str);
    virtual void render();
    void updateText(std::string text);
    void updateColor(SDL_Color color);
    void updateSize(int w,int h);
    void updatePosition(int x,int y);

private:
    void loadTexture(SDL_Color color, const char* text, Font fontDetails);
    Font _fontDetail;
    SDL_Rect _textRect;
    SDL_Color _color;
    std::string _text;
    SDL_Texture* _textTextrue;
};

