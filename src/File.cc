#include "File.h"

#include <fstream>
#include <vector>

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
    
    if ( ObjectType == GameObject::Platform )
    {
      
    }
    
    
    load.close();
    printf("Load successful\n");
  }
  else
  {
    printf("Could not open: ", path, "\n");
  }
}

void File::save(LevelData lData)
{
  
}