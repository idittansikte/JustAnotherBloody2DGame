#include "Platform.h"
#include "GameObject.h"
#include <iostream>
#include <cmath>

void Platform::Init()
{
  
}

void Platform::HandleCollision(GameObject* otherObject)
{
  if ( otherObject->getObjectType() == GameObject::PROJECTILE ){
    Projectile* p = dynamic_cast<Projectile*>(otherObject);
    
    m_health -= p->getDamage();
  }
}

void Platform::Update()
{
  if (m_health <= 0)
    setDead();
}

void Platform::Draw(Renderer* renderer)
{
  GameObject::Draw(renderer);
  
  Rect r = this->getRect();
  Rect healthbar(r.x+10, r.y+40, r.w-40, 10);
  if ( this->getObjectType() == GameObject::INVI_PLATFORM ){
    m_bar.showHealthBar(renderer, healthbar, m_max_health, m_health);
  }
}

void Platform::Clean()
{
  
}