#include "Player.h"


void Player::Init()
{
  
}

void Player::HandleCollision(GameObject* otherObject)
{
  if ( otherObject->getObjectType() == GameObject::PLATFORM )
}

void Player::Update()
{
  ;
}

void Player::Draw(Renderer* renderer)
{
  GameObject::Draw(renderer);
}

void Player::Clean()
{
  
}

void Player::movement_left(){
  add_pos_x((-1)*m_current_walking_speed);
}
void Player::movement_right(){
  add_pos_x(m_current_walking_speed);
}

void Player::movement_up(){
  add_pos_y((-1)*m_current_walking_speed);
}

void Player::movement_down(){
  add_pos_y(m_current_walking_speed);
}