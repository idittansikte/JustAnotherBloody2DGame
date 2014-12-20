#include <iostream>

#include "Level.h"
#include "gameobjects/Player.h"
#include "gameobjects/Platform.h"
#include "Constants.h"
#include "Point.h"

Level::Level()
{
  m_StaticColliesGrid = new Collision( SCREEN_WIDTH*2, SCREEN_HEIGHT*2 );
  m_MovingColliesGrid = new Collision( SCREEN_WIDTH*2, SCREEN_HEIGHT*2 );
}

Level::~Level()
{}

void Level::Init()
{
  
  addGameObject(0,0,100,100, GameObject::PLAYER, PLAYER_FILEPATH);
  addGameObject(200,0,100,100, GameObject::PLATFORM, BLOCK_FILEPATH);
  
    //Update Only needed once cuz static object wont move...
  m_StaticColliesGrid->update_grid(m_vStaticGameObjects, Point(SCREEN_WIDTH/2, SCREEN_HEIGHT/2), false );
}

void Level::addGameObject(int x, int y, int w, int h, GameObject::ObjectType OType, std::string texturePath)
{
  if (OType == GameObject::PLAYER){
    m_Player = new Player(Rect(x,y,w,h), OType, texturePath, m_iUniqueCounter++);
    m_vMovingGameObjects.push_back(m_Player);
  }
  else if ( OType == GameObject::PLATFORM ){
    m_vStaticGameObjects.push_back(new Platform(Rect(x,y,w,h), OType, texturePath, m_iUniqueCounter++));
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
  m_MovingColliesGrid->update_grid(m_vMovingGameObjects, Point(SCREEN_WIDTH/2, SCREEN_HEIGHT/2), false );

  vector<pair<GameObject*, GameObject*>> collies = m_MovingColliesGrid->getColliedPairs(m_StaticColliesGrid);
  
  if ( collies.empty() )
    std::cout << "No collies \n";
  
    for (auto it : collies)
      std::cout << "Collied: " << it.first->getRect().x << " " << it.second->getRect().x << std::endl;
    
    
  for (auto it : m_vStaticGameObjects)
    {
      it->Update();
    }
  
  for (auto it : m_vMovingGameObjects)
    {
      it->Update();
    }
}

void Level::Draw(Renderer* renderer)
{
  
    for (auto it : m_vMovingGameObjects)
    {
      it->Draw(renderer);
    }
    
    for (auto itt : m_vStaticGameObjects)
    {
      itt->Draw(renderer);
    }
}

void Level::Clean()
{
  
}