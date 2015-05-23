#include "PlayState.h"
#include "PauseState.h"
#include "MenuState.h"
#include "InputDefinition.h"
#include "Level.h"


PlayState PlayState::m_PlayState;

PlayState::PlayState():
  m_is_paused(false)
{ }

void PlayState::Init()
{
  m_Level = new Level("Level.dat");
  m_Level->Init();
  //playSprite = Sprite::Load("");
  printf("PlayState Init Successful\n");
}

void PlayState::Clean()
{
  printf("PlayState Clean Successful\n");
}

void PlayState::Pause()
{
  m_is_paused = true;
  printf("PlayState Paused\n");
}
void PlayState::Resume()
{
  m_is_paused = false;
  printf("PlayState Resumed\n");
}

void PlayState::HandleEvents(Game* game)
{
  if( Input::getInstance()->get_quit() )
      game->Quit();
      
  if(Input::getInstance()->is_key_down(KEY_SPACE))
      game->PushState(PauseState::Instance());
  
  if(Input::getInstance()->is_key_pressed(KEY_RIGHT) || Input::getInstance()->is_key_pressed(KEY_D))
      m_Level->getPlayer()->movement_right();
  
  if(Input::getInstance()->is_key_pressed(KEY_LEFT) || Input::getInstance()->is_key_pressed(KEY_A))
      m_Level->getPlayer()->movement_left();
  
  if(Input::getInstance()->is_key_down(KEY_UP) || Input::getInstance()->is_key_down(KEY_W))
      m_Level->getPlayer()->movement_up();
      
  if(Input::getInstance()->is_key_down(KEY_F12))
      m_Level->Reset();
      
  if(Input::getInstance()->is_key_pressed(KEY_DOWN) || Input::getInstance()->is_key_pressed(KEY_S))
      m_Level->getPlayer()->movement_down();
      
  if(Input::getInstance()->is_mouse_down(MOUSE_LEFT))
      m_Level->getPlayer()->movement_shoot();
}
void PlayState::Update(Game* game)
{
  if(m_Level->getPlayer() == nullptr){
    printf("There are no player in game...Returning to Menu\n");
    game->ChangeState(MenuState::Instance());
    return;
  }

  if( !m_is_paused ){
    printf("HERE!\n");
    if( m_Level->getPlayer()->isDead() ){
      printf("HERE!\n");
      m_Level->Reset();
    }
    m_Level->Update();
  }
}

void PlayState::Draw(Game* game, Renderer* renderer)
{

  m_Level->Draw(renderer);
  DrawCursor(renderer);
}


void PlayState::DrawCursor(Renderer* renderer){
  Point camAdj = renderer->getCameraAdjustment();
  Rect<int> A(Input::getInstance()->get_mouse_x()-10 + camAdj.x, Input::getInstance()->get_mouse_y()-10 + camAdj.y, 20, 20 );
  renderer->drawTexture(A, "imgs/aim.png", true);
  renderer->DisableCursor(true);
}
