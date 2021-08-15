#pragma once
#include<memory>
#include"SDL.h"
#include "SDL_image.h"
#include "OresGame.h"
#include "TextureManager.h"
#include "ProgressTexture.h"
#include "TileManager.h"
#include "Tiles.h"
#include "ComponentManager.h"
#include "CanvasImage.h"
#include "Text.h"

class Text;
class ProgressTexture;
class TileManager;
class Tile;
class CanvasImage;

struct Level{
    int level;
    int brokenTileStart;
    int tilesTobreak;
};
class Ores:public Component
{
public:
    Ores();
    void init();
    virtual void update();
private:
    std::shared_ptr<TileManager> _tileManager;
    std::shared_ptr<ProgressTexture> _progressTexture;
    std::shared_ptr<ProgressTexture> _levelTexture;
    std::shared_ptr<CanvasImage> _increaseTiles;
    std::shared_ptr<CanvasImage> _backgroundImage;
    std::shared_ptr<CanvasImage> _homeScreenImage;
    std::shared_ptr<CanvasImage> _gameOverImage;
    std::shared_ptr<Text> _currentLevelText;
    std::shared_ptr<Text> _pushText;
    std::shared_ptr<Text> _scoreText;
    std::shared_ptr<Text> _score;
    const int _progressTime;
    Level _levelData;

    void levelUp(int level);
    void reset();
    void updateProgressBar();
    void updateLevelBar();
};

