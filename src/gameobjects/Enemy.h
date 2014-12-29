#ifndef ENEMY_H
#define ENEMY_H

#include <string>

#include "../Renderer.h"
#include "MovingGameObject.h"
#include "../Rect.h"
#include "../Constants.h"

class Enemy : public MovingGameObject
{
  public:
    
  Enemy(
	Rect r,
	Rect c,
	GameObject::ObjectType otype,
	std::string texturePath,
	int uniqueID
	):
    MovingGameObject(r, c, otype, texturePath, uniqueID)
  {}
  
  void Init();
  
  void HandleCollision(GameObject* otherObject);
  
  void Update();
  
  void Draw(Renderer* renderer);
  
  void Clean();
  
  private:
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