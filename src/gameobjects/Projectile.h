#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <string>

#include "../Renderer.h"
#include "MovingGameObject.h"
#include "../Rect.h"
#include "../Constants.h"

class Projectile : public MovingGameObject
{
  public:
    
  Projectile(
	Rect<int> r,
	Rect<int> c,
	std::string texturePath,
	int uniqueID,
	int distance,
	bool immune,
	int health,
	float velocity
	);
  
  void Init( GameObject* shooter, int uniqueTag, Point startpos, Point targetpos = Point(), float angle = 0.0 );
  
  void HandleCollision(GameObject* otherObject);
  
  void Update();
  
  void Draw(Renderer* renderer);
  
  void Clean();
  
  void Reset();
  
  int getDamage(){ return m_damage; }
  
  Projectile* Clone() { return new Projectile(*this); }
  
  ObjectType getType() { return GameObject::PROJECTILE; }
  
  void setShooter(GameObject* shooter){ m_shooter = shooter; }
  
  private:
    
    GameObject::ObjectType m_shooterType;
    
    GameObject* m_shooter;
    
    Point m_startPos;
    
    float m_angle;
    
    int m_distance;
    
    float m_velocity;
   /* 
    std::string m_name{""};
    
    const int m_hitpoint_max;
    int m_hitpoint_current;
    
    const int m_min_damage;
    const int m_max_damage;
    
    int m_attack_interval;
    
    int m_movement_speed;*/
};

#endif