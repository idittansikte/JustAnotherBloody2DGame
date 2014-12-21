#ifndef MOVINGGAMEOBJECT_H
#define MOVINGGAMEOBJECT_H

#include <string>

#include "GameObject.h"
#include "../Rect.h"
#include "../Constants.h"
#include "../Renderer.h"

class MovingGameObject : public GameObject
{
  public:
    
    void Init();
    
    
    bool collidedFromLeft(GameObject* otherObject);
    bool collidedFromRight(GameObject* otherObject);
    bool collidedFromTop(GameObject* otherObject);
    bool collidedFromBottom(GameObject* otherObject);
    void HandleCollision(GameObject* otherObject);
    
    void apply_physics();
    void turnOn_falling();
    void turnOff_falling();
  
    void CleanupFrame();
    void Update();
      
    void Draw(Renderer* renderer);
    
    void Clean();
  
    void apply_velocity_x(float x);
    void apply_velocity_y(float y);
    
  protected:
    MovingGameObject( Rect r, GameObject::ObjectType otype, std::string texturePath, int uniqueID)
      : GameObject(r, otype, texturePath, uniqueID), m_max_fallspeed(40)
    {}
    
    //For collision detection
    bool contactTop;
    bool contactBottom;
    bool contactLeft;
    bool contactRight;
    
  private:

  Point m_previous_position; //
  Point m_velocity;

  bool m_falling;
  const float m_max_fallspeed;
  float m_current_fallspeed;
    
};

#endif