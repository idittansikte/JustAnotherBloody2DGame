#include "GameObject.h"
#include "Renderer.h"
#include <vector>


class Level
{
  public:
  Level();
  ~Level();
  
  void Init();
  
  void LoadLevel();
  void SaveLevel();
  
  void Update();
  
  void Draw(Renderer* Renderer);
  
  void Clean();
  
  private:
    std::vector<GameObject*> m_vGameObjects;
};