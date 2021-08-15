#include "ComponentManager.h"

SDL_Renderer* ComponentManager::_renderer = nullptr;
SDL_Event ComponentManager::_event;


void ComponentManager::render()
{
    for (auto component : _components)
    {
        component->render();
    }
}
void  ComponentManager::update()
{
    for (auto component : _components)
    {
        component->update();
    }
}
void  ComponentManager::handleEvent()
{
    static bool pressed = false;
    bool click = false;
    switch (_event.type)
    {
    case SDL_MOUSEBUTTONDOWN:
    {
        pressed = true;
        break;
    }
    case SDL_MOUSEBUTTONUP:
    {
        if (pressed)
        {
            pressed = false;
            click = true;
        }
        break;
    }
    default:
    {
        break;
    }
    }

    for (auto component : _components)
    {
        component->handleEvent();
        if(click) component->handleClick(_event.button.x,_event.button.y);
    }
}