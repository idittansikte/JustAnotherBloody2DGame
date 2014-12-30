#ifndef PLATFORM_H
#define PLATFORM_H

#include <string>

#include "../Renderer.h"
#include "StaticGameObject.h"
#include "../Rect.h"
#include "../Constants.h"
#include "Projectile.h"
#include "gadgets/Bar.h"

class Platform : public StaticGameObject
{
  public:
    
  Platform( Rect r, Rect c, GameObject::ObjectType otype, std::string texturePath, int uniqueID )
    : StaticGameObject(r, c, otype, texturePath, uniqueID)
  {
    m_max_health = 400;
    m_health = m_max_health;
  }
  
  void Init();
  
  void HandleCollision(GameObject* otherObject);
  
  void Update();
  
  void Draw(Renderer* renderer);
  
  void Clean();
  
  private:
    
    int m_max_health;
    
    int m_health;
    
    Bar m_bar;

};

#endif