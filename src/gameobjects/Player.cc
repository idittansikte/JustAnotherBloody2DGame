#include "Player.h"

#include <iostream>

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
  
  CleanupFrame();
}

void Player::Draw(Renderer* renderer)
{
  GameObject::Draw(renderer);
}

void Player::Clean()
{
  
}

void Player::movement_left(){
  apply_velocity_x(-m_current_walking_speed);
}
void Player::movement_right(){
  apply_velocity_x(m_current_walking_speed);
}

void Player::movement_up(){
  m_want_jump = true;
}

void Player::movement_down(){
  // Ducka...
  //apply_velocity_y(m_current_walking_speed);
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
    turnOff_falling();
    if( !contactTop ) // If player haven't collied with his head.
    {
      if(m_jump_current_velocity > 0){
	apply_velocity_y(-m_jump_current_velocity);
	m_jump_current_velocity -= 0.5;
      }
      else{
	m_jumping = false;
      }
    }
    else{
      m_jumping = false; //Disable jumping if contact with head...
      //turnOn_falling();
    }
  }
}