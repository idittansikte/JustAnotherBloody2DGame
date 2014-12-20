#include "Enemy.h"


void Enemy::Init()
{
  
}

void Enemy::HandleCollision(GameObject* otherObject)
{
  
}

void Enemy::Update()
{
  if (getRect().x < SCREEN_WIDTH)
    add_pos_x(4);
  else
    add_pos_x(-SCREEN_WIDTH);
}

void Enemy::Draw(Renderer* renderer)
{
  GameObject::Draw(renderer);
}

void Enemy::Clean()
{
  
}