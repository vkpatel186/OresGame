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
    _animationSpeed  = w/10;
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
    if (_destX != pos.x)
    {

        _destX > pos.x ? pos.x+= _animationSpeed : pos.x-= _animationSpeed;
        isAnimationRunning = true;
    }
    if (_destY != pos.y)
    {
        _destY > pos.y ? pos.y+= _animationSpeed : pos.y-= _animationSpeed;
        isAnimationRunning = true;
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