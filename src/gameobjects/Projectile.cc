#include "Projectile.h"

#include <iostream>
#include <cmath>

Projectile::Projectile(
	Rect<int> r,
	Rect<int> c,
	std::string texturePath,
	int uniqueID,
	int distance,
	bool immune,
	int health,
	float velocity
	):
    MovingGameObject( r, c, texturePath, uniqueID, immune, health, 0 ), m_distance(distance), m_velocity(velocity)
  {}
  

void Projectile::Init( GameObject* shooter, int uniqueTag, Point startpos, Point targetpos, float angle )
{
  m_shooter = shooter;
  updatePos(startpos);
  changeUniqueTag(uniqueTag);
  
  if(targetpos.x == 0 && targetpos.y == 0){
    m_angle = angle;
  }
  else{
    //Calculate angle of direction
    int deltaX = targetpos.x - startpos.x;
    int deltaY = targetpos.y - startpos.y;
    m_angle = ( atan2(deltaY,deltaX) * 180 ) / 3.14;
  }
      m_startPos = Point(startpos.x, startpos.y);
}
    
void Projectile::HandleCollision(GameObject* otherObject){
  if(m_shooter->getType() != otherObject->getType() && this->getType() != otherObject->getType()){ // not if projectile hits own kind
    this->setDead();
    if(m_shooter != nullptr)
      otherObject->DrainHealth( m_shooter->getDamage() );
  }
}

void Projectile::Update(){
  
  Rect<int> pos = this->getRect();
  // Calculate distance between now and startpos
  double distance = sqrt( (pos.x - m_startPos.x)*(pos.x - m_startPos.x) + (pos.y - m_startPos.y)*(pos.y - m_startPos.y) );

  if( distance > m_distance )
    this->setDead();

  if(isDead())
    return;
  
  Point centerSize(pos.w/2, pos.h/2);
  
  float newPosx = pos.x + m_velocity * cos(m_angle * 3.14/180);
  float newPosy = pos.y + m_velocity * sin(m_angle * 3.14/180);
  
  updatePos(Point(newPosx, newPosy));
}

void Projectile::Draw(Renderer* renderer){
  
  Rect<int> pos = this->getRect();
  Point centerSize(pos.w/2, pos.h/2);
  
  if(!isDead()){
    renderer->drawTexture( pos, this->getTexturePath(), true, Rect<int>(), false, false, centerSize, m_angle );
  }
  else{
    GetAnimation("DEATH")->DrawCurrentFrame(renderer, getRect());
    return;
  }
    
    
  MovingGameObject::Draw(renderer);
}

void Projectile::Clean()
{
  
}

void Projectile::Reset(){
  setDead();
}