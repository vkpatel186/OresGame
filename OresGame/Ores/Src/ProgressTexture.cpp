#include "ProgressTexture.h"

void ProgressTexture::init(SDL_Rect data)
{
    if (ComponentManager::_renderer)
    {
        _outLine = TextureManager::LoadTexture("Assets/outline.png");
        _progress = TextureManager::LoadTexture("Assets/fill.png");
        _progressRect.x = data.x;
        _progressRect.y = data.y;
        _progressRect.h = data.h;
        _maxWidth = data.w;
        _percentage = 0;

    }
}

void ProgressTexture::update()
{
    int destW = std::min(_maxWidth, static_cast<int>(_percentage / 100.0f * _maxWidth));
    int animValue = std::abs(destW - _progressRect.w) / 2;
    destW > _progressRect.w ? _progressRect.w += animValue : _progressRect.w -= animValue;
}

void ProgressTexture::updatePercentage(int percentage)
{
    _percentage = percentage;
}
void ProgressTexture::render()
{
    auto _outLineRect = SDL_Rect({ _progressRect.x - 2 ,_progressRect.y - 2 ,_maxWidth+4,_progressRect.h+4 });
    SDL_RenderCopy(ComponentManager::_renderer, _outLine, NULL, &_outLineRect);
    SDL_RenderCopy(ComponentManager::_renderer, _progress, NULL, &_progressRect);
}