#ifndef ENEMY_H
#define ENEMY_H

#include <string>

#include "MovingGameObject.h"
#include "../Point.h"

class Projectile;

class Enemy : public MovingGameObject
{
  public:
    
  Enemy(
	Rect r,
	Rect c,
	std::string texturePath,
	int uniqueID,
	bool immune,
	int health,
	int damage
	);
  
  void Init(Point startpos);
  
  void HandleCollision(GameObject* otherObject);
  
  void Update();
  
  void Draw(Renderer* renderer);
  
  void Clean();
  
  void Reset();
  
  void setTarget(GameObject* target, int aggrodistance);
	    
  void setProjectile(Projectile* projectile, int intervall);
  
  GameObject* Clone() { return new Enemy(*this); }
  
  ObjectType getType() { return GameObject::ENEMY; }
  
  bool TargetInRange();
  
  void MakeMovement();
  
  void MakeAttack();
  void Idle();
  void RangeAttackFocus();
  void CombatAttackFocus();
  
  private:
    
    Point m_start_position;
    
    GameObject* m_target;
    int m_aggroDistance;
    float m_angle;
    
    Projectile* m_projectile;
    int m_intervall;
    
    Timer m_timer;
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