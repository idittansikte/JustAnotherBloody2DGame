#include "Level.h"
#include "Player.h"

Level::Level()
{}
Level::~Level()
{}

void Level::Init()
{
  pushGameObject(0,0,100,100, Renderer::PLAYER);
  pushGameObject(100,200,100,100, Renderer::PLAYER);
}

void pushGameObject(int x, int y, int w, int h, Renderer::ObjectType type)
{
  if (type == PLAYER){
    m_vGameObjects.push_back(new Player(Rect(x,y,w,h), Renderer::type, m_iUniqueCounter++);
  }
  else if ( type == GRASS_PLATFORM_TOPLEFT || type == GRASS_PLATFORM_TOPRIGHT || type == GRASS_PLATFORM_BOTTOMRIGHT
           || type == GRASS_PLATFORM_BOTTOMLEFT ){
    m_vGameObjects.push_back(new Platform(Rect(x,y,w,h), Renderer::type, m_iUniqueCounter++);
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
  
}

void Level::Draw(Renderer* renderer)
{
  
    for (auto it : m_vGameObjects)
    {
      it->Draw(renderer);
    }
}

void Level::Clean()
{
  
}