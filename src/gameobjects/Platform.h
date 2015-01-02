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
  
  Platform( Rect r, Rect c, GameObject::ObjectType otype, std::string texturePath, int uniqueID, bool immune, int health, int damage, int damageTicks,
	   int friktion, int m_jumpAcceleration );
  
  void Init();
  
  void HandleCollision(GameObject* otherObject);
  
  void Update();
  
  void Draw(Renderer* renderer);
  
  void Clean();
  
  GameObject* Clone();
  
  int getFriktion(){ return m_friktion; }
  int getJumpAcceleration(){ return m_jumpAcceleration; }
  
  private:
    
    State currentState{NORMAL};
    
    const int m_damageTicks;
    const int m_friktion;
    int m_jumpAcceleration;

    bool m_deadAnimationActive{false};
    Point currentAniamtionClip;
    int m_ani_delay;
};

#endif