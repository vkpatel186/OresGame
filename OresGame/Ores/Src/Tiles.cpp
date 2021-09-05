#include "Tiles.h"

Tiles::Tiles()
{
    _tile = ComponentManager::getComponentManager()->createComponent< CanvasImage>();
}

void Tiles::init(const char* asset, int index, int h, int w, int x, int y)
{
    _tile->init(asset, { x, y, w, h }, false, []() {});
    _destX = x;
    _destY = y;
    _imageIndex = index;
    _animationSpeed  = 5;
}

void Tiles::updateTileImageAndIndex(const char* asset, int index)
{
    _tile->updateImage(asset);
    _imageIndex = index;
}
void Tiles::updateDestPosition(int x, int y, bool force)
{
    _destX = x; 
    _destY = y;
    if (force)
    {
        _tile->updatePosition(x, y);
    }
}
void Tiles::update()
{
    isAnimationRunning = false;
    auto pos = _tile->getImageData();

    if (std::abs(_destX - pos.x) > _animationSpeed)
    {
        _destX > pos.x ? pos.x+= _animationSpeed : pos.x-= _animationSpeed;
        isAnimationRunning = true;
    }
    else
    {
         pos.x = _destX;
    }

    if (std::abs(_destY - pos.y) > _animationSpeed)
    {
        _destY > pos.y ? pos.y+= _animationSpeed : pos.y-= _animationSpeed;
        isAnimationRunning = true;
    }
    else
    {
        pos.y = _destY;
    }
    _tile->updatePosition(pos.x, pos.y);
}


bool Tiles::isClicked(int x, int y)
{
    auto imageSize = _tile->getImageData();
    if (!isAnimationRunning && _imageIndex)
    {
        if (x >= _destX && x <= _destX + imageSize.w &&
            y >= _destY && y <= _destY + imageSize.h)
        {
            return true;
        }
    }
    return false;
}