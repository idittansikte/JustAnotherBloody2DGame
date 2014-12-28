#include "Player.h"

#include <iostream>

Player::Player( Rect r, GameObject::ObjectType otype, std::string texturePath, int uniqueID ) :
  MovingGameObject(r, otype, texturePath, uniqueID),
  m_current_walking_speed(4.0),
  m_jump_start_velocity(8.0),
  m_jumping(false),
  m_want_jump(false),
  vx(0),
  vy(0)
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
  
  MovingGameObject::Update();
  
  JumpHandler();
  
  apply_velocity_x(vx);
  
  apply_gravitaion();
  CleanupFrame();
  vx = 0;
}

void Player::Draw(Renderer* renderer)
{
  GameObject::Draw(renderer);
}

void Player::Clean()
{
  
}

void Player::movement_left(){
	vx -= m_current_walking_speed;	
}

void Player::movement_right(){
	vx += m_current_walking_speed;
}

void Player::movement_up(){
  m_want_jump = true;
}

void Player::movement_down(){
  // Ducka...
  // apply_velocity_y(m_current_walking_speed);
}

void Player::try_enable_jump(){
  //gravityOff();
  if(m_want_jump){
    if (contactBottom == true){ // Start jumping procedure
      m_jumping = true;
      m_jump_current_velocity = m_jump_start_velocity;
    }
    m_want_jump = false;
  }
}

void Player::JumpHandler(){
  
  if(!m_jumping){
    try_enable_jump();
  }
  else{ // If jumping is enabled
    if( !contactTop ) // If player haven't collied with his head.
    {
      if(m_jump_current_velocity > 0){
		apply_velocity_y(-m_jump_current_velocity); // Fix the real gravitation instead of 2
		m_jump_current_velocity -= 0.4;
		m_current_fallspeed = 0;
      }
      else{
		m_jumping = false;
      }
    }
    else{
	  //apply_velocity_y(m_jump_current_velocity);
      m_jumping = false; //Disable jumping if contact with head...
      //turnOn_falling();
    }
  }
}