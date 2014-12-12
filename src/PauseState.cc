#include "PauseState.h"

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
            game->PopState();
            break;
      }
    }
  }
}
void PauseState::Update(Game* game)
{
  ;
}

void PauseState::Draw(Game* game, Renderer* renderer)
{
  //Sprite::Draw(game->getScreen(), pauseSprite, 0, 0);
  //SDL_Flip(game->getScreen());
}