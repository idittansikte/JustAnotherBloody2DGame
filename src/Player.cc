#include "Player.h"


void Player::Init()
{
  
}

void Player::Update()
{
  if (getRect().x < SCREEN_WIDTH)
    add_pos_x(4);
  else
    add_pos_x(-SCREEN_WIDTH-200);
}

void Player::Draw(Renderer* renderer)
{
  GameObject::Draw(renderer);
}

void Player::Clean()
{
  
}