#include "Projectile.h"

#include <iostream>
#include <cmath>

Projectile::Projectile(
	Rect r,
	Rect c,
	GameObject::ObjectType otype,
	std::string texturePath,
	int uniqueID,
	GameObject::ObjectType shooterType,
	Point targetPos,
	int distance,
	int speed,
	int damage,
	int immune,
	int health
	):
    MovingGameObject(r, c, otype, texturePath, uniqueID, immune, health, damage), m_shooterType(shooterType), m_distance(distance)
  {
    
    //Calculate angle of direction
    int deltaX = targetPos.x - r.x;
    int deltaY = targetPos.y - r.y;
    m_angle = ( atan2(deltaY,deltaX) * 180 ) / 3.14;

    m_startPos = Point(r.x, r.y);
  }
  
Projectile::Projectile(
	Rect r,
	Rect c,
	GameObject::ObjectType otype,
	std::string texturePath,
	int uniqueID,
	GameObject::ObjectType shooterType,
	float angle,
	int distance,
	int speed,
	int damage,
	int immune,
	int health
	):
    MovingGameObject(r, c, otype, texturePath, uniqueID, immune, health, damage), m_shooterType(shooterType), m_distance(distance), m_angle(angle)
  {
    m_startPos = Point(r.x, r.y);
  }

void Projectile::Init()
{
  
}

void Projectile::HandleCollision(GameObject* otherObject)
{
  this->setDead();
}

void Projectile::Update()
{
  Rect pos = this->getRect();
  
  float velocity = 12.0;
  
  
  // Calculate distance between now and startpos
  double distance = sqrt( (pos.x - m_startPos.x)*(pos.x - m_startPos.x) + (pos.y - m_startPos.y)*(pos.y - m_startPos.y) );
  
  if( distance > m_distance )
    this->setDead();
    
  if(isDead())
    return;
  
  Point centerSize(pos.w/2, pos.h/2);
  
  float newPosx = pos.x + velocity * cos(m_angle * 3.14/180);
  float newPosy = pos.y + velocity * sin(m_angle * 3.14/180);
  
  updatePos(Point(newPosx, newPosy));
}

void Projectile::Draw(Renderer* renderer)
{
  Rect pos = this->getRect();
  Point centerSize(pos.w/2, pos.h/2);
  
  if(!isDead()){
    renderer->drawTexture( Rect(pos.x,pos.y,40,40), "imgs/bullet.png", true, Rect(0,0,50,50), false, false, centerSize, m_angle );
  }
  else{
    //GetAnimation("DEATH")->DrawCurrentFrame(renderer, getRect());
    return;
  }
    
    
  MovingGameObject::Draw(renderer);
}

void Projectile::Clean()
{
  
}