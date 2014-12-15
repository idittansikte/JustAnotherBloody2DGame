// http://buildnewgames.com/broad-phase-collision-detection/

#include "GameObject.h"
#include "Renderer.h"
#include <vector>
#include <map>
#include <string>

class Level
{
  public:
  Level();
  ~Level();
  
  void Init();
  
  void LoadLevel();
  void SaveLevel();
  
  void pushGameObject(int x, int y, int w, int h, Renderer::ObjectType type)
  
  void Update();
  
  void Draw(Renderer* Renderer);
  
  void Clean();
  
  private:
    std::vector<GameObject*> m_vMovingGameObjects;
    std::vector<GameObject*> m_vStaticGameObjects;
    int m_iUniqueCounter{};
    
};