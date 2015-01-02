#include "Player.h"

#include "../Input.h"

#include "../ProjectileManager.h"
#include "Platform.h"
#include <iostream>
#include <math.h>

Player::Player( Rect r, Rect c, GameObject::ObjectType otype, std::string texturePath, int uniqueID , bool immune, int health, int damage) :
  MovingGameObject(r, c, otype, texturePath, uniqueID, immune, health, damage),
  m_jump_start_velocity(12.0),
  m_want_jump(false),
  m_doubleJump_used(false),
  m_start_pos(Point(r.x, r.y))
  {}

void Player::Init()
{
  
}

void Player::HandleCollision(GameObject* otherObject)
{
  
  MovingGameObject::HandleCollision(otherObject);
  
  HandleAcceleration(otherObject);
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
  
  if(!isDead()){
    renderer->drawTexture( getRect(), getTexturePath(), true);
    renderPistol(renderer);
  }
  else{
    //GetAnimation("DEATH")->DrawCurrentFrame(renderer, getRect());
    return;
  }
  
  GameObject::Draw(renderer);
}

void Player::Clean()
{
  
}

void Player::movement_left(){
  m_current_direction = LEFT;
  if (vx > -ax*10.0 + m_ground_friktion*10.0)
    vx -= ax;
}

void Player::movement_right(){
  m_current_direction = RIGHT;
  if (vx < ax*10.0 - m_ground_friktion*10.0)
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
  
  ProjectileManager::getInstance()->AddProjectile(BULLET_FILEPATH, m_uniqueTag++, GameObject::PLAYER, Rect(pistolHole.x,pistolHole.y,40,40), m_angle, 250, 3, 100);
}

void Player::JumpHandler(){
  
  if( contactTop ){
    vy = 0;
  }
  
  if ( contactBottom ){
    
    m_doubleJump_used = true;
  }


  if(m_want_jump && m_doubleJump_used){ // Start jumping procedure
    
      vy = -m_ground_jumpacceleration;
      m_doubleJump_used = false;
  }
  //else if( m_want_jump && !contactBottom && !m_doubleJump_used && vy >= -m_jump_start_velocity+4 ){ // if already in air
  //  vy = -m_jump_start_velocity;
  //  m_doubleJump_used = true;
  //}
  
  m_want_jump = false;
  
}

void Player::renderPistol(Renderer* renderer){
  Point center = getCenterPos(); //center of player
  center.x -= 20;
  center.y -= 20;
  Point centerSize(20, 20);
  int radius = 45; // pixels
  int radiusB = 70; // pixels
  
  Point adjustment = renderer->getCameraAdjustment();
  
  int mouseX = Input::getInstance()->get_mouse_x() + adjustment.x;
  int mouseY = Input::getInstance()->get_mouse_y() + adjustment.y;
  
  int deltaX, deltaY;
  
  deltaX = mouseX - center.x;
  deltaY = mouseY - center.y;
  
  m_angle = ( atan2(deltaY,deltaX) * 180 ) / 3.14;
  
  Point pistolPos;
  // Set pistol on circel around player...
  pistolPos.x = center.x + radius * cos(m_angle * 3.14/180);
  pistolPos.y = center.y + radius * sin(m_angle * 3.14/180);
  
  // Set pistol on circel around player...
  pistolHole.x = center.x + radiusB * cos(m_angle * 3.14/180);
  pistolHole.y = center.y + radiusB * sin(m_angle * 3.14/180);
  
  //Flip pistol if it is upsidedown
  if (m_angle < 90 && m_angle > -90)
    renderer->drawTexture( Rect(pistolPos.x,pistolPos.y,40,40), "imgs/pistol.png", true, Rect(0,0,50,50), false, false, centerSize, m_angle );
  else
    renderer->drawTexture( Rect(pistolPos.x,pistolPos.y,40,40), "imgs/pistol.png", true, Rect(0,0,50,50), false, true, centerSize, m_angle );
}

void Player::HandleAcceleration(GameObject* otherObject){
  
  if (otherObject->getObjectType() == PLATFORM){
    Platform* pl = dynamic_cast<Platform*>(otherObject);
    float temp = pl->getFriktion();
    m_ground_friktion = temp/10;
    m_ground_jumpacceleration = pl->getJumpAcceleration();
  }
  else
    m_ground_friktion = 5;
  
}


