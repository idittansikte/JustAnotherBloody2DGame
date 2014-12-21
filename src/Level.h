// http://buildnewgames.com/broad-phase-collision-detection/

#include <vector>
#include <map>
#include <string>

#include "gameobjects/GameObject.h"
#include "Renderer.h"
#include "gameobjects/Player.h"
#include "Collision.h"
#include "Constants.h"
#include "LevelData.h"


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
  
  Player* getPlayer(){ return m_Player; }
  
  private:
    int m_iWorldWidth;
    int m_iWorldHeight; 
    LevelData m_LevelData;
    std::vector<GameObject*> m_vMovingGameObjects;
    std::vector<GameObject*> m_vStaticGameObjects;
    Collision* m_StaticColliesGrid;
    Collision* m_MovingColliesGrid;
    Player* m_Player;
    int m_iUniqueCounter{};
    
};