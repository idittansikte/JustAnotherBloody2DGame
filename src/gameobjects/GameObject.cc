#include "GameObject.h"

#include <iostream>

GameObject::GameObject( Rect r, ObjectType oType, std::string texturePath, int uniqueID)
      : m_rRect(r),
      m_eObjectType(oType),
      m_sTexturePath(texturePath),
      m_iUniqueID(uniqueID),
      m_dead(false)
    {}
  
void GameObject::Init()
{
  
}

void GameObject::Update()
{
  
}

void GameObject::Draw(Renderer* renderer){
  renderer->drawTexture( m_rRect, m_sTexturePath, true);
}

void GameObject::Clean(){
  
}

bool GameObject::is_in_screen_range(Point screenCenter){
      if ( this->getRect().x < screenCenter.x - SCREEN_WIDTH || this->getRect().x > screenCenter.x + SCREEN_WIDTH
        || this->getRect().y < screenCenter.y - SCREEN_HEIGHT || this->getRect().y < screenCenter.y + SCREEN_HEIGHT ){
          return false;
      }
  return true;
}


void GameObject::setDead(){
  m_dead = true;
}

void GameObject::setAlive(){
  m_dead = false;
}

bool GameObject::isDead(){
  return m_dead;
}
