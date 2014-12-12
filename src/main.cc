#include "Game.h"
#include "MenuState.h"
#include "GameState.h"

#include <iostream>

int main(int argc, char* argv[])
{
  Game game;
  
  GameInst::Instance()->Init();
  
  GameInst::Instance()->ChangeState(MenuState::Instance());
  
  while(game.Running())
  {
    GameInst::Instance()->HandleEvents();
    GameInst::Instance()->Update();
    GameInst::Instance()->Draw();
  }

  // cleanup game
  GameInst::Instance()->Clean();
  
  return 0;
}