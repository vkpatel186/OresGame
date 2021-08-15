#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* file_name)
{
    SDL_Surface* tempSurface = IMG_Load(file_name);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ComponentManager::_renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    return tex;
}
