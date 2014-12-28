#include "Collision.h"
#include "Rect.h"

#include <iostream>


Collision::Collision(int ww, int wh):
  m_CollisionGridSize(300),
  m_isGrid(false),
  WORLD_WIDTH(ww),
  WORLD_HEIGHT(wh)
{}

void Collision::update_grid( vector<GameObject*> ObjectList, Point center, bool update_only_visable )
{
  //std::cout << "Updating collision grid... " << std::endl;
  allocatedCells = 0;
  grid.clear();
  m_isGrid = true;
  int gridWidth = WORLD_WIDTH / m_CollisionGridSize;
  int gridHeight = WORLD_HEIGHT / m_CollisionGridSize;
  
  int cObjectMinX, cObjectMinY, cObjectMaxX, cObjectMaxY;
  
  int gridCol, gridCell;
  
  int totalCells = gridWidth * gridHeight;
  
  grid.resize(gridWidth);
  
  //For all objects in list...
  for( unsigned int i{}; i < ObjectList.size(); ++i)
    {
	GameObject* cObject = ObjectList[i];
    
      // Check if Object is outside of SCREEN_SIZE size, dont update... (because we dont want any uneeded checked that drain power from our system)
      if (update_only_visable){
	if ( !cObject->is_in_screen_range(center) ){
          continue;
	}
      }
    
      // Get witch [start and end] column and cell object should be placed in  
      cObjectMinX = cObject->getRect().x / m_CollisionGridSize;
      cObjectMinY = cObject->getRect().y / m_CollisionGridSize;
      cObjectMaxX = ( cObject->getRect().x + cObject->getRect().w ) / m_CollisionGridSize;
      cObjectMaxY = ( cObject->getRect().y + cObject->getRect().h ) / m_CollisionGridSize;
      // For every grid column object is inside:
      for ( int cX{cObjectMinX}; cX <= cObjectMaxX; ++cX )
	{
	  if ( grid[cX].empty() )
	    grid[cX].resize(gridHeight);
        
	  // For every grid cell object is inside:
	  for ( int cY{cObjectMinY}; cY <= cObjectMaxY; ++cY)
	    {
	      allocatedCells += 1; // Just a simple counter for testing...
	      grid[cX][cY].push_back(cObject); //Add Object to grid cell.
	    }
	}
    }
  //std::cout << "allocatedCells " << allocatedCells << " gridWidth " << gridWidth << " gridHeight " << gridHeight << std::endl;
  //std::cout << "Updated collision grid successfull... " << std::endl;
}

vector<pair<GameObject*, GameObject*>> Collision::getColliedPairs(Collision* otherList)
{
  if (otherList == nullptr)
    otherList = this;
  vector<pair<GameObject*, GameObject*>> cColliedPairs; // Vector wich we will return
  map<std::string, bool> m_mChecked; //To know wich objects we have checked..
  //For every column in this grid
  for( unsigned int i{}; i < grid.size(); ++i)
    {
      // If column empty, move on
      if (this->grid[i].empty() || otherList->grid[i].empty())
	continue;
      //For every cell in this column
      for( unsigned int j{}; j < this->grid[i].size(); ++j )
	{
	  // If cell empty, move on
	  if ( this->grid[i][j].empty() || otherList->grid[i][j].empty())
	    continue;
      
	  // For every object in this cell
	  for( unsigned int k{}; k < this->grid[i][j].size(); ++k )
	    {
	      GameObject* GameObjectA = this->grid[i][j][k];
        
	      unsigned int l;
	      if(otherList == this)
		l = k+1; // if we check this with this, we dont need to scan whole list all the time.
	      else
		l = 0;
          
	      // For every object in otherList cell (can be this)
	      for(; l < otherList->grid[i][j].size(); ++l )
		{
		  GameObject* GameObjectB = otherList->grid[i][j][l];
            
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

int get_grid_col(int x_value)
{
  
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
  
  if ( ( aBottom > bUpper ) && ( aRight > bLeft )
       && ( aUpper < bBottom ) && ( aLeft < bRight ) )
    return true;
  return false;
  
}
