#include "MenuState.h"
#include "PlayState.h"

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
  SDL_Event event;
  
  if( SDL_PollEvent(&event) )
  {
    switch( event.type )
    {
      case SDL_QUIT:
        game->Quit();
        break;
      
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym){
          case SDLK_SPACE:
            game->ChangeState(PlayState::Instance());
            break;
        }
    }
  }
}
void MenuState::Update(Game* game)
{
  ;
}

void MenuState::Draw(Game* game, Renderer* renderer)
{
  renderer->drawTexture( Rect(0,0,SCREEN_WIDTH, SCREEN_HEIGHT), Renderer::MENU_BACKGROUND, false);
}