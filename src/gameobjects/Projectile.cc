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
	int damage
	):
    MovingGameObject(r, c, otype, texturePath, uniqueID), m_shooterType(shooterType), m_distance(distance)
  {
    int deltaX, deltaY;
    deltaX = targetPos.x - r.x;
    deltaY = targetPos.y - r.y;
    angle = ( atan2(deltaY,deltaX) * 180 ) / 3.14;
    
    //float endPosx = r.x + distance * cos(angle * 3.14/180);
    //float endPosy = r.y + distance * sin(angle * 3.14/180);
    m_startPos = Point(r.x, r.y);
  }

void Projectile::Init()
{
  
}

void Projectile::HandleCollision(GameObject* otherObject)
{
  
}

void Projectile::Update()
{
  Rect pos = this->getRect();
  
  float velocity = 10.0;
  
  
  // Calculate distance between now and startpos
  double distance = sqrt( (pos.x - m_startPos.x)*(pos.x - m_startPos.x) + (pos.y - m_startPos.y)*(pos.y - m_startPos.y) );
  
  if( distance > m_distance )
    this->setDead();
    
  if(isDead())
    return;
  
  Point centerSize(pos.w/2, pos.h/2);
  
  float newPosx = pos.x + velocity * cos(angle * 3.14/180);
  float newPosy = pos.y + velocity * sin(angle * 3.14/180);
  
  updatePos(Point(newPosx, newPosy));
}

void Projectile::Draw(Renderer* renderer)
{
  
  if(isDead())
    return;
  
  Rect pos = this->getRect();
  Point centerSize(pos.w/2, pos.h/2);
  
  //if (angle < 90 && angle > -90)
    renderer->drawTexture( Rect(pos.x,pos.y,40,40), "imgs/bullet.png", true, Rect(0,0,50,50), false, false, centerSize, angle );
  //else
    //renderer->drawTexture( Rect(posx,posy,40,40), "imgs/bullet.png", true, Rect(0,0,50,50), true, false, centerSize, angle );
}

void Projectile::Clean()
{
  
}