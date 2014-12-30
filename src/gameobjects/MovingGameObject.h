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
    virtual void HandleCollision(GameObject* otherObject);
    
    void PhysicHandler();
    void turnOn_falling();
    void turnOff_falling();
  
    void CleanupFrame();
    void Update();
      
    void Draw(Renderer* renderer);
    
    void Clean();
  
    void apply_velocity_x(float x);
    void apply_velocity_y(float y);
    
  protected:
    MovingGameObject( Rect r, Rect c, GameObject::ObjectType otype, std::string texturePath, int uniqueID)
      : GameObject(r, c, otype, texturePath, uniqueID), vx(0), vy(0), ax(0.5), ay(0.5)
    {}
    
    //For collision detection
    bool contactTop{false};
    bool contactBottom{false};
    bool contactLeft{false};
    bool contactRight{false};
    float m_current_fallspeed;
    
    float vx;
    float vy;
    float ax; // acceleration X
    float ay; // acceleration Y
    const float vy_max{15};
    const float vx_max{6};
    
  private:
  
  Point m_previous_position; //
  Point m_velocity;

  bool m_falling;
  
  
    
};

#endif