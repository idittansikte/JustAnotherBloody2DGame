#include <iostream>
#include <utility>

#include "Level.h"
#include "gameobjects/Player.h"
//#include "gameobjects/Platform.h"
#include "gameobjects/Projectile.h"
//#include "gameobjects/GameObjectManager.h"
#include "Constants.h"
#include "Point.h"
#include "Input.h"
#include "ProjectileManager.h"
//#include "gameobjects/Enemy.h"

#include "gameobjects/Enemy.h"
class Platform;
class GameObjectManager;

Level::Level():
  m_iWorldWidth(2000),
  m_iWorldHeight(2000)
{
  m_LevelData.levelWidth=2000;
  m_LevelData.levelHeight=2000;
  m_StaticColliesGrid = new Collision( m_iWorldWidth, m_iWorldHeight );
  m_MovingColliesGrid = new Collision( m_iWorldWidth, m_iWorldHeight );
  
  //std::multimap<int, GameObject*>* list1 = m_vMovingGameObjects;
  //std::multimap<int, GameObject*>* list2 = m_vStaticGameObjects;
  //std::multimap<int, GameObject*>* list3 = m_vMiscGameObjects;
    
  m_objectLists.push_back(&m_vMovingGameObjects);
  m_objectLists.push_back(&m_vStaticGameObjects);
  m_objectLists.push_back(&m_vMiscGameObjects); 
}

Level::~Level()
{}

void Level::Init()
{
  
  GameObjectManager* gm = GameObjectManager::Instance();
  
  GameObject* go = gm->GetNewPlatform("NORMAL");
  go->updatePos(Point(100, 300));
  go->changeUniqueTag(uniqueTag++);
  m_vStaticGameObjects.insert( std::make_pair( 1 , go ));
  
  go = gm->GetNewPlatform("NORMAL");
  go->updatePos(Point(200, 300));
  go->changeUniqueTag(uniqueTag++);
  m_vStaticGameObjects.insert( std::make_pair( 1 , go ));
  
   go = gm->GetNewPlatform("NORMAL");
  go->updatePos(Point(300, 300));
  go->changeUniqueTag(uniqueTag++);
  m_vStaticGameObjects.insert( std::make_pair( 1 , go ));
  
  go = gm->GetNewPlatform("NORMAL");
  go->updatePos(Point(400, 300));
  go->changeUniqueTag(uniqueTag++);
  m_vStaticGameObjects.insert( std::make_pair( 1 , go ));
  
     go = gm->GetNewPlatform("NORMAL");
  go->updatePos(Point(500, 300));
  go->changeUniqueTag(uniqueTag++);
  m_vStaticGameObjects.insert( std::make_pair( 1 , go ));
  
  go = gm->GetNewPlatform("FIRE");
  go->updatePos(Point(600, 400));
  go->changeUniqueTag(uniqueTag++);
  m_vStaticGameObjects.insert( std::make_pair( 1 , go ));
  
    go = gm->GetNewPlatform("FIRE");
  go->updatePos(Point(700, 500));
  go->changeUniqueTag(uniqueTag++);
  m_vStaticGameObjects.insert( std::make_pair( 1 , go ));
  
     go = gm->GetNewPlatform("FIRE");
  go->updatePos(Point(800, 600));
  go->changeUniqueTag(uniqueTag++);
  m_vStaticGameObjects.insert( std::make_pair( 1 , go ));
  
  go = gm->GetNewPlatform("FIRE");
  go->updatePos(Point(900, 600));
  go->changeUniqueTag(uniqueTag++);
  m_vStaticGameObjects.insert( std::make_pair( 1 , go ));
  
  GameObject* ne = gm->GetNewEnemy("Crow");
  ne->updatePos(Point(400, 100));
  ne->Init(Point(400, 100));
  ne->changeUniqueTag(uniqueTag++);
  m_vMovingGameObjects.insert( std::make_pair( 1 , ne ));
  
  m_Player = gm->GetNewPlayer("Hero"); //new Player(Rect(100,100,50,50), Rect(0,12,40,40), PLAYER_FILEPATH, uniqueTag++, false, 1000, 100);
  m_Player->updatePos(Point(100, 100));
  m_Player->changeUniqueTag(uniqueTag++);
  m_vMovingGameObjects.insert( std::make_pair( 2, m_Player ) );
  
    //Update Only needed once cuz static object wont move...
  m_StaticColliesGrid->AddToGrid(m_vStaticGameObjects, m_Player->getCenterPos(), m_screenSize, false );
}

void Level::LoadLevel()
{
  
}

void Level::SaveLevel()
{
  
}

void Level::Update()
{

  m_MovingColliesGrid->CleanGrid(); // Make a clean cuz objects are moving and need to be updated..
  
  ProjectileManager::getInstance()->Update();
  
  // Update all static objects
  for (auto it : m_vStaticGameObjects)
    {
      it.second->Update();
    }
  
  // Update all moving objects
  for (auto it : m_vMovingGameObjects)
    {
      it.second->Update();
    }
    
    // Update the grid of moving objects
  m_MovingColliesGrid->AddToGrid(m_vMovingGameObjects, Point(m_screenSize.w/2, m_screenSize.h/2), m_screenSize, false );
  m_MovingColliesGrid->AddToGrid(ProjectileManager::getInstance()->GetProjectiles(), Point(m_screenSize.w/2, m_screenSize.h/2), m_screenSize, false );
  
  // Check collision between static and moving objects
  vector<pair<GameObject*, GameObject*>> collies = m_MovingColliesGrid->getColliedPairs(m_StaticColliesGrid);
  collies = m_MovingColliesGrid->getColliedPairs(m_MovingColliesGrid);
  
  // Handle collied pairs if there where any...
  if ( !collies.empty() ){
    for (auto it : collies){
      it.first->HandleCollision(it.second);
      it.second->HandleCollision(it.first);
      //std::cout << "Collied: " << it.first->getRect().x << " " << it.second->getRect().x << std::endl;
    }
  }
}

void Level::Draw(Renderer* renderer)
{
  //UpdateScreen Size
  m_screenSize = renderer->getWindowSize();
  
  //Update camera to the current center of SCREEN before any other draws on map...
  renderer->updateCamera(m_Player->getRect(), m_iWorldWidth, m_iWorldHeight);

  const int max_layers = 4;
  int current_layer = 0;
  for(; current_layer <= max_layers; ++current_layer ){
    std::pair< std::multimap<int, GameObject*>::iterator, std::multimap<int, GameObject*>::iterator > it;

    for( auto p : m_objectLists){
        it = p->equal_range(current_layer);
        for( std::multimap<int, GameObject*>::iterator pp = it.first; pp != it.second; ++pp){
          (*pp).second->Draw(renderer);
        }
    }
  }
  
    ProjectileManager::getInstance()->DrawAll(renderer);
}

void Level::Clean()
{
  
}

void Level::Reset(){
  for( auto p : m_objectLists){
    for( auto k : *p ){
      k.second->Reset();
    }
  }
}