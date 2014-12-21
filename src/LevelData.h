#ifndef LEVELDATA_H
#define LEVELDATA_H

#include <vector>
#include <string>

#include "gameobjects/GameObject.h"
#include "gameobjects/Player.h"

struct LevelData
{
  LevelData(){}
  
  vector<GameObject*> vMoving;
  vector<GameObject*> vStatics;
  vector<GameObject*> vBackgrounds;
  vector<GameObject*> vDecorations;
  
  Player* pPlayer;
  
  int levelWidth;
  int levelHeight;
  
  std::string levelName;
};

#endif