#include "File.h"

#include <fstream>
#include <iostream>
#include <vector>
#include "gameobjects/Platform.h"

LevelData File::load(std::string filepath, std::string filename)
{
  printf("Loading file...\n");
  
  std::string path;
  path.append(filepath);
  path.append(filename);
  path.append(".level");
  
  LevelData lData;
  
  std::ifstream load(path.c_str(), std::ios_base::binary);
  
  if(load.is_open())
  {
    int ObjectType;
    
    load >> ObjectType;
    
    if ( ObjectType == GameObject::PLATFORM )
    {
      
    }
    
    
    load.close();
    printf("Load successful\n");
  }
  else
  {
    std::cerr << "Could not open: " << path <<  "\n";
  }
}

void File::save(LevelData lData)
{
  
}