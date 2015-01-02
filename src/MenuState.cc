#include "MenuState.h"
#include "PlayState.h"

#include "Constants.h"
#include "InputDefinition.h"

MenuState MenuState::m_MenuState;

void MenuState::Init()
{
  //menuSprite = Sprite::Load("");
  printf("MenuState Init Successful\n");
}

void MenuState::Clean()
{
  printf("MenuState Clean Successful\n");
}

void MenuState::Pause()
{
  printf("MenuState Paused\n");
}
void MenuState::Resume()
{
  printf("MenuState Resumed\n");
}

void MenuState::HandleEvents(Game* game)
{
  if( Input::getInstance()->get_quit() )
      game->Quit();
      
  if(Input::getInstance()->is_key_pressed(KEY_SPACE))
      game->ChangeState(PlayState::Instance());
      
}
void MenuState::Update(Game* game)
{
;
}

void MenuState::Draw(Game* game, Renderer* renderer)
{
  renderer->drawTexture( Rect(0,0,renderer->getWindowSize().w, renderer->getWindowSize().h), MENU_BACKGROUND_FILEPATH, false);
}