#include "Level.h"
#include "Player.h"

Level::Level()
{}
Level::~Level()
{}

void Level::Init()
{
  m_vGameObjects.push_back(new Player(Rect(0,0,100,100), Renderer::PLAYER));
  m_vGameObjects.push_back(new Player(Rect(100,200,100,100), Renderer::PLAYER));
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