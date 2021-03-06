#ifndef PLATFORM_H
#define PLATFORM_H

#include <string>

#include "StaticGameObject.h"
#include "../Rect.h"
#include "../Point.h"
#include "../Constants.h"
#include "Projectile.h"

class Renderer;
class Bar;


class Platform : public StaticGameObject
{
  public:
 
  enum State{NORMAL, DIES};
  
  Platform( Rect<int> r, Rect<int> c, std::string texturePath, int uniqueID, bool immune, int health, int damage, int damageTicks,
	   int friktion, int m_jumpAcceleration );
  
  void Init(Point startpos, int uniquetag);
  
  void Reset();
  
  void HandleCollision(GameObject* otherObject);
  
  void Update();
  
  void Draw(Renderer* renderer);
  
  
  GameObject* Clone();
  ObjectType getType() { return GameObject::PLATFORM; }
  
  int getFriktion(){ return m_friktion; }
  int getJumpAcceleration(){ return m_jumpAcceleration; }
  
  private:
    
    Timer m_damagetimer;
    
    State currentState{NORMAL};
    
    const int m_damageTicks;
    const int m_friktion;
    int m_jumpAcceleration;

    bool m_deadAnimationActive{false};
    Point currentAniamtionClip;
    int m_ani_delay;
};

#endif