#ifndef FILE_H
#define FILE_H

#include <string>

#include "LevelData.h"
#include "GameObject.h"

class File
{
  public:
    File(){}
    ~File(){}
    
    LevelData load(std::string filename);
    
    void save(LevelData lData);
};

#endif