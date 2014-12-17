#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Game.h"
#include "Renderer.h"
#include "Input.h"

class GameState
{
  public:
    
    virtual void Init() = 0;
    virtual void Clean() = 0;
    
    virtual void Pause() = 0;
    virtual void Resume() = 0;
    
    virtual void HandleEvents(Game* game) = 0;
    virtual void Update(Game* game) = 0;
    virtual void Draw(Game* game, Renderer*) = 0;
    
    void ChangeState(Game* game, GameState* state){
      game->ChangeState(state);
    }
  protected:
    GameState() { }
};
#endif