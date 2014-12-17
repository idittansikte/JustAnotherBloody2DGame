#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "GameState.h"
#include "Renderer.h"
#include "Level.h"
#include "Input.h"

class PlayState : public GameState
{
  public:
    
    void Init();
    void Clean();
    
    void Pause();
    void Resume();
    
    void HandleEvents(Game* game);
    void Update(Game* game);
    void Draw(Game* game, Renderer* renderer);
    
    static PlayState* Instance()
    {
      return &m_PlayState;
    }
  protected:
    
    PlayState();
    
  private:
    static PlayState m_PlayState;
    Level* m_Level;
    
    bool m_is_paused;
};

#endif