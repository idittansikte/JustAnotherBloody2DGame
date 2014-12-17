#include "Collision.h"
#include "Rect.h"


Collision::Collision()
  {}

void Collision::init(int collisionGridSize, int ww, int wh)
{
  m_CollisionGridSize = collisionGridSize;
  WORLD_WIDTH = ww;
  WORLD_HEIGHT = wh;
}

void Collision::update( vector<GameObject*> ObjectList )
{
  
  int gridWidth = WORLD_WIDTH / m_CollisionGridSize;
  int gridHeight = WORLD_HEIGHT / m_CollisionGridSize;
  
  int cObjectMinX, cObjectMinY, cObjectMaxX, cObjectMaxY;
  
  int gridCol, gridCell;
  
  int totalCells = gridWidth * gridHeight;
  
  grid.resize(gridWidth);
  
  for( unsigned int i{}; i < ObjectList.size(); ++i)
  {
    GameObject* cObject = ObjectList[i];
    
    // Check if Object is outside of WORLD size
    if ( cObject->getRect().x < 0 || cObject->getRect().x > WORLD_WIDTH
        || cObject->getRect().y < 0 || cObject->getRect().y > WORLD_HEIGHT ){
      continue;
    }
    
    cObjectMinX = cObject->getRect().x / m_CollisionGridSize;
    cObjectMinY = cObject->getRect().y / m_CollisionGridSize;
    cObjectMaxX = ( cObject->getRect().x + cObject->getRect().w ) / m_CollisionGridSize;
    cObjectMaxY = ( cObject->getRect().y + cObject->getRect().h ) / m_CollisionGridSize;
    
    for ( unsigned int cX{cObjectMinX}; cX < cObjectMaxX; ++cX )
    {
      if ( grid[cX].empty() )
        grid[cX].resize(gridHeight);
      
      for ( unsigned int cY{cObjectMinY}; cY < cObjectMaxY; ++cY)
      {
        allocatedCells += 1;
        grid[cX][cY].push_back(cObject);
      }
    }
  }
  
}
  

vector<pair<GameObject*, GameObject*>> Collision::findColliedPairs()
{
  vector<pair<GameObject*, GameObject*>> cColliedPairs;
  //For every column in grid
  for( unsigned int i{}; i < grid.size(); ++i)
  {
    if (grid[i].empty())
      continue;
    //For every cell in column
    for( unsigned int j{}; j < grid[i].size(); ++j )
    {
      if ( grid[i].empty())
        continue;
      
      // For every object in cell
      for( unsigned int k{}; k < grid[i][j].size(); ++k )
      {
        GameObject* GameObjectA = grid[i][j][k];
        // For every other object in cell
        for( unsigned int l{k+1}; l < grid[i][j].size(); ++l )
        {
          GameObject* GameObjectB = grid[i][j][l];
          
          std::string hashA = to_string(GameObjectA->getUniqueID()) + ':' + to_string(GameObjectB->getUniqueID());
          std::string hashB = to_string(GameObjectB->getUniqueID()) + ':' + to_string(GameObjectA->getUniqueID());
          
          if( !m_mChecked[hashA] && !m_mChecked[hashB] )
          {
              m_mChecked[hashA] = m_mChecked[hashB] = true;
              
              if ( aabbIntersection(GameObjectA, GameObjectB) )
              {
                cColliedPairs.push_back( make_pair( GameObjectA, GameObjectB ) );
              }
          }
        }
      }
    }
  }
  return cColliedPairs;
}

bool Collision::aabbIntersection(GameObject* objA, GameObject* objB)
{
  Rect a = objA->getRect();
  Rect b = objB->getRect();
  
  int aBottom, aUpper, aLeft, aRight,
      bBottom, bUpper, bLeft, bRight;
      
  aBottom = a.y + a.h;
  aUpper = a.y;
  aLeft = a.x;
  aRight = a.x + a.w;
  
  bBottom = b.y + b.h;
  bUpper = b.y;
  bLeft = b.x;
  bRight = b.x + b.w;
  
  if ( ( aBottom > bUpper && aLeft < bRight ) || ( aBottom > bUpper && aRight > bLeft )
      || ( aUpper < bBottom && aLeft < bRight ) || ( aUpper < bBottom && aLeft > bRight ) )
    return true;
  return false;
  
}