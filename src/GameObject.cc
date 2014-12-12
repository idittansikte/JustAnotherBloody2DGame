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
  renderer->drawTexture( m_rRect, m_iType, true);
}

void GameObject::Clean()
{
  
}