#ifndef COLLISION_H
#define COLLISION_H

#include "GameObject.h"
#include <map>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Collision
{
public:
  Collision();
  ~Collision(){}
  
  void init(int collisionGridSize, int ww, int wh);
  
  void update(vector<GameObject*> ObjectList);
  
  vector<pair<GameObject*, GameObject*>> findColliedPairs();
  
  bool aabbIntersection(GameObject* objA, GameObject* objB);
  
  
private:
  int m_CollisionGridSize{};
  int WORLD_WIDTH;
  int WORLD_HEIGHT;
  
  int allocatedCells{0};
  
  map<std::string, bool> m_mChecked;
  
  vector<vector<vector<GameObject*>>> grid;
  
};
#endif