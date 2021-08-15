#include "OresGame.h"
#include "TextureManager.h"
#include "ComponentManager.h"
#include "Constants.h"
#include <time.h>
using namespace constants;

int main(int argc, char* argv[])
{
    srand(time(NULL));
    const int framedelay = 1000 / FRAME_RATE;
    std::shared_ptr<OresGame> game = ComponentManager::getComponentManager()->createComponent<OresGame>();
    Uint32 frameStart;
    int frameTime;

    game->init("OresGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDHT, SCREEN_HEIGHT, false);
    while (game->running())
    {
        frameStart = SDL_GetTicks();
        ComponentManager::getComponentManager()->handleEvent();
        ComponentManager::getComponentManager()->update();
        SDL_RenderClear(ComponentManager::_renderer);
        ComponentManager::getComponentManager()->render();
        SDL_RenderPresent(ComponentManager::_renderer);
        frameTime = SDL_GetTicks() - frameStart;
        if (framedelay > frameTime)
        {
            SDL_Delay(framedelay - frameTime);
        }
    }
    game->clean();
    return 0;
}
