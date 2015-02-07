#include "PauseState.h"

#include "InputDefinition.h"

PauseState PauseState::m_PauseState;

void PauseState::Init()
{
  pauseSprite = nullptr;
  //playSprite = Sprite::Load("");
  printf("PauseState Init Successful\n");
}

void PauseState::Clean()
{
  printf("PauseState Clean Successful\n");
}

void PauseState::Pause()
{
  printf("PauseState Paused\n");
}
void PauseState::Resume()
{
  printf("PauseState Resumed\n");
}

void PauseState::HandleEvents(Game* game)
{
  if( Input::getInstance()->get_quit() )
      game->Quit();
      
  if(Input::getInstance()->is_key_pressed(KEY_ESCAPE))
      game->PopState();
      
}
void PauseState::Update(Game* game)
{
  ;
}

void PauseState::Draw(Game* game, Renderer* renderer)
{
  renderer->drawTexture(Rect<int>(0,0,renderer->getWindowSize().w, renderer->getWindowSize().h), BACKGROUND_PAUSEMENU_FILEPATH, false);
  //SDL_Flip(game->getScreen());
}