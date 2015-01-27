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
	int damage,
	int aggroDistance
	);
  
  void Init(Point startpos, int uniquetag, GameObject* target);
  
  void Reset();
  
  void HandleCollision(GameObject* otherObject);
  
  void Update();
  
  void Draw(Renderer* renderer);
	    
  void setProjectile(Projectile* projectile, int intervall);
  
  GameObject* Clone() { return new Enemy(*this); }
  
  ObjectType getType() { return GameObject::ENEMY; }
  
  bool TargetInRange();
  
  void MakeMovement();
  
  void MakeAttack();
  void Idle();
  void RangeAttackFocus();
  void CombatAttackFocus();
  
  void SetMaxMovementRight(int max);
  void SetMaxMovementLeft(int max);
  int GetMaxMovementRight();
  int GetMaxMovementLeft();
  
  private:
    
    GameObject* m_target;
    int m_aggroDistance;
    float m_angle;
    
    Projectile* m_projectile;
    int m_intervall;
    
    Timer m_timer;
    
    int m_max_movement_right{};
    int m_max_movement_left{};
};

#endif