#include "Game.h"
#include "GameState.h"
#include <iostream>

using namespace std;

Game::Game()
{
  
}

void Game::Init()
{
  m_bRunning = true;
  mRenderer = new Renderer();
  mRenderer->Init();
}

void Game::ChangeState(GameState* state)
{
  // cleanup the current state
  if( !m_vStates.empty() )
  {
    m_vStates.back()->Clean();
    m_vStates.pop_back();
  }
  
  //stor and init the new state
  m_vStates.push_back(state);
  m_vStates.back()->Init();
}

void Game::PushState(GameState* state)
{
  // Pause current state
  if( !m_vStates.empty() )
  {
    m_vStates.back()->Pause();
  }
  
  // Store and init new state
  m_vStates.push_back(state);
  m_vStates.back()->Init();
}

void Game::PopState()
{
  // cleanup and resume previous state
  if( !m_vStates.empty() )
  {
    m_vStates.back()->Clean();
    m_vStates.pop_back();
  }
  
  if( !m_vStates.empty() )
  {
    m_vStates.back()->Resume();
  }
}


void Game::HandleEvents()
{       
  // Lets move this to the current state instead
  m_vStates.back()->HandleEvents(this);
}

void Game::Update()
{
  Input::getInstance()->update();
  // Lets move this to the current state
  for ( auto it : m_vStates )
    it->Update(this);
}

void Game::Draw()
{
  mRenderer->beginScene();
  // Lets move this to the current state
  for ( auto it : m_vStates )
    it->Draw(this, mRenderer);
  
  mRenderer->endScene();
}

void Game::Clean()
{
  while( !m_vStates.empty() )
  {
    m_vStates.back()->Clean();
    m_vStates.pop_back();
  }
  mRenderer->Clean();
}
