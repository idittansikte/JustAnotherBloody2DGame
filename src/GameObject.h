#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Rect.h"
#include "Constants.h"
#include "Renderer.h"
class GameObject
{
  public:
    
  GameObject( Rect r, Renderer::ObjectType type)
    : m_rRect(r), m_iType(type)
  {}
  
  virtual void Init();
  
  virtual void Update();
  
  virtual void Draw(Renderer* renderer);
  
  virtual void Clean();
  
  private:
  Renderer::ObjectType m_iType;
  Rect m_rRect;
};

#endif