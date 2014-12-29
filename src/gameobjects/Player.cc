#include "Player.h"

#include <iostream>

Player::Player( Rect r, Rect c, GameObject::ObjectType otype, std::string texturePath, int uniqueID ) :
  MovingGameObject(r, c, otype, texturePath, uniqueID),
  m_jump_start_velocity(12.0),
  m_want_jump(false),
  m_doubleJump_used(false)
  {}

void Player::Init()
{
  
}

void Player::HandleCollision(GameObject* otherObject)
{
  
  MovingGameObject::HandleCollision(otherObject);
}

void Player::Update()
{
  apply_gravitaion();
  
  JumpHandler();
  
  CleanupFrame();
  
  MovingGameObject::Update(); // Applying velocity
}

void Player::Draw(Renderer* renderer)
{
  GameObject::Draw(renderer);
}

void Player::Clean()
{
  
}

void Player::movement_left(){
  if (vx > -vx_max)
    vx -= ax;
}

void Player::movement_right(){
  if (vx < vx_max)
    vx += ax;
}

void Player::movement_up(){
  m_want_jump = true;
}

void Player::movement_down(){
  // Ducka...
  // apply_velocity_y(m_current_walking_speed);
}

void Player::JumpHandler(){
  
  if( contactTop ){
    vy = 0;
  }
    
  if(m_want_jump && contactBottom){ // Start jumping procedure
    
      vy = -m_jump_start_velocity;
      m_doubleJump_used = false;
  }
  else if( m_want_jump && !contactBottom && !m_doubleJump_used && vy >= -m_jump_start_velocity+4 ){ // if already in air
    vy = -m_jump_start_velocity;
    m_doubleJump_used = true;
  }
  
  m_want_jump = false;
  
}





