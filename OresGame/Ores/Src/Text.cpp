#include "Text.h"
#include "SDL_ttf.h"


void Text::init(SDL_Color color, SDL_Rect rect, Font fontDetails,std::string str)
{
    _color = color;
    _textRect = rect;
    _text = str;
    _fontDetail = fontDetails;
    _textTextrue = loadTexture(color, str.c_str(), fontDetails);
}
void Text::updateText(std::string text)
{
    SDL_DestroyTexture(_textTextrue);
    _text = text;
    _textTextrue = loadTexture(_color, _text.c_str(), _fontDetail);
}

void Text::updateColor(SDL_Color color)
{
    SDL_DestroyTexture(_textTextrue);
    _color = color;
    _textTextrue = loadTexture(_color, _text.c_str(), _fontDetail);
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

SDL_Texture* Text::loadTexture(SDL_Color color, const char* text, Font fontDetails)
{
    TTF_Font* font = TTF_OpenFont(fontDetails.fontPath.c_str(), fontDetails.fontSize);
    if (!font) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        // handle error
    }
    SDL_Surface* tempSurface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ComponentManager::_renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    return tex;
}
