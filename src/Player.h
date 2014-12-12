#ifndef PLAYER_H
#define PLAYER_H

#include "Renderer.h"
#include "GameObject.h"
#include "Rect.h"
#include "Constants.h"

class Player : public GameObject
{
  public:
    
  Player( Rect r, Renderer::ObjectType type )
    : GameObject(r, type)
  {}
  
  void Init();
  
  void Update();
  
  void Draw(Renderer* renderer);
  
  void Clean();
  
  private:

};

#endif