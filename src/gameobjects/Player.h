#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "../Renderer.h"
#include "MovingGameObject.h"
#include "../Rect.h"
#include "../Constants.h"

class Player : public MovingGameObject
{
  public:
    
  Player( Rect r, GameObject::ObjectType otype, std::string texturePath, int uniqueID )
    : MovingGameObject(r, otype, texturePath, uniqueID), m_current_walking_speed(2)
  {}
  
  void Init();
  
  void HandleCollision(GameObject* otherObject) override;
  
  void Update();
  
  void Draw(Renderer* renderer);
  
  void Clean();
  
  void movement_left();
  void movement_right();
  void movement_up();
  void movement_down();
  
  private:
    
  //const int m_normal_movement_speed;
  int m_current_walking_speed;
  
  // PlayerState* currentState;
  
};

#endif