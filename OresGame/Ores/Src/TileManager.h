#pragma once

#include<vector>
#include<memory>
#include<map>
#include<algorithm>
#include"SDL.h"
#include "SDL_image.h"
#include "OresGame.h"
#include "TextureManager.h"
#include "ComponentManager.h"
#include "Tiles.h"
#include "Constants.h"

class Tiles;
class TileManager:public Component
{
public:
    TileManager(int totalRow,  int totalCol);
    void init(int xPos, int yPos, int tileH, int tileW ,int visibleCol);
    void reduceGroupXPosition();
    virtual void handleClick(int x, int y);
    int getTotalBrokenTile() { return _totalBrokenTiles; }
    int getTotalVisibleColum() { return _visibleCol; }
    void setEnable(bool enable) { _enabled = enable; }
    void levelUp(int visibleCol);

private:
    int _groupPosX;
    int _groupPosY;
    int _tileH;
    int _tileW;
    int _totalRow;
    int _totalCol;
    int _visibleCol;
    int _totalBrokenTiles;
    bool _isUpdateRequired;
    bool _enabled;
    std::map<int, std::string> _tileAssetMap;
    std::vector<std::vector<std::shared_ptr<Tiles>>> _tileArray;
    void handleTilePressed(int x, int y);
    bool processTilePressed(int row, int colum);
    int removeTile(int index, int row, int colum);
    void updateTilePositions();
    void updateColumIndex();
    int updateRowIndex();
    std::vector<int> getEmptyColum();
    void fillEmptyData(int columSize);
    void refreshTilePositions(int startRow, int startCol, bool force = false);
    int getTotalVisibleTiles();

};

