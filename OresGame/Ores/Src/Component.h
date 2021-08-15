#pragma once

class Component
{
public:
    virtual void render() {};
    virtual void update() {};
    virtual void handleEvent() {};
    virtual void handleClick(int x,int y) {};
};