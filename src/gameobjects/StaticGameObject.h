#ifndef STATICGAMEOBJECT_H
#define STATICGAMEOBJECT_H

#include <string>

#include "GameObject.h"
#include "../Rect.h"
#include "../Constants.h"
#include "../Renderer.h"


class StaticGameObject : public GameObject
{
  public:
    StaticGameObject() = delete;
  
    void Init();
    
    void HandleCollision(GameObject* otherObject);
    
    void Update();
    
    void Draw(Renderer* renderer);
    
    void Clean();
  
  protected:
    StaticGameObject( Rect r, GameObject::ObjectType otype, std::string texturePath , int uniqueID)
      : GameObject(r, otype, texturePath, uniqueID)
    {}
  
  private:

    
};

#endif