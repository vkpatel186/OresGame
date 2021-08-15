#include "TileManager.h"

TileManager::TileManager(int totalRow,int totalCol):
     _totalRow(totalRow)
    , _totalCol(totalCol)
    , _tileAssetMap(
        {
            {0,""},
            {1,"Assets/blueTile.png"},
            {2,"Assets/redTile.png"},
            {3,"Assets/greenTile.png"},
            {4,"Assets/yellowTile.png"},
        }
    )
    , _enabled(false)
{
    _tileArray.resize(_totalRow, std::vector<std::shared_ptr<Tiles>>(_totalCol));
    for(unsigned int i = 0; i < _tileArray.size(); i++)
    {
        for(unsigned int j = 0; j < _tileArray[0].size(); j++)
        {
            _tileArray[i][j] = ComponentManager::getComponentManager()->createComponent<Tiles>();
        }
    }
}


void TileManager::init(int xPos, int yPos, int tileH, int tileW,int visibleCol)
{
    _visibleCol = visibleCol;
    _groupPosX = xPos;
    _groupPosY = yPos;
    _tileH = tileH;
    _tileW = tileW; 
    
    _totalBrokenTiles = 0;

    for(unsigned int i =0;i< _tileArray.size();i++)
    {
        for(unsigned int j = 0; j < _tileArray[0].size(); j++)
        {
            int index =( rand() % (_tileAssetMap.size() - 1)) + 1;
            _tileArray[i][j]->init(_tileAssetMap[index].c_str() ,
                index, 
                tileH, 
                tileW, 
                xPos + (j * tileW), 
                yPos + (i * tileH));
        }
    }
}

void TileManager::handleClick(int x, int y)
{
    if (_enabled)
    {
        handleTilePressed(x, y);
    }
}

void TileManager::handleTilePressed(int x, int y)
{
    for(unsigned int i = 0; i < _tileArray.size(); i++)
    {
        for(int j = 0; j < _visibleCol; j++)
        {
            if (_tileArray[i][j]->isClicked(x, y))
            {
                if (processTilePressed(i, j))
                {
                    updateTilePositions();
                }
            }
        }
    }
    
}

bool TileManager::processTilePressed(int row, int colum)
{
    bool ret = false;
    int currentIndex = _tileArray[row][colum]->getIndex();
    _tileArray[row][colum]->updateTileImageAndIndex(_tileAssetMap[0].c_str(), 0);
    int result =    removeTile(currentIndex, row + 1, colum) +
                    removeTile(currentIndex, row - 1, colum) +
                    removeTile(currentIndex, row , colum-1) +
                    removeTile(currentIndex, row , colum+1);
    if (result > 0)
    { 
        _totalBrokenTiles = _totalBrokenTiles+result +1 ;
        ret = true;
    }
    else
    {
        _tileArray[row][colum]->updateTileImageAndIndex(_tileAssetMap[currentIndex].c_str(), currentIndex);
    }
        
    return ret;
}

int TileManager::removeTile(int index, int row, int colum)
{
        if (row >= 0 && row < _totalRow && 
            colum >= 0 && colum < _visibleCol &&
            _tileArray[row][colum]->getIndex() == index)
        {
            _tileArray[row][colum]->updateTileImageAndIndex(_tileAssetMap[0].c_str(), 0);
            return(removeTile(index, row + 1, colum) +
                removeTile(index, row - 1, colum) +
                removeTile(index, row, colum - 1) +
                removeTile(index, row, colum + 1) + 1);

        }
        else
        {
            return 0;
        }
}

void TileManager::updateTilePositions()
{
    updateColumIndex();
    int emptyColum = updateRowIndex();
    _groupPosX += emptyColum * _tileW;
    _visibleCol = std::max(_visibleCol - emptyColum,0);
    refreshTilePositions(0,0);
    fillEmptyData(emptyColum);
}

void TileManager::updateColumIndex()
{
    for(unsigned int index = 0; index < _tileArray[0].size() ; index++)
    {
        unsigned int n = _tileArray.size();
        for (unsigned int i = 0; i < n; i++)
            // Last i elements are already in place 
            for (unsigned int j = 0; j < n - i -1; j++)
                if (_tileArray[j][index]->getIndex() != 0 && _tileArray[j+1][index]->getIndex() == 0)
                    std::swap(_tileArray[j][index], _tileArray[j+1][index]);
    }
}

int TileManager::updateRowIndex()
{
    //Update Only if colum is empty
    //Find empty colum
    std::vector<int> columList = getEmptyColum();
    for (auto it = columList.rbegin(); it != columList.rend(); ++it)
    {
        for(unsigned int i = 0; i < _tileArray.size(); i++)
        {
            for(unsigned int j = *it; j < _tileArray[0].size()-1; j++)
            {
                std::swap(_tileArray[i][j], _tileArray[i][j + 1]);
            }
        }
            
    }
    return columList.size();
}

std::vector<int> TileManager::getEmptyColum()
{
    std::vector<int> result;
    for(int i = 0; i < _visibleCol; i++)
    {
        bool flag = true;
        for(unsigned int j = 0; j < _tileArray.size(); j++)
        {
            flag = _tileArray[j][i]->getIndex() == 0;
            if (!flag) break;
        }
        if (flag) result.push_back(i);
    }
    return result;
}


void TileManager::fillEmptyData(int columSize)
{
    for(unsigned int i = 0; i < _tileArray.size(); i++)
    {
        for(unsigned int j = _tileArray[0].size() - columSize; j < _tileArray[0].size(); j++)
        {
            int index = (rand() % (_tileAssetMap.size() - 1)) + 1;
            _tileArray[i][j]->updateTileImageAndIndex(_tileAssetMap[index].c_str(), index);
        }
    }
    refreshTilePositions(0, _tileArray[0].size() - columSize, true);
}

void TileManager::refreshTilePositions(int startRow, int startCol, bool force)
{
    for(unsigned int i = startRow; i < _tileArray.size(); i++)
    {
        for(unsigned int j = startCol; j < _tileArray[0].size(); j++)
        {
            _tileArray[i][j]->updateDestPosition(_groupPosX + (j * _tileW), _groupPosY + (i * _tileH), force);
        }
    }
}

void TileManager::reduceGroupXPosition()
{
    _groupPosX -= _tileW;
    _visibleCol = std::min(_totalCol,_visibleCol+1);
    refreshTilePositions(0, 0);
}

void TileManager::levelUp(int visibleCol)
{
    //Add all tile in total broken tile number
    _totalBrokenTiles += getTotalVisibleTiles();

    //Make visible colum as start
    _visibleCol = visibleCol;

    //Move all tiles to out side of screen 
    _groupPosX = constants::SCREEN_WIDHT;
    refreshTilePositions(0, 0, true);

    //fill all tiles randomly
    for(unsigned int i = 0; i < _tileArray.size(); i++)
    {
        for(unsigned int j = 0; j < _tileArray[0].size(); j++)
        {
            int index = (rand() % (_tileAssetMap.size() - 1)) + 1;
            _tileArray[i][j]->updateTileImageAndIndex(_tileAssetMap[index].c_str(), index);
        }
    }
    
    //animate tiles to visible tiles
    _groupPosX = constants::SCREEN_WIDHT - (_visibleCol * _tileW);
    refreshTilePositions(0, 0);
}

int TileManager::getTotalVisibleTiles()
{
    int count = 0;
    for(unsigned int i = 0; i < _tileArray.size(); i++)
    {
        for(int j = 0; j < _visibleCol; j++)
        {
            if (_tileArray[i][j]->getIndex() != 0)
            {
                count++;
            }
        }
    }
    return count;
}