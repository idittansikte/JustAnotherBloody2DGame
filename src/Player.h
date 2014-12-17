#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "Renderer.h"
#include "MovingGameObject.h"
#include "Rect.h"
#include "Constants.h"

class Player : public MovingGameObject
{
  public:
    
  Player( Rect r, GameObject::ObjectType otype, std::string texturePath, int uniqueID )
    : MovingGameObject(r, otype, texturePath, uniqueID)
  {}
  
  void Init();
  
  void Update();
  
  void Draw(Renderer* renderer);
  
  void Clean();
  
  private:

};

#endif