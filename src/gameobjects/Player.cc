#include "Player.h"
#include "../Input.h"
#include "../ProjectileManager.h"

#include <iostream>
#include <math.h>

Player::Player( Rect r, Rect c, GameObject::ObjectType otype, std::string texturePath, int uniqueID ) :
  MovingGameObject(r, c, otype, texturePath, uniqueID),
  m_jump_start_velocity(12.0),
  m_want_jump(false),
  m_doubleJump_used(false)
  {}

void Player::Init()
{
  
}

void Player::HandleCollision(GameObject* otherObject)
{
  
  MovingGameObject::HandleCollision(otherObject);
}

void Player::Update()
{
  
  
  PhysicHandler();
  
  JumpHandler();
  
  MovingGameObject::Update(); // Applying velocity
  
  CleanupFrame();
}

void Player::Draw(Renderer* renderer)
{
  cameraAdjustment = renderer->getCameraAdjustment();
  GameObject::Draw(renderer);
  renderPistol(renderer);
}

void Player::Clean()
{
  
}

void Player::movement_left(){
  if (vx > -vx_max)
    vx -= ax;
}

void Player::movement_right(){
  if (vx < vx_max)
    vx += ax;
}

void Player::movement_up(){
  m_want_jump = true;
}

void Player::movement_down(){
  // Ducka...
  // apply_velocity_y(m_current_walking_speed);
}

void Player::movement_shoot(){
  
  //double distance = sqrt( (pistolHole.x - getCenterPos().x)*(pistolHole.x - getCenterPos().x) + (pistolHole.y - getCenterPos().y)*(pistolHole.y - getCenterPos().y) );
  
  ProjectileManager::getInstance()->AddProjectile(BULLET_FILEPATH, m_uniqueTag++, GameObject::PLAYER, Rect(pistolHole.x,pistolHole.y,40,40),
                                  Point(Input::getInstance()->get_mouse_x()+ cameraAdjustment.x,
					Input::getInstance()->get_mouse_y()+ cameraAdjustment.y ), 250, 3, 100);
}

void Player::JumpHandler(){
  
  if( contactTop ){
    vy = 0;
  }
    
  if(m_want_jump && contactBottom){ // Start jumping procedure
    
      vy = -m_jump_start_velocity;
      m_doubleJump_used = false;
  }
  else if( m_want_jump && !contactBottom && !m_doubleJump_used && vy >= -m_jump_start_velocity+4 ){ // if already in air
    vy = -m_jump_start_velocity;
    m_doubleJump_used = true;
  }
  
  m_want_jump = false;
  
}

void Player::renderPistol(Renderer* renderer){
  Point center = getCenterPos(); //center of player
  center.x -= 20;
  center.y -= 20;
  Point centerSize(20, 20);
  int radius = 50; // pixels
  
  Point adjustment = renderer->getCameraAdjustment();
  
  int mouseX = Input::getInstance()->get_mouse_x() + adjustment.x;
  int mouseY = Input::getInstance()->get_mouse_y() + adjustment.y;
  
  int deltaX, deltaY;
  
  deltaX = mouseX - center.x;
  deltaY = mouseY - center.y;
  
  double angle = ( atan2(deltaY,deltaX) * 180 ) / 3.14;
  
  // Set pistol on circel around player...
  pistolHole.x = center.x + radius * cos(angle * 3.14/180);
  pistolHole.y = center.y + radius * sin(angle * 3.14/180);
  
  //Flip pistol if it is upsidedown
  if (angle < 90 && angle > -90)
    renderer->drawTexture( Rect(pistolHole.x,pistolHole.y,40,40), "imgs/pistol.png", true, Rect(0,0,50,50), false, false, centerSize, angle );
  else
    renderer->drawTexture( Rect(pistolHole.x,pistolHole.y,40,40), "imgs/pistol.png", true, Rect(0,0,50,50), true, false, centerSize, angle );
}



