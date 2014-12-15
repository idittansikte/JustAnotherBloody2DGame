#include "PlayState.h"
#include "PauseState.h"

PlayState PlayState::m_PlayState;

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
  printf("PlayState Paused\n");
}
void PlayState::Resume()
{
  printf("PlayState Resumed\n");
}

void PlayState::HandleEvents(Game* game)
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
            game->PushState(PauseState::Instance());
            break;
          case SDLK_UP:
            
            break;
          case SDLK_DOWN:
            
            break;
          case SDLK_LEFT:
            
            break;
          case SDLK_RIGHT:
            
            break;
          
        }
    }
  }
}
void PlayState::Update(Game* game)
{
  m_Level->Update();
}

void PlayState::Draw(Game* game, Renderer* renderer)
{

  m_Level->Draw(renderer);
  //Sprite::Draw(game->getScreen(), playSprite, 0, 0);
  //SDL_Flip(game->getScreen());
}