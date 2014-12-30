#ifndef ENEMY_H
#define ENEMY_H

#include <string>

#include "../Renderer.h"
#include "MovingGameObject.h"
#include "../Rect.h"
#include "../Constants.h"

class Projectile : public MovingGameObject
{
  public:
    
  Projectile(
	Rect r,
	Rect c,
	GameObject::ObjectType otype,
	std::string texturePath,
	int uniqueID,
	GameObject::ObjectType shooterType,
	Point targetPos,
	int distance,
	int speed,
	int damage
	);
  
  void Init();
  
  void HandleCollision(GameObject* otherObject);
  
  void Update();
  
  void Draw(Renderer* renderer);
  
  void Clean();
  
  private:
    
    GameObject::ObjectType m_shooterType;
    
    Point m_startPos;
    
    double angle;
    
    int m_distance;
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