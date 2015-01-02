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

class Enemy;
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
}

Level::~Level()
{}

void Level::Init()
{
  
  GameObjectManager gm(LUA_FILEPATH);
  gm.loadGameObjectsFromFile();
  
  GameObject* go = gm.GetGameObject("NORMAL");
  go->updatePos(Point(100, 300));
  go->changeUniqueTag(uniqueTag++);
  m_vStaticGameObjects.insert( std::make_pair( 1 , go ));
  
  go = gm.GetGameObject("NORMAL");
  go->updatePos(Point(200, 300));
  go->changeUniqueTag(uniqueTag++);
  m_vStaticGameObjects.insert( std::make_pair( 1 , go ));
  
   go = gm.GetGameObject("NORMAL");
  go->updatePos(Point(300, 300));
  go->changeUniqueTag(uniqueTag++);
  m_vStaticGameObjects.insert( std::make_pair( 1 , go ));
  
  go = gm.GetGameObject("NORMAL");
  go->updatePos(Point(400, 300));
  go->changeUniqueTag(uniqueTag++);
  m_vStaticGameObjects.insert( std::make_pair( 1 , go ));
  
     go = gm.GetGameObject("NORMAL");
  go->updatePos(Point(500, 300));
  go->changeUniqueTag(uniqueTag++);
  m_vStaticGameObjects.insert( std::make_pair( 1 , go ));
  
  go = gm.GetGameObject("FIRE");
  go->updatePos(Point(600, 400));
  go->changeUniqueTag(uniqueTag++);
  m_vStaticGameObjects.insert( std::make_pair( 1 , go ));
  
    go = gm.GetGameObject("FIRE");
  go->updatePos(Point(700, 500));
  go->changeUniqueTag(uniqueTag++);
  m_vStaticGameObjects.insert( std::make_pair( 1 , go ));
  
     go = gm.GetGameObject("FIRE");
  go->updatePos(Point(800, 600));
  go->changeUniqueTag(uniqueTag++);
  m_vStaticGameObjects.insert( std::make_pair( 1 , go ));
  
  go = gm.GetGameObject("FIRE");
  go->updatePos(Point(900, 600));
  go->changeUniqueTag(uniqueTag++);
  m_vStaticGameObjects.insert( std::make_pair( 1 , go ));
  
  go = gm.GetEnemy("Crow");
  go->updatePos(Point(500, 200));
  go->changeUniqueTag(uniqueTag++);
  m_vMovingGameObjects.insert( std::make_pair( 1 , go ));
  
  m_Player = new Player(Rect(100,100,50,50), Rect(0,12,40,40),  GameObject::PLAYER, PLAYER_FILEPATH, uniqueTag++, false, 1000, 100);
  m_vMovingGameObjects.insert( std::make_pair( 1, m_Player ) );
  
    //Update Only needed once cuz static object wont move...
  m_StaticColliesGrid->AddToGrid(m_vStaticGameObjects, m_Player->getCenterPos(), m_screenSize, false );
}

void Level::addGameObject(int x, int y, int w, int h, GameObject::ObjectType OType, std::string texturePath)
{
  if (OType == GameObject::PLAYER){

  }
  else if ( OType == GameObject::PLATFORM ){
    //m_vStaticGameObjects.insert( std::make_pair( 0, new Platform( Rect(x,y,w,h), Rect(7,20,79,79), OType, texturePath, uniqueTag++ ) ) );
  }
  else if ( OType == GameObject::INVI_PLATFORM ){
    
    //m_vStaticGameObjects.insert( std::make_pair( 2, new Platform( Rect(x,y,w,h), Rect(7,20,79,79), OType, texturePath, uniqueTag++ ) ) );
  }
  else if ( OType == GameObject::ENEMY ){
    //m_vMovingGameObjects.insert( std::make_pair( 1, new Enemy( Rect(x,y,w,h), Rect(x,y,w,h), OType, texturePath, uniqueTag++ ) ) );
  }
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
  else{
     //std::cout << "No collies \n";
  }
}

void Level::Draw(Renderer* renderer)
{
  m_screenSize = renderer->getWindowSize();
  //Update camera to the current center of SCREEN before any other draws on map...
  renderer->updateCamera(m_Player->getRect(), m_iWorldWidth, m_iWorldHeight);

  
  //std::multimap<int, GameObject*>::iterator itStatic = m_vStaticGameObjects.begin();
  //std::multimap<int, GameObject*>::iterator itMoving = m_vMovingGameObjects.begin();
  //std::multimap<int, GameObject*>::iterator itMisc = m_vMiscGameObjects.begin();
  
  
  const int max_layers = 4;
  int current_layer = 0;
  for(; current_layer <= max_layers; ++current_layer ){
    std::pair< std::multimap<int, GameObject*>::iterator, std::multimap<int, GameObject*>::iterator > it;
    it = m_vStaticGameObjects.equal_range(current_layer);
    for( std::multimap<int, GameObject*>::iterator pp = it.first; pp != it.second; ++pp){
        (*pp).second->Draw(renderer);
    }
    it = m_vMovingGameObjects.equal_range(current_layer);
    for( std::multimap<int, GameObject*>::iterator pp = it.first; pp != it.second; ++pp){
        (*pp).second->Draw(renderer);
    }
    it = m_vMiscGameObjects.equal_range(current_layer);
    for( std::multimap<int, GameObject*>::iterator pp = it.first; pp != it.second; ++pp){
        (*pp).second->Draw(renderer);
    }
  }
  
    //// Draw all static objects
    //for (auto itt : m_vStaticGameObjects)
    //{
    //  if( !itt.second->isDead() )
    //    itt.second->Draw(renderer);
    //}
    //
    //// Draw all moving objects
    //for (auto it : m_vMovingGameObjects)
    //{
    //  it.second->Draw(renderer);
    //}
    //
    //// Draw all Misc objects
    //for (auto it : m_vMiscGameObjects)
    //{
    //  it.second->Draw(renderer);
    //}
    
    ProjectileManager::getInstance()->DrawAll(renderer);
}

void Level::Clean()
{
  
}