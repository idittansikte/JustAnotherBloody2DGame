#include "GameObject.h"

#include "Renderer.h"
  
void GameObject::Init()
{
  
}

void GameObject::Update()
{
  
}

void GameObject::Draw(Renderer* renderer)
{
  renderer->drawTexture( m_rRect, m_sTexturePath, true);
}

void GameObject::Clean()
{
  
}

void GameObject::add_pos_x(int x)
{
  m_rRect.x += x;
}

void GameObject::add_pos_y(int y)
{
  m_rRect.y += y;
}