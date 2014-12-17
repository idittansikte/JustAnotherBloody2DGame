// http://buildnewgames.com/broad-phase-collision-detection/

#include "GameObject.h"
#include "Renderer.h"
#include "Player.h"
#include "Collision.h"
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
  
  void addGameObject(int x, int y, int w, int h, GameObject::ObjectType OType, std::string texturePath);
  
  void Update();
  
  void Draw(Renderer* Renderer);
  
  void Clean();
  
  private:
    int m_iWorldWidth;
    int m_iWorldHeight; 
    std::vector<GameObject*> m_vMovingGameObjects;
    std::vector<GameObject*> m_vStaticGameObjects;
    Collision m_StaticColliesGrid;
    Collision m_MovingColliesGrid;
    Player* m_Player;
    int m_iUniqueCounter{};
    
};