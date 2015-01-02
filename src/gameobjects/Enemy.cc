#include "Enemy.h"

#include <iostream>

Enemy::Enemy(
      Rect r,
      Rect c,
      GameObject::ObjectType otype,
      std::string texturePath,
      int uniqueID,
      bool immune,
      int health,
      int damage
      ):
  MovingGameObject(r, c, otype, texturePath, uniqueID, immune, health, damage), m_start_position(Point(r.x, r.y))
{
    m_bar->setBarBox(Rect( 0, 0, 100, 4));
    // Randomzie start direction
    if( rand() % 2 == 0){
      SetDirection(LEFT);
    }
    else
      SetDirection(RIGHT);
      
  
}

void Enemy::Init()
{
  
}

void Enemy::HandleCollision(GameObject* otherObject)
{
  MovingGameObject::HandleCollision(otherObject);
}

void Enemy::Update()
{
  
  Rect r = getRect();
  if( GetDirection() == RIGHT && !isDead()){
    if( r.x > m_start_position.x + 200 ){
      ChangeDirection();
      vx = 0;
      return;
    }
    if(vx <= ax*5)
      vx += ax;
    
  }
  else{
    if( r.x < m_start_position.x - 200 && !isDead() ){
      ChangeDirection();
      vx = 0;
      return;
    }
    if(vx >= -ax*5)
      vx -= ax;
  }
  
  MovingGameObject::Update();
}

void Enemy::Draw(Renderer* renderer)
{
    if(!isDead()){
      if( GetDirection() == RIGHT )
	GetAnimation("WALK")->DrawCurrentFrame(renderer, getRect(), true);
      else
	GetAnimation("WALK")->DrawCurrentFrame(renderer, getRect(), false);
    }
    else{
      if( GetDirection() == RIGHT )
	GetAnimation("DEATH")->DrawCurrentFrame(renderer, getRect(), true);
      else
	GetAnimation("DEATH")->DrawCurrentFrame(renderer, getRect(), false);
      return;
    }
    MovingGameObject::Draw(renderer);
}

void Enemy::Clean()
{
  
}