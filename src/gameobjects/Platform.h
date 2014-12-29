#ifndef PLATFORM_H
#define PLATFORM_H

#include <string>

#include "../Renderer.h"
#include "StaticGameObject.h"
#include "../Rect.h"
#include "../Constants.h"

class Platform : public StaticGameObject
{
  public:
    
  Platform( Rect r, Rect c, GameObject::ObjectType otype, std::string texturePath, int uniqueID )
    : StaticGameObject(r, c, otype, texturePath, uniqueID)
  {}
  
  void Init();
  
  void HandleCollision(GameObject* otherObject);
  
  void Update();
  
  void Draw(Renderer* renderer);
  
  void Clean();
  
  private:
    
    int speed{};

};

#endif