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
    apply_velocity_x(4);
  else
    apply_velocity_x(-SCREEN_WIDTH);
}

void Enemy::Draw(Renderer* renderer)
{
  GameObject::Draw(renderer);
}

void Enemy::Clean()
{
  
}