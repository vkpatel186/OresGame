#include "CanvasImage.h"

void CanvasImage::init(const char* asset, SDL_Rect data, bool enabled, std::function<void(void)> callback)
{
    _image = TextureManager::LoadTexture(asset);
    _imageRect = data;
    _callback = callback;
    _enabled = enabled;
}
void CanvasImage::updateImage(const char* asset)
{
    SDL_DestroyTexture(_image);
    _image = TextureManager::LoadTexture(asset);
}
void CanvasImage::updatePosition(int x, int y)
{
    _imageRect.x = x;
    _imageRect.y = y;
}
void CanvasImage::updateSize(int w, int h)
{
    _imageRect.w = w;
    _imageRect.h = h;
}
void CanvasImage::handleClick(int x, int y)
{
    if (_enabled && 
        x >= _imageRect.x && x <= _imageRect.x + _imageRect.w &&
        y >= _imageRect.y && y <= _imageRect.y + _imageRect.h)
    {
        _callback();
    }
    
}

void CanvasImage::render()
{
    SDL_RenderCopy(ComponentManager::_renderer, _image, NULL, &_imageRect);
}