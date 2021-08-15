#pragma once
#include "SDL.h"

namespace constants
{
    constexpr int SCREEN_WIDHT = 800;
    constexpr int SCREEN_HEIGHT = 640;
    constexpr int FRAME_RATE = 60;


    constexpr int START_VISIBLE_COL = 6;
    constexpr int END_GAME_COL = 16;
    constexpr int TILE_HEIGHT = 40;
    constexpr int TILE_WIDTH = 40;

    constexpr SDL_Rect BackgroundImageData = { 0,0,800,640 };
    constexpr SDL_Rect GameOverImageData = { 0,0 ,800,640};
    constexpr SDL_Rect BackButtonData = { 740, 600,30, 30  };
    constexpr SDL_Rect HomeScreenImageData = { 0, 0 , 800, 640};


    constexpr SDL_Color White = { 255,255,255,255 };
    constexpr SDL_Rect ScoreTextData = { 20,25,60,15 };
    constexpr SDL_Rect ScoreData = { 80,25,60,15 };
    constexpr SDL_Rect PushTextData = { 280,25,60,15 };
    constexpr SDL_Rect CurrentLevelTextData = { 520,25,60,15 };

    constexpr SDL_Rect ProgressBarData = { 350,25,80,15 };
    constexpr SDL_Rect LevelBarData = { 600,25,80,15 };
    
}


