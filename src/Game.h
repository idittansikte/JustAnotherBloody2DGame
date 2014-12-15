#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Renderer.h"

class GameState;

class Game
{
  public:
    Game();
    ~Game(){};
    
    void Init();
    
    void ChangeState(GameState* state);
    void PushState(GameState* state);
    void PopState();
    
    void HandleEvents();
    
    void Update();
    
    void Draw();
    
    void Clean();
    
    bool Running(){ return m_bRunning; }
    void Quit() { m_bRunning = false; }
    
  private:
    
    
    
    std::vector<GameState*> m_vStates;
    
    bool m_bRunning;
    bool m_bFullscreen;
    
    Renderer* mRenderer;
};

#endif