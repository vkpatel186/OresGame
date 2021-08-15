#ifndef ORES_GAME
#define ORES_GAME
#include<iostream>
#include"Ores.h"
#include"SDL.h"
#include "ComponentManager.h"

class Ores;
class OresGame: public Component
{
public:
	OresGame();
	~OresGame();

	void init(const char* title, int xpos, int ypos, int width, int height, bool isFullScreen);
	virtual void update();
	virtual void handleEvent();
	void clean();
	bool running() { return _isRunning; }

private:
	bool _isRunning;
	SDL_Window* _window;
	std::shared_ptr<Ores> _game;
	
};

#endif // !ORES_GAME
