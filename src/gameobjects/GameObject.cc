#include "GameObject.h"

#include <iostream>
#include <utility>

GameObject::GameObject( Rect r, Rect c, ObjectType oType, std::string texturePath, int uniqueID, bool immune, int health, int damage):
      m_rRect(r),
      m_rcollisionRect(c),
      m_eObjectType(oType),
      m_sTexturePath(texturePath),
      m_iUniqueID(uniqueID),
      m_dead(false),
      m_immune(immune),
      m_max_health(health),
      m_damage(damage)
    {
      m_health = m_max_health;
      m_bar = new Bar();
    }

void GameObject::Init()
{
  
}

void GameObject::HandleCollision(GameObject* otherObject){
          if ( otherObject->getObjectType() == GameObject::PROJECTILE ){
	    m_health -= otherObject->m_damage;
	    m_bar->showBar(3);
	  }
}
	  
void GameObject::Update()
{
  if (m_health <= 0)
    setDead();
}

void GameObject::Draw(Renderer* renderer){
  m_bar->drawHealthBar(renderer, this);
}

void GameObject::Clean(){
  
}

bool GameObject::is_in_screen_range(Point screenCenter, Rect screenSize){
      if ( this->getRect().x < screenCenter.x - screenSize.w || this->getRect().x > screenCenter.x + screenSize.w
        || this->getRect().y < screenCenter.y - screenSize.h || this->getRect().y < screenCenter.y + screenSize.h ){
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

Rect GameObject::getCollisionRect(){
  return Rect(m_rRect.x + m_rcollisionRect.x, m_rRect.y + m_rcollisionRect.y,
	      m_rcollisionRect.w, m_rcollisionRect.h);
}

void GameObject::AddAnimation(std::string animationName, Animation* newAnimation){
  
  m_animations.insert( make_pair( animationName, newAnimation ) );
  
}


Animation* GameObject::GetAnimation(std::string animationName){
  
  return m_animations.find( animationName )->second;
  
}

void GameObject::CloneAnimations(){

    for (std::map<std::string, Animation*>::iterator it = m_animations.begin(); it != m_animations.end(); ++it)
    {
        it->second = it->second->Clone();
    }
    
}