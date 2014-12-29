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
    
  Player( Rect r, Rect c, GameObject::ObjectType otype, std::string texturePath, int uniqueID );
  
  void Init();
  
  void HandleCollision(GameObject* otherObject) override;
  
  void Update();
  
  void Draw(Renderer* renderer);
  
  void Clean();
  
  void movement_left();
  void movement_right();
  void movement_up();
  void movement_down();
  
  void JumpHandler();
  
  private:
    
  const float m_jump_start_velocity;
  
  bool m_want_jump; 
  bool m_doubleJump_used;
  
  // PlayerState* currentState;
  
};

#endif