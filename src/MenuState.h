#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <SDL2/SDL.h>

#include "Renderer.h"
#include "GameState.h"
#include "Game.h"

class MenuState : public GameState
{
  public:
    
    void Init();
    void Clean();
    
    void Pause();
    void Resume();
    
    void HandleEvents(Game* game);
    void Update(Game* game);
    void Draw(Game* game, Renderer* renderer);
    
    static MenuState* Instance()
    {
      return &m_MenuState;
    }
  protected:
    
    MenuState() { }
    
  private:
    static MenuState m_MenuState;
};

#endif