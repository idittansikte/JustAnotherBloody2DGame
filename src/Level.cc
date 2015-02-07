#include <iostream>
#include <utility>

#include "Level.h"
#include "gameobjects/Player.h"
#include "gameobjects/Platform.h"
#include "gameobjects/Projectile.h"
#include "Constants.h"
#include "Point.h"
#include "Input.h"
#include "ProjectileManager.h"
#include "gameobjects/Enemy.h"

#include <fstream>
#include <sstream>


class Platform;
class GameObjectManager;

Level::Level(std::string map_path):
  m_iWorldWidth(4000),
  m_iWorldHeight(4000)
{
  //GameObjectManager::Instance()->loadGameObjectsFromFile();
  
  if(!map_path.empty() )
    Load(map_path);
  
  m_Player = nullptr;
  
  m_StaticColliesGrid = new Collision( m_iWorldWidth, m_iWorldHeight );
  m_MovingColliesGrid = new Collision( m_iWorldWidth, m_iWorldHeight );
    
  m_objectLists.push_back(&m_vMovingGameObjects);
  m_objectLists.push_back(&m_vStaticGameObjects);
  m_objectLists.push_back(&m_vMiscGameObjects);
  m_objectLists.push_back(&m_vEditorList);
}

Level::~Level()
{
  // Delete all created objects(pointers) in Level..
  std::vector< std::multimap<int, GameObject*>* >::iterator it;
  for(it = m_objectLists.begin(); it != m_objectLists.end(); ++it){
    std::multimap<int, GameObject*>::iterator object;
    for(object = (*it)->begin(); object != (*it)->end(); ++object){
      delete object->second;
      object->second = nullptr;
    } // End of second loop
  } // End of firest loop
}

void Level::Init()
{
    //Update Only needed once cuz static object wont move...
  m_StaticColliesGrid->AddToGrid(m_vStaticGameObjects, Point(), m_screenSize, false );
}

void Level::Load( std::string levelname ){
  std::stringstream ss;
  ifstream input;
  input.open(levelname, ios::in | ios::binary);

  if(!input){
    std::cerr << levelname << " could not be loaded!\n";
    return;
  }
  std::string str;
  while( std::getline(input, str) ){
    if( str.at(0) == ' ' ){
      continue;
    }
    
    int layer, x, y = 0;
    std::string name = "";
    
    ss << str;
    ss >> layer >> name >> x >> y;
    
    GameObject* no = GameObjectManager::Instance()->GetGameObject(name);
    if( no != nullptr){
        
      if(no->getType() == GameObject::PLATFORM){ // Its a platfrom
        no->Init(Point(x, y), uniqueTag++);
        m_vStaticGameObjects.insert( std::make_pair( layer, no) );
      }
      else if(no->getType() == GameObject::ENEMY){ // Its a enemy
        Enemy* enemy = dynamic_cast<Enemy*>(no);
        enemy->Init(Point(x, y), uniqueTag++, m_Player);
        m_vMovingGameObjects.insert( std::make_pair( layer, enemy) );
      }
      else if(no->getType() == GameObject::PLAYER){ // Its a player
        m_Player = dynamic_cast<Player*>(no);
        m_Player->Init(Point(x, y), uniqueTag++);
        m_vMovingGameObjects.insert( std::make_pair( layer, m_Player) );
      }
    }
    else
      std::cerr << name << " does not exist and could not be added.\n";
      
    ss.str(""); // Clean ss
    ss.clear(); // Clear ss flags...
    
  } // END OF FILE
}

std::multimap<int,GameObject*>* Level::GetEditorList(){
  return &m_vEditorList;
}

void Level::Update()
{
   // Cleanup last frame grid for movingsobject to make a new one.
  m_MovingColliesGrid->CleanGrid();
  
  // Update all projectiles
  ProjectileManager::getInstance()->Update();
  
  // Update all objects...
  for( auto p : m_objectLists){
    for( auto k : *p ){
      k.second->Update();
    }
  }
    
    // Update the grid of moving objects
  m_MovingColliesGrid->AddToGrid(m_vMovingGameObjects, Point(m_screenSize.w/2, m_screenSize.h/2), m_screenSize, false );
  m_MovingColliesGrid->AddToGrid(ProjectileManager::getInstance()->GetProjectiles(), Point(m_screenSize.w/2, m_screenSize.h/2), m_screenSize, false );
  
  // Check collision between static and moving objects
  vector<pair<GameObject*, GameObject*>> colliesMS = m_MovingColliesGrid->getColliedPairs(m_StaticColliesGrid);
  vector<pair<GameObject*, GameObject*>> colliesMM = m_MovingColliesGrid->getColliedPairs(m_MovingColliesGrid);
  
  //Merge into one ..
  vector<pair<GameObject*, GameObject*>> collies;
  std::copy(colliesMS.begin(), colliesMS.end(), std::back_inserter(collies));
  std::copy(colliesMM.begin(), colliesMM.end(), std::back_inserter(collies));
  
  // Handle collied pairs if there where any...
  if ( !collies.empty() ){
    for (auto it : collies){
      it.first->HandleCollision(it.second);
      it.second->HandleCollision(it.first);
      //std::cout << "Collied: " << it.first->getRect().x << " " << it.second->getRect().x << std::endl;
    }
  }
}

void Level::Draw(Renderer* renderer)
{
  //UpdateScreen Size
  m_screenSize = renderer->getWindowSize();
  
  //Update camera to the current center of SCREEN before any other draws on map...
  if(m_Player != nullptr)
    SetCamera(m_Player->getRect());

  UpdateCamera(renderer);
  
  // Draw all objects, first layer first then second...
  const int max_layers = 5;
  int current_layer = 0;
  for(; current_layer <= max_layers; ++current_layer ){
    std::pair< std::multimap<int, GameObject*>::iterator, std::multimap<int, GameObject*>::iterator > it;

    for( auto p : m_objectLists){
        if(p->size() != 0){
          it = p->equal_range(current_layer);
          for( std::multimap<int, GameObject*>::iterator pp = it.first; pp != it.second; ++pp){
            (*pp).second->Draw(renderer);
          }
        }
    }
  }
  
  ProjectileManager::getInstance()->DrawAll(renderer);
}

void Level::Clean()
{
  
}

void Level::Reset(){
  for( auto p : m_objectLists){
    for( auto k : *p ){
      k.second->Reset();
    }
  }
}

void Level::SetCamera(Rect<int> campos){
  m_camera_position = campos;
}

void Level::UpdateCamera(Renderer* renderer){
  renderer->updateCamera(m_camera_position, m_iWorldWidth, m_iWorldHeight);
}