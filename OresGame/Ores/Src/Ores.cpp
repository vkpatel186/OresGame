#include "Ores.h"
using namespace constants;

Ores::Ores():
    _progressTime(10000)
{
    _backgroundImage = ComponentManager::getComponentManager()->createComponent< CanvasImage>();
    _progressTexture = ComponentManager::getComponentManager()->createComponent<ProgressTexture>();
    _levelTexture = ComponentManager::getComponentManager()->createComponent<ProgressTexture>();
    _tileManager = ComponentManager::getComponentManager()->createComponent< TileManager>(10, 18);
    _increaseTiles = ComponentManager::getComponentManager()->createComponent< CanvasImage>();
    _currentLevelText = ComponentManager::getComponentManager()->createComponent<Text>();
    _pushText = ComponentManager::getComponentManager()->createComponent<Text>();   
    _homeScreenImage = ComponentManager::getComponentManager()->createComponent< CanvasImage>();
    _gameOverImage = ComponentManager::getComponentManager()->createComponent< CanvasImage>();
    _scoreText = ComponentManager::getComponentManager()->createComponent<Text>();
    _score = ComponentManager::getComponentManager()->createComponent<Text>();
}

void Ores::init()
{
    if (ComponentManager::_renderer)
    {
        _levelData = { 1,0,20 };
        _backgroundImage->init("Assets/background.png", BackgroundImageData ,false, []() {});
        _gameOverImage->init("", GameOverImageData, false, [this]() {init(); });
        _scoreText->init(White, ScoreTextData, { "Font/SHOWG.TTF",15 }, "SCORE:");
        _score->init(White, ScoreData, { "Font/SHOWG.TTF",15 }, "0");
        _pushText->init(White, PushTextData, { "Font/SHOWG.TTF",15 }, "PUSH:");
        _progressTexture->init(ProgressBarData);
        _currentLevelText->init(White, CurrentLevelTextData, {"Font/SHOWG.TTF",15}, "Level: 1");
        _levelTexture->init(LevelBarData);
        _tileManager->init(SCREEN_WIDHT -(START_VISIBLE_COL * TILE_WIDTH), 123, TILE_HEIGHT, TILE_WIDTH, START_VISIBLE_COL);
        _increaseTiles->init("Assets/backArrow.PNG", BackButtonData, false,[this]() {_tileManager->reduceGroupXPosition(); });
        _homeScreenImage->init("Assets/startGame.png", HomeScreenImageData, true ,
            [this]() {
                _tileManager->setEnable(true); 
                _increaseTiles->setEnable(true);
                _homeScreenImage->updateImage(""); 
                _homeScreenImage->setEnable(false);
            });
    }
}

void Ores::update()
{

    //Check If game is over
    if (_tileManager->getTotalVisibleColum() > END_GAME_COL)
    {
        _gameOverImage->setEnable(true);
        _homeScreenImage->updateImage("Assets/gameover.png");

    }
    
    //Update Progress Bar
    updateProgressBar();
    updateLevelBar();
    
    //Update Score based on total broke tiles
    auto ss = std::to_string(_tileManager->getTotalBrokenTile() * 5);
    _score->updateText(ss);
    _score->updateSize(ss.size()*10,15);
}

void Ores::updateProgressBar()
{
    static Uint32 startVal = SDL_GetTicks();
    if (!_homeScreenImage->getEnable())
    {
        float percentage = 100.0f * (SDL_GetTicks() - startVal) / _progressTime;
        if (percentage >= 100.0f)
        {
            _tileManager->reduceGroupXPosition();
            startVal = SDL_GetTicks();
        }
        _progressTexture->updatePercentage(static_cast<int>(percentage));
    }
    else
    {
        startVal = SDL_GetTicks();
    }
}
void Ores::updateLevelBar()
{
    if (_levelData.brokenTileStart != _tileManager->getTotalBrokenTile())
    {
        float per = 100.0f * (_tileManager->getTotalBrokenTile() - _levelData.brokenTileStart) / _levelData.tilesTobreak;
        if (per >= 100.0f)
        {
            per = 0.0f;
            _levelData.brokenTileStart = _tileManager->getTotalBrokenTile();
            _levelData.tilesTobreak += 10;
            _levelData.level++;
            levelUp(_levelData.level);
        }
        _levelTexture->updatePercentage(static_cast<int>(per));
    }
}

void Ores::levelUp(int level)
{
    std::string ss("Level: ");
    ss = ss + std::to_string(level);
    _tileManager->levelUp(START_VISIBLE_COL);
    _levelData.brokenTileStart = _tileManager->getTotalBrokenTile();
    _currentLevelText->updateText(ss);
}