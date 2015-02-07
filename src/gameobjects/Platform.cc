#include "Platform.h"
#include <iostream>
#include <cmath>


Platform::Platform( Rect<int> r, Rect<int> c, std::string texturePath, int uniqueID,
		   bool immune, int health, int damage, int damageTicks, int friktion, int jumpAcceleration)
  : StaticGameObject(r, c, texturePath, uniqueID, immune, health, damage), m_damageTicks(damageTicks), m_friktion(friktion),
  m_jumpAcceleration(jumpAcceleration)

{
    m_bar->setBarBox(Rect<int>( 10, 40, 60, 4));
    if( this->getDamage() > 0 )
      m_damagetimer.start();
}


void Platform::Init(Point startpos, int uniquetag)
{
  StaticGameObject::Init(startpos, uniquetag);
}

void Platform::Reset(){
  StaticGameObject::Reset();
}

void Platform::HandleCollision(GameObject* otherObject)
{
  StaticGameObject::HandleCollision(otherObject);
  
  if ( otherObject->getType() == GameObject::PLAYER ){
    if( this->getDamage() > 0 && m_damagetimer.getMillisecondsFromStart() > m_damageTicks ){
      otherObject->DrainHealth( this->getDamage() );
      m_damagetimer.reset();
    }
  }

}

void Platform::Update()
{
  
  StaticGameObject::Update();
  
}

void Platform::Draw(Renderer* renderer)
{
  
  if(!isDead()){
    renderer->drawTexture( getRect(), getTexturePath(), true);
  }
  else{
    GetAnimation("DEATH")->DrawCurrentFrame(renderer, getRect());
    return;
  }
    
    
  StaticGameObject::Draw(renderer);
  
}

GameObject* Platform::Clone(){
  GameObject* newPlatform = new Platform(*this);
  newPlatform->CloneAnimations();
  newPlatform->m_bar = this->m_bar->Clone();
  return newPlatform;
}