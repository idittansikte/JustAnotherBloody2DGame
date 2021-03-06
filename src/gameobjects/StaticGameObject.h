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
  
    void Init(Point startpos, int uniquetag);
    
    void HandleCollision(GameObject* otherObject);
    
    void Update();
    
    virtual void Draw(Renderer* renderer);
    
    virtual void Reset();
    
    virtual ObjectType getType() = 0;
  
  protected:
    StaticGameObject( Rect<int> r, Rect<int> c, std::string texturePath , int uniqueID, bool immune, int health, int damage)
      : GameObject(r, c, texturePath, uniqueID, immune, health, damage)
    {}
  
    virtual GameObject* Clone() = 0;
  private:

    
};

#endif