#include "Enemy.h"

#include <iostream>

#include "Projectile.h"
#include "../ProjectileManager.h"

Enemy::Enemy(
      Rect r,
      Rect c,
      std::string texturePath,
      int uniqueID,
      bool immune,
      int health,
      int damage,
      int aggroDistance
      ):
  MovingGameObject(r, c, texturePath, uniqueID, immune, health, damage), m_aggroDistance(aggroDistance)
{
    m_bar->setBarBox(Rect( 0, 0, 100, 4));
      
    m_projectile = nullptr;
    m_intervall = 0;
    m_target = nullptr;
    m_timer.start();
    SetDirection(LEFT);
}

void Enemy::Init(Point startpos, int uniquetag, GameObject* target)
{
  MovingGameObject::Init(startpos, uniquetag);
  m_target = target;
      // Randomzie start direction
    if( rand() % 2 == 0)
      SetDirection(LEFT);
    else
      SetDirection(RIGHT);
}

void Enemy::Reset(){
  MovingGameObject::Reset();

  if( rand() % 2 == 0)
    SetDirection(LEFT);
  else
    SetDirection(RIGHT);
    
  m_timer.reset();
  
}

void Enemy::HandleCollision(GameObject* otherObject)
{
  MovingGameObject::HandleCollision(otherObject);
}

void Enemy::Update()
{
  if(isDead())
    return;
  
  if( TargetInRange() ){ // if in range and a ranger
    if ( m_projectile != nullptr ){
      RangeAttackFocus();
    }
    else{
      CombatAttackFocus();
    }
  }
  else{
    Idle();
  }
  
  MovingGameObject::Update();
  CleanupFrame();
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

void Enemy::setProjectile(Projectile* projectile, int intervall){
  
  m_projectile = projectile;
  m_intervall = intervall;
  
}

bool Enemy::TargetInRange(){
  Point targetpos = m_target->getCenterPos();
  Point thispos = this->getPos();
  
  double distance = sqrt( (thispos.x - targetpos.x)*(thispos.x - targetpos.x) + (thispos.y - targetpos.y)*(thispos.y - targetpos.y) );

  return ( distance < m_aggroDistance );
}

void Enemy::MakeAttack(){
  if(m_timer.getMillisecondsFromStart() > m_intervall){
    m_timer.reset();
    if( m_target != nullptr ){
      if( TargetInRange() ){
	  if( m_projectile != nullptr ){
	    
	      Point targetpos = m_target->getCenterPos();
	      Rect thisrect = this->getRect();
  
	      Projectile* clone = m_projectile->Clone();
	      
	    if( GetDirection() == RIGHT ){
	      int deltaX = targetpos.x - (thisrect.x+thisrect.w);
	      int deltaY = targetpos.y - (thisrect.y+(thisrect.h/2));
	      m_angle = ( atan2(deltaY,deltaX) * 180 ) / 3.14;
	      
	      clone->Init(this, 500, Point(thisrect.x+thisrect.w, thisrect.y+(thisrect.h/2)), Point(), m_angle );
	      ProjectileManager::getInstance()->AddProjectile(clone);
	    }
	    else if ( GetDirection() == LEFT ){
	      int deltaX = targetpos.x - thisrect.x;
	      int deltaY = targetpos.y - (thisrect.y+(thisrect.h/2));
	      m_angle = ( atan2(deltaY,deltaX) * 180 ) / 3.14;
	      
	      clone->Init(this, 500, Point(thisrect.x, thisrect.y+(thisrect.h/2)), Point(), m_angle );
	      ProjectileManager::getInstance()->AddProjectile(clone);
	    }	
	  }
      }
    }
  }
}

void Enemy::Idle(){
  
  Rect r = getRect();
  Point startpos = GetStartPos();
  MakeMovement();
  
    if( r.x >= startpos.x + 200 || contactRight){
      SetDirection(LEFT);
    }
    else if( r.x <= startpos.x - 200 || contactLeft){
      SetDirection(RIGHT);
    }
}

void Enemy::RangeAttackFocus(){
  
    Point r = getCenterPos();
    Point targetrect = m_target->getCenterPos();
    
    MakeAttack();
    
    if( targetrect.x <= r.x ) // Target on left side
      SetDirection(LEFT);
    else
      SetDirection(RIGHT);
    
    if( ( r.x < targetrect.x - 200 || r.x > targetrect.x + 200 ) ){ // if not close enought from target
      MakeMovement();
    }
    else
      vx = 0;
}

void Enemy::CombatAttackFocus(){
  
}

void Enemy::MakeMovement(){
  
  Rect r = getRect();
  Point startpos = GetStartPos();
  
  if(GetDirection() == LEFT){
    if(vx >= -(ax*5))
      vx -= ax;
  }
  else{
    if(vx <= ax*5)
      vx += ax;
  }
  // Check if outside of spawn
  if( r.x > startpos.x + 200 ){ // If too far to the right
    this->updatePos_x(startpos.x + 200);
    vx = 0;
  }
  else if( r.x < startpos.x - 200 ){ // If too far to the left
    this->updatePos_x(startpos.x - 200);
    vx = 0;
  }
}

void Enemy::SetMaxMovementRight(int max){
  m_max_movement_right = max;
}

void Enemy::SetMaxMovementLeft(int max){
  m_max_movement_left = max;
}

int Enemy::GetMaxMovementRight(){
  return m_max_movement_right;
}

int Enemy::GetMaxMovementLeft(){
  return m_max_movement_left;
}