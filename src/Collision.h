#ifndef COLLISION_H
#define COLLISION_H

#include <map>
#include <string>

class Collision
{
public:
  Collision(){}
  ~Collision(){}
  
  
  void pushPair(GameObject* objA, GameObject* objB);
  bool checked(std::string hash);
  void testCollison(GameObject* objA, GameObject* objB);
  
  
private:
  map<std::string> m_mChecked;
  vector<std::pair> ColliedPairs;
  const int m_CollisionGridSize{50};
}
#endif