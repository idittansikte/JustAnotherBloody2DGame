#include "MovingGameObject.h"

#include <iostream>
#include <math.h>

void MovingGameObject::Init(Point startpos, int uniquetag)
{
  GameObject::Init(startpos, uniquetag);
  m_start_position = startpos;
}

void MovingGameObject::Reset(){
  GameObject::Reset();
  vx = 0;
  vy = 0;
  ax = 1.0;
  ay = 0.5;
  contactTop = false;
  contactBottom = false;
  contactLeft = false;
  contactRight = false;
  updatePos(m_start_position);
}

bool MovingGameObject::collidedFromLeft(GameObject* otherObject)
{
  Rect<int> A = this->getCollisionRect();
  Rect<int> B = otherObject->getCollisionRect();
    return m_previous_position.x + A.w <= B.x && // was not colliding
           A.x + A.w > B.x;
}

bool MovingGameObject::collidedFromRight(GameObject* otherObject)
{
  Rect<int> A = this->getCollisionRect();
  Rect<int> B = otherObject->getCollisionRect();
    return m_previous_position.x >= B.x + B.w && // was not colliding
           A.x < B.x + B.w;
}

bool MovingGameObject::collidedFromTop(GameObject* otherObject)
{
  Rect<int> A = this->getCollisionRect();
  Rect<int> B = otherObject->getCollisionRect();
    return m_previous_position.y + A.h <= B.y && // was not colliding
           A.y + A.h > B.y;
}

bool MovingGameObject::collidedFromBottom(GameObject* otherObject){
  Rect<int> A = this->getCollisionRect();
  Rect<int> B = otherObject->getCollisionRect();
    return m_previous_position.y >= B.y + B.h && // was not colliding
           A.y < B.y + B.h;
}

void MovingGameObject::HandleCollision(GameObject* otherObject)
{
  GameObject::HandleCollision(otherObject);
  

  
  if ( this->getType() != GameObject::PROJECTILE && otherObject->getType() != GameObject::PROJECTILE ){
    
      Rect<int> A = this->getCollisionRect();
      Rect<int> B = otherObject->getCollisionRect();
      
    if ( collidedFromTop(otherObject) ){ //Collied  top
      m_previous_position.y = B.y-A.h;
      updatePos_y( m_previous_position.y );
      contactBottom = true;
    }
    
    if ( collidedFromBottom(otherObject) ){
      m_previous_position.y = B.y + B.h;
      updatePos_y( m_previous_position.y );
      contactTop = true;
    }
    
    if ( collidedFromLeft(otherObject) ){
      m_previous_position.x = B.x-A.w;
      updatePos_x(m_previous_position.x);
      contactRight = true;
    }
    
    if ( collidedFromRight(otherObject) ){
      m_previous_position.x = B.x+B.w;
      updatePos_x(m_previous_position.x);
      contactLeft = true;
    }
  }
}

void MovingGameObject::PhysicHandler(){
  
    if( vy < vy_max ){ // Max fallspeed
      vy += ay;
    }
    
    if ( contactBottom ){ // Reset if contact with feets, otherwise it will never reset,,
      vy = 0;
    }
    
    //Friction
    if( m_current_direction == LEFT ){
      if(vx < 0)
	vx += m_ground_friktion;
      else
	vx = 0;
    }
    
    if( m_current_direction == RIGHT ){
      if (vx > 0)
	vx -= m_ground_friktion;
      else
	vx = 0;
    }
}

void MovingGameObject::turnOn_falling(){
  m_falling = true;
}

void MovingGameObject::turnOff_falling(){
  m_falling = false;
}

void MovingGameObject::CleanupFrame(){
  contactTop = false;
  contactBottom = false;
  contactLeft = false;
  contactRight = false;
}

void MovingGameObject::Update()
{
  apply_velocity_x(vx);
  apply_velocity_y(vy);
  
  GameObject::Update();
}

void MovingGameObject::Draw(Renderer* renderer)
{
    GameObject::Draw(renderer);
}

void MovingGameObject::apply_velocity_x(float x_){
  Rect<int> A = this->getCollisionRect();
  int x = round(x_);
  
  this->m_previous_position.x = A.x ;
  this->updatePos_x( A.x + x );
}

void MovingGameObject::apply_velocity_y(float y_){
  Rect<int> A = this->getCollisionRect();
  int y = round(y_);
  
  this->m_previous_position.y = A.y;
  updatePos_y( A.y + y);
}

void MovingGameObject::SetDirection(Direction dir){
  m_current_direction = dir;
}

void MovingGameObject::ChangeDirection(){
  if(m_current_direction == RIGHT)
    m_current_direction = LEFT;
  else
    m_current_direction = RIGHT;
}

Direction MovingGameObject::GetDirection(){
  return m_current_direction;
}

