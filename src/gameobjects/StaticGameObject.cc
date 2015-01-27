#include "StaticGameObject.h"

void StaticGameObject::Init(Point startpos, int uniquetag)
{
    GameObject::Init(startpos, uniquetag);
}

void StaticGameObject::Reset(){
  GameObject::Reset();
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