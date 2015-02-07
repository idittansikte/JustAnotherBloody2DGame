#include "Game.h"
#include "gameobjects/GameObjectManager.h"
#include "MenuState.h"
#include "GameState.h"
#include <iostream>

int main(int argc, char* argv[])
{
  GameObjectManager::Instance()->loadGameObjectsFromFile();
  Game game;
  
  game.Init();
  
  game.ChangeState(MenuState::Instance());
  
  while(game.Running())
  {
    game.HandleEvents();
    game.Update();
    game.Draw();
  }

  // cleanup game
  game.Clean();
  
  return 0;
}