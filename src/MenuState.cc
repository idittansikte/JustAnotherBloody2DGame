#include "MenuState.h"
#include "PlayState.h"
#include "EditorState.h"

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
      
  if( Input::getInstance()->is_key_pressed(KEY_SPACE) )
      game->ChangeState(PlayState::Instance());
  
  if(Input::getInstance()->is_mouse_down(MOUSE_LEFT)){
      if( Input::getInstance()->is_mouse_inside(Rect<int>(0,0,50,50)) ){
        printf("EditorState CLICK\n");
	game->ChangeState(EditorState::Instance());
      }
  }
}
void MenuState::Update(Game* game)
{
;
}

void MenuState::Draw(Game* game, Renderer* renderer)
{
  renderer->drawTexture( Rect<int>(0,0,renderer->getWindowSize().w, renderer->getWindowSize().h), MENU_BACKGROUND_FILEPATH, false);
}