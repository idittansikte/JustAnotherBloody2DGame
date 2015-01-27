#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "GameState.h"
#include "Renderer.h"
#include "Input.h"
#include "LevelData.h"

class Level;

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
    void DrawCursor(Renderer* renderer);
    
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