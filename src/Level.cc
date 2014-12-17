#include "Level.h"
#include "Player.h"
#include "Platform.h"
#include "Constants.h"

Level::Level()
{}
Level::~Level()
{}

void Level::Init()
{
  addGameObject(0,0,100,100, GameObject::PLAYER, PLAYER_FILEPATH);
  addGameObject(100,200,100,100, GameObject::PLAYER, PLAYER_FILEPATH);
}

void Level::addGameObject(int x, int y, int w, int h, GameObject::ObjectType OType, std::string texturePath)
{
  if (OType == GameObject::PLAYER){
    m_vMovingGameObjects.push_back(new Player(Rect(x,y,w,h), OType, texturePath, m_iUniqueCounter++));
  }
  else if ( OType == GameObject::PLATFORM ){
    m_vStaticGameObjects.push_back(new Platform(Rect(x,y,w,h), OType, texturePath, m_iUniqueCounter++));
  }
}

void Level::LoadLevel()
{
  
  m_StaticColliesGrid.init(200, 2000, 2000);
  m_MovingColliesGrid.init(200, 2000, 2000);
}

void Level::SaveLevel()
{
  
}

void Level::Update()
{
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
    
    for (auto it : m_vStaticGameObjects)
    {
      it->Draw(renderer);
    }
}

void Level::Clean()
{
  
}