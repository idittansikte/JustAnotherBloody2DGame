#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include <SDL2/SDL.h>

#include "GameState.h"
#include "Renderer.h"
#include "Input.h"

class PauseState : public GameState
{
  public:
    
    void Init();
    void Clean();
    
    void Pause();
    void Resume();
    
    void HandleEvents(Game* game);
    void Update(Game* game);
    void Draw(Game* game, Renderer* renderer);
    
    static PauseState* Instance()
    {
      return &m_PauseState;
    }
  protected:
    
    PauseState() { }
    
  private:
    static PauseState m_PauseState;
    
    SDL_Surface* pauseSprite;
};

#endif