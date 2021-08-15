#pragma once

#include "Component.h"
#include <vector>
#include<memory>
#include"SDL.h"
#include "Constants.h"
class ComponentManager {

public:
    static SDL_Event _event;
    static SDL_Renderer* _renderer;

    static ComponentManager* getComponentManager()
    {
        static ComponentManager *instance = new ComponentManager(); // Guaranteed to be destroyed.
        return instance;
    }

    template<class T, typename... Args>
    std::shared_ptr<T> createComponent(const Args&&... args)
    {   
        _components.push_back(std::make_shared<T>(args...));
        return std::dynamic_pointer_cast<T>(_components.back());
    }
    void render();
    void update();
    void handleEvent();

private:
    ComponentManager() {};
    ComponentManager(ComponentManager const&) {};
    void operator=(ComponentManager const&) {};
    std::vector<std::shared_ptr<Component>> _components;

};

