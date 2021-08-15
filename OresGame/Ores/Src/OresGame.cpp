#include "OresGame.h"
#include "SDL_ttf.h"

OresGame::OresGame()
{
    _game = ComponentManager::getComponentManager()->createComponent<Ores>();
}
OresGame::~OresGame()
{
}

void OresGame::init(const char* title, int xpos, int ypos, int width, int height, bool isFullScreen)
{
    int flags = isFullScreen ? SDL_WINDOW_FULLSCREEN : 0;
   
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0 && TTF_Init()!=1)
    {
        _window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        ComponentManager::_renderer = SDL_CreateRenderer(_window, -1, 0);
        if (_window == nullptr || ComponentManager::_renderer == nullptr)
        {
            _isRunning = false;
            std::cout << "Window or ComponentManager::_renderer Creation failed" << std::endl;
        }
        _isRunning = true;

    }
    else
    {
        _isRunning = false;
    }

    _game->init();


}
void OresGame::update()
{
    SDL_SetRenderDrawColor(ComponentManager::_renderer, 255, 255, 255, 255);
}
void OresGame::handleEvent()
{

    SDL_PollEvent(&ComponentManager::_event);
    switch (ComponentManager::_event.type)
    {
    case SDL_QUIT:
    {
        _isRunning = false;
        break;
    }
    default:
        break;
    }
}
void OresGame::clean()
{
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(ComponentManager::_renderer);
    SDL_Quit();
}