// http://buildnewgames.com/broad-phase-collision-detection/

#include <vector>
#include <map>
#include <string>

#include "gameobjects/GameObjectManager.h"
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
  
  std::multimap<int,GameObject*>* GetEditorList();
  void AddObject(int layer, GameObject* object);
  
  void Load(std::string levelname);
  void SaveLevel();
  
  void Update();
  
  void Draw(Renderer* Renderer);
  
  void Clean();
  void Reset();
  
  Player* getPlayer(){ return m_Player; }
  
  void SetCamera(Rect campos);
  void UpdateCamera(Renderer* renderer);
  
  private:
    int m_iWorldWidth;
    int m_iWorldHeight;
    
    Rect m_screenSize;
    
    LevelData m_LevelData;
    
    
    std::multimap<int, GameObject*> m_vEditorList;
    
    std::multimap<int, GameObject*> m_vMovingGameObjects;
    std::multimap<int, GameObject*> m_vStaticGameObjects;
    std::multimap<int, GameObject*> m_vMiscGameObjects;
    
    vector<std::multimap<int, GameObject*>* > m_objectLists; 
    
    Collision* m_StaticColliesGrid;
    Collision* m_MovingColliesGrid;
    
    Player* m_Player;
    
    Rect m_camera_position;
    
    int uniqueTag{};
     
};