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
    
  Player( Rect r, GameObject::ObjectType otype, std::string texturePath, int uniqueID );
  
  void Init();
  
  void HandleCollision(GameObject* otherObject) override;
  
  void Update();
  
  void Draw(Renderer* renderer);
  
  void Clean();
  
  void movement_left();
  void movement_right();
  void movement_up();
  void movement_down();
  
  void try_enable_jump();
  void JumpHandler();
  
  private:
    
  float vx;
  float vy;
  //const int m_normal_movement_speed;
  float m_current_walking_speed;
  const float m_jump_start_velocity;
  float m_jump_current_velocity;
  bool m_want_jump; 
  bool m_jumping;
  
  // PlayerState* currentState;
  
};

#endif