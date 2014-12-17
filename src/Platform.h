#ifndef PLATFORM_H
#define PLATFORM_H

#include <string>

#include "Renderer.h"
#include "StaticGameObject.h"
#include "Rect.h"
#include "Constants.h"

class Platform : public StaticGameObject
{
  public:
    
  Platform( Rect r, GameObject::ObjectType otype, std::string texturePath, int uniqueID )
    : StaticGameObject(r, otype, texturePath, uniqueID)
  {}
  
  void Init();
  
  void Update();
  
  void Draw(Renderer* renderer);
  
  void Clean();
  
  private:

};

#endif