#ifndef MOVINGGAMEOBJECT_H
#define MOVINGGAMEOBJECT_H

#include <string>

#include "GameObject.h"
#include "Rect.h"
#include "Constants.h"
#include "Renderer.h"

class MovingGameObject : public GameObject
{
  public:
    
    void Init();
    
    void Update();
    
    void Draw(Renderer* renderer);
    
    void Clean();
  
  protected:
    MovingGameObject( Rect r, GameObject::ObjectType otype, std::string texturePath, int uniqueID)
      : GameObject(r, otype, texturePath, uniqueID)
    {}
  
  private:

    
};

#endif