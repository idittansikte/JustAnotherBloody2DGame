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
  Level(std::string map_path);
  ~Level();
  
  void Init();
  
  std::multimap<int,GameObject*>* GetEditorList();

  void Load(std::string levelname);
  
  void Update();
  
  void Draw(Renderer* Renderer);
  
  void Clean();
  void Reset();
  
  Player* getPlayer(){ return m_Player; }
  
  void SetCamera(Rect<int> campos);
  Rect<int> GetCameraPos(){ return m_camera_position; }
  void UpdateCamera(Renderer* renderer);
  
  private:
    int m_iWorldWidth;
    int m_iWorldHeight;
    
    Rect<int> m_screenSize;
    
    LevelData m_LevelData;
    
    
    std::multimap<int, GameObject*> m_vEditorList;
    
    std::multimap<int, GameObject*> m_vMovingGameObjects;
    std::multimap<int, GameObject*> m_vStaticGameObjects;
    std::multimap<int, GameObject*> m_vMiscGameObjects;
    
    vector<std::multimap<int, GameObject*>* > m_objectLists; 
    
    Collision* m_StaticColliesGrid;
    Collision* m_MovingColliesGrid;
    
    Player* m_Player;
    
    Rect<int> m_camera_position;
    
    int uniqueTag{};
     
};