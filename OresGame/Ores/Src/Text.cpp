#include "Text.h"
#include "SDL_ttf.h"


void Text::init(SDL_Color color, SDL_Rect rect, Font fontDetails,std::string str)
{
    _color = color;
    _textRect = rect;
    _text = str;
    _fontDetail = fontDetails;
    loadTexture(color, str.c_str(), fontDetails);
}
void Text::updateText(std::string text)
{
    if (text != _text)
    {
        _text = text;
        loadTexture(_color, _text.c_str(), _fontDetail);
    }
}

void Text::updateColor(SDL_Color color)
{
    if (color.r != _color.r || color.g != _color.g ||
        color.b != _color.b || color.a != _color.a)
    {
        _color = color;
        loadTexture(_color, _text.c_str(), _fontDetail);
    }
}
void Text::updateSize(int w, int h)
{
    _textRect.w = w;
    _textRect.h = h;

}

void Text::updatePosition(int x, int y)
{
    _textRect.x = x;
    _textRect.y = y;

}
void Text::render()
{
    SDL_RenderCopy(ComponentManager::_renderer, _textTextrue, NULL, &_textRect);
}

void Text::loadTexture(SDL_Color color, const char* text, Font fontDetails)
{
    SDL_DestroyTexture(_textTextrue);
    TTF_Font* font = TTF_OpenFont(fontDetails.fontPath.c_str(), fontDetails.fontSize);
    if (!font) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        // handle error
    }
    SDL_Surface* tempSurface = TTF_RenderText_Solid(font, text, color);
    _textTextrue = SDL_CreateTextureFromSurface(ComponentManager::_renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
}
