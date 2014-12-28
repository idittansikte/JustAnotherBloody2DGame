#include "PlayState.h"
#include "PauseState.h"

#include "InputDefinition.h"


PlayState PlayState::m_PlayState;

PlayState::PlayState():
  m_is_paused(false)
{ }

void PlayState::Init()
{
  m_Level = new Level();
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
      
  if(Input::getInstance()->is_key_pressed(KEY_SPACE))
      game->PushState(PauseState::Instance());
      
  if(Input::getInstance()->is_key_pressed(KEY_RIGHT))
      m_Level->getPlayer()->movement_right();
      
  if(Input::getInstance()->is_key_pressed(KEY_LEFT))
      m_Level->getPlayer()->movement_left();
  
  if(Input::getInstance()->is_key_pressed(KEY_UP))
      m_Level->getPlayer()->movement_up();
      
  if(Input::getInstance()->is_key_pressed(KEY_DOWN))
      m_Level->getPlayer()->movement_down();
      
}
void PlayState::Update(Game* game)
{
  if( !m_is_paused )
    m_Level->Update();
}

void PlayState::Draw(Game* game, Renderer* renderer)
{

  m_Level->Draw(renderer);
  //Sprite::Draw(game->getScreen(), playSprite, 0, 0);
  //SDL_Flip(game->getScreen());
}