#include "Platform.h"
#include <iostream>
#include <cmath>


Platform::Platform( Rect r, Rect c, GameObject::ObjectType otype, std::string texturePath, int uniqueID,
		   bool immune, int health, int damage, int damageTicks, int friktion, int jumpAcceleration)
  : StaticGameObject(r, c, otype, texturePath, uniqueID, immune, health, damage), m_damageTicks(damageTicks), m_friktion(friktion),
  m_jumpAcceleration(jumpAcceleration)

{
    m_bar->setBarBox(Rect( 10, 40, 60, 4));
}


void Platform::Init()
{
  
}

void Platform::HandleCollision(GameObject* otherObject)
{
  StaticGameObject::HandleCollision(otherObject);

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

void Platform::Clean()
{
  
}

GameObject* Platform::Clone(){
  GameObject* newPlatform = new Platform(*this);
  newPlatform->CloneAnimations();
  newPlatform->m_bar = this->m_bar->Clone();
  return newPlatform;
}