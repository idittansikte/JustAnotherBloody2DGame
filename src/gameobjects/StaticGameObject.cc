#include "StaticGameObject.h"

void StaticGameObject::Init()
{
    
}

void StaticGameObject::HandleCollision(GameObject* otherObject)
{
    GameObject::HandleCollision(otherObject);
  
}

void StaticGameObject::Update()
{
    GameObject::Update();
}

void StaticGameObject::Draw(Renderer* renderer)
{
    GameObject::Draw(renderer);
}

void StaticGameObject::Clean()
{
  
}

void StaticGameObject::Reset(){
  GameObject::Reset();
}