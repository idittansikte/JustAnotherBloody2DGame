#ifndef COLLISION_H
#define COLLISION_H

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "gameobjects/GameObject.h"
#include "Point.h"

using namespace std;

class Collision
{
public:
  Collision(int ww, int wh);
  ~Collision(){}
  
  void CleanGrid();
  
  void AddToGrid(multimap<int, GameObject*> ObjectList, Point center, Rect screenSize, bool update_only_visable = true);
  
  vector<pair<GameObject*, GameObject*>> getColliedPairs(Collision* otherList = nullptr);
  
  bool aabbIntersection(GameObject* objA, GameObject* objB);
  void aabbWorldIntersection(GameObject* obj);
  
  int get_grid_col(int x_value);
  
  vector<vector<vector<GameObject*>>> grid;

private:
  
  bool m_isGrid;
  
  vector<pair<GameObject*, GameObject*>> cColliedPairs; // Vector wich we will return
  map<std::string, bool> m_mChecked; //To know wich objects we have checked..
  
  int m_CollisionGridSize{};
  int WORLD_WIDTH;
  int WORLD_HEIGHT;
  
  int allocatedCells{0};
  
  
  
};
#endif