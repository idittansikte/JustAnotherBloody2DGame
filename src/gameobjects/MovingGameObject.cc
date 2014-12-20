#include "MovingGameObject.h"

void MovingGameObject::Init()
{
  
}

void MovingGameObject::HandleCollision(GameObject* otherObject)
{
  
}

void MovingGameObject::Update()
{

}

void MovingGameObject::Draw(Renderer* renderer)
{
  
}

void MovingGameObject::Clean()
{
  
}

void MovingGameObject::add_pos_x(int x){
  this->m_previous_position = Point(this->getPoint().x, this->m_previous_position.y );
  this->updatePos( Point(this->getRect().x + x, this->getRect().y));
}

void MovingGameObject::add_pos_y(int y){
  this->m_previous_position = Point(this->m_previous_position.x, this->getPoint().y);
  updatePos( Point(getRect().x, getRect().y + y));
}