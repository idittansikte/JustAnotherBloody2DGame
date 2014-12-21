#include "MovingGameObject.h"

#include <iostream>
#include <math.h>

void MovingGameObject::Init()
{
  
}

bool MovingGameObject::collidedFromLeft(GameObject* otherObject)
{
    return m_previous_position.x + this->getWidth() < otherObject->getPos_x() && // was not colliding
           getPos_x() + this->getWidth() > otherObject->getPos_x();
}

bool MovingGameObject::collidedFromRight(GameObject* otherObject)
{
    return m_previous_position.x > otherObject->getPos_x() + otherObject->getWidth() && // was not colliding
           this->getPos_x() < otherObject->getPos_x() + otherObject->getWidth();
}

bool MovingGameObject::collidedFromTop(GameObject* otherObject)
{
    return m_previous_position.y + this->getHeight() < otherObject->getPos_y() && // was not colliding
           this->getPos_y() + this->getHeight() >= otherObject->getPos_y();
}

bool MovingGameObject::collidedFromBottom(GameObject* otherObject)
{
    return m_previous_position.y > otherObject->getPos_y() + otherObject->getHeight() && // was not colliding
           this->getPos_y() <= otherObject->getPos_y() + otherObject->getHeight();
}

void MovingGameObject::HandleCollision(GameObject* otherObject)
{
  Rect this_r = this->getRect();
  Rect other_r = otherObject->getRect();
  
  
  if ( otherObject->getObjectType() == GameObject::PLATFORM ){
    
    if ( collidedFromTop(otherObject) ){ //Collied  top
      updatePos_y( otherObject->getPos_y() );
      contactBottom = true;
      turnOff_falling();
    }
    
    if ( collidedFromBottom(otherObject) ){ 
      updatePos_y(m_previous_position.y);
      contactTop = true;
    }
    
    if ( collidedFromLeft(otherObject) ){ 
      updatePos_x(m_previous_position.x);
      contactRight = true;
    }
    
    if ( collidedFromRight(otherObject) ){ 
      updatePos_x(m_previous_position.x);
      contactLeft = true;
    }
  }
}

void MovingGameObject::apply_physics(){
  if ( m_falling && !contactBottom ){
  
    if( m_current_fallspeed < m_max_fallspeed ){
      m_current_fallspeed += 0.5;
    }
    
    apply_velocity_y(m_current_fallspeed);
  }
}

void MovingGameObject::turnOn_falling(){
  m_current_fallspeed = 0;
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
  turnOn_falling(); // Always turn on falling to next frame..
}

void MovingGameObject::Update()
{
  
  //If moving object is outside world, move back. --->>>> world height and world width need to be implemented!
  Rect r = this->getRect();
  if ( r.x < 0 || r.y < 0 )
  {
    if (r.x < 0 && r.y < 0)
      updatePos(m_previous_position);
    else if ( r.x < 0 )
      updatePos_x(m_previous_position.x);
    else
      updatePos_y(m_previous_position.y);
  }
  
  apply_physics();
  
  //CleanupFrame(); // Reset all collie booleans for next frame... 
}

void MovingGameObject::Draw(Renderer* renderer)
{
  
}

void MovingGameObject::Clean()
{
  
}

void MovingGameObject::apply_velocity_x(float x_){
  int x = round(x_);
  this->m_previous_position = Point(this->getPoint().x, this->m_previous_position.y );
  this->updatePos( Point(this->getRect().x + x, this->getRect().y));
}

void MovingGameObject::apply_velocity_y(float y_){
  int y = round(y_);
  this->m_previous_position = Point(this->m_previous_position.x, this->getPoint().y);
  updatePos( Point(getRect().x, getRect().y + y));
}