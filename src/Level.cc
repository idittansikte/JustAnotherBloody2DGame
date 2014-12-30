#include <iostream>

#include "Level.h"
#include "gameobjects/Player.h"
#include "gameobjects/Platform.h"
#include "gameobjects/Projectile.h"
#include "Constants.h"
#include "Point.h"
#include "Input.h"

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
  
  addGameObject(200,0,50,50, GameObject::PLAYER, PLAYER_FILEPATH);
  
  addGameObject(200,600,100,100, GameObject::PLATFORM, BLOCK3DBack_FILEPATH);
  addGameObject(300,550,100,100, GameObject::PLATFORM, BLOCK3DBack_FILEPATH);
  addGameObject(100,550,100,100, GameObject::PLATFORM, BLOCK3DBack_FILEPATH);
  addGameObject(300,300,100,100, GameObject::PLATFORM, BLOCK3DBack_FILEPATH);
  
  addGameObject(200,600,100,100, GameObject::INVI_PLATFORM, BLOCK3DFront_FILEPATH);
  addGameObject(300,550,100,100, GameObject::INVI_PLATFORM, BLOCK3DFront_FILEPATH);
  addGameObject(100,550,100,100, GameObject::INVI_PLATFORM, BLOCK3DFront_FILEPATH);
  addGameObject(300,300,100,100, GameObject::INVI_PLATFORM, BLOCK3DFront_FILEPATH);
  
  
  addGameObject(381,550,100,100, GameObject::PLATFORM, BLOCK3DBack_FILEPATH);
  addGameObject(381,550,100,100, GameObject::INVI_PLATFORM, BLOCK3DFront_FILEPATH);
  
  addGameObject(462,550,100,100, GameObject::PLATFORM, BLOCK3DBack_FILEPATH);
  addGameObject(462,550,100,100, GameObject::INVI_PLATFORM, BLOCK3DFront_FILEPATH);
  
  addGameObject(543,550,100,100, GameObject::PLATFORM, BLOCK3DBack_FILEPATH);
  addGameObject(543,550,100,100, GameObject::INVI_PLATFORM, BLOCK3DFront_FILEPATH);
  
  addGameObject(624,550,100,100, GameObject::PLATFORM, BLOCK3DBack_FILEPATH);
  addGameObject(624,550,100,100, GameObject::INVI_PLATFORM, BLOCK3DFront_FILEPATH);
  
  addGameObject(724,550,100,100, GameObject::PLATFORM, BLOCK3DBack_FILEPATH);
  addGameObject(724,550,100,100, GameObject::INVI_PLATFORM, BLOCK3DFront_FILEPATH);
  
  addGameObject(824,550,100,100, GameObject::PLATFORM, BLOCK3DBack_FILEPATH);
  addGameObject(824,550,100,100, GameObject::INVI_PLATFORM, BLOCK3DFront_FILEPATH);
  
  addGameObject(924,550,100,100, GameObject::PLATFORM, BLOCK3DBack_FILEPATH);
  addGameObject(924,550,100,100, GameObject::INVI_PLATFORM, BLOCK3DFront_FILEPATH);
  
  addGameObject(1024,550,100,100, GameObject::PLATFORM, BLOCK3DBack_FILEPATH);
  addGameObject(1024,550,100,100, GameObject::INVI_PLATFORM, BLOCK3DFront_FILEPATH);
  
  addGameObject(1124,550,100,100, GameObject::PLATFORM, BLOCK3DBack_FILEPATH);
  addGameObject(1124,550,100,100, GameObject::INVI_PLATFORM, BLOCK3DFront_FILEPATH);
  //addGameObject(350,400,100,100, GameObject::PLATFORM, BLOCK3DBack_FILEPATH);
  
    //Update Only needed once cuz static object wont move...
  m_StaticColliesGrid->update_grid(m_vStaticGameObjects, m_Player->getCenterPos(), false );
}

void Level::addGameObject(int x, int y, int w, int h, GameObject::ObjectType OType, std::string texturePath)
{
  if (OType == GameObject::PLAYER){
    m_Player = new Player(Rect(x,y,w,h), Rect(0,12,40,40),  OType, texturePath, m_iUniqueCounter++);
    m_vMovingGameObjects.push_back(m_Player);
  }
  else if ( OType == GameObject::PLATFORM ){
    m_vStaticGameObjects.push_back(new Platform(Rect(x,y,w,h), Rect(7,20,79,79), OType, texturePath, m_iUniqueCounter++));
  }
  else if ( OType == GameObject::INVI_PLATFORM ){
    m_vMiscGameObjects.push_back(new Platform(Rect(x,y,w,h), Rect(x,y,w,h), OType, texturePath, m_iUniqueCounter++));
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
  
  ProjectileManager::getInstance()->Update();
  // Update the grid of moving objects
  m_MovingColliesGrid->update_grid(m_vMovingGameObjects, Point(SCREEN_WIDTH/2, SCREEN_HEIGHT/2), false );
    
  // Update all static objects
  for (auto it : m_vStaticGameObjects)
    {
      it->Update();
    }
  
  // Update all moving objects
  for (auto it : m_vMovingGameObjects)
    {
      it->Update();
    }
    
  // Check collision between static and moving objects
  vector<pair<GameObject*, GameObject*>> collies = m_MovingColliesGrid->getColliedPairs(m_StaticColliesGrid);
 
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
  
  ProjectileManager::getInstance()->DrawAll(renderer);
  //Update camera to the current center of SCREEN before any other draws on map...
  renderer->updateCamera(m_Player->getRect(), m_iWorldWidth, m_iWorldHeight);

    // Draw all static objects
    for (auto itt : m_vStaticGameObjects)
    {
      itt->Draw(renderer);
    }
    
    // Draw all moving objects
    for (auto it : m_vMovingGameObjects)
    {
      it->Draw(renderer);
    }
    
    // Draw all Misc objects
    for (auto it : m_vMiscGameObjects)
    {
      it->Draw(renderer);
    }
}

void Level::Clean()
{
  
}