#pragma once
#include<memory>
#include<functional>
#include"SDL.h"
#include "SDL_image.h"
#include "TextureManager.h"
#include "Component.h"
#include "ComponentManager.h"

class CanvasImage : public Component
{
    
public:
    void init(const char* asset, SDL_Rect data,bool enabled,std::function<void(void)> callback);
    void updateImage(const char* asset);
    void updatePosition(int x, int y);
    void updateSize(int w, int h);
    SDL_Rect getImageData() { return _imageRect; }
    virtual void handleClick(int x, int y);
    virtual void render();
    void setEnable(bool enable) { _enabled = enable; }
    bool getEnable() { return _enabled; }
private:
    SDL_Texture* _image;
    SDL_Rect _imageRect;
    std::function<void(void)> _callback;
    bool _enabled;
};

