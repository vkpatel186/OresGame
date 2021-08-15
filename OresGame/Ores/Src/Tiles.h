#pragma once
#include<memory>
#include"SDL.h"
#include "SDL_image.h"
#include "OresGame.h"
#include "TextureManager.h"
#include "ComponentManager.h"
#include "CanvasImage.h"

class CanvasImage;
class Tiles: public Component
{
public:
    Tiles();
    void init(const char* asset, int index,int h, int w, int x, int y);
    void updateTileImageAndIndex(const char* asset,int index);
    void updateDestPosition(int x, int y, bool force = false);
    bool isClicked(int x, int y);
    virtual void update(); 
    int getIndex() { return _imageIndex; }
private:
    std::shared_ptr<CanvasImage> _tile;
    int _imageIndex;
    int _destX, _destY;
    bool isAnimationRunning;
    int _animationSpeed;
};

