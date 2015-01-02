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
    
    virtual void Draw(Renderer* renderer);
    
    void Clean();
  
  protected:
    StaticGameObject( Rect r, Rect c, GameObject::ObjectType otype, std::string texturePath , int uniqueID, bool immune, int health, int damage)
      : GameObject(r, c, otype, texturePath, uniqueID, immune, health, damage)
    {}
  
    virtual GameObject* Clone() = 0;
  private:

    
};

#endif