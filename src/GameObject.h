#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Rect.h"
#include "Constants.h"
#include "Renderer.h"
class GameObject
{
  public:
    
    GameObject( Rect r, Renderer::ObjectType type, int uniqueID)
      : m_rRect(r), m_eType(type), m_iUniqueID(uniqueID)
    {}
    
    virtual void Init();
    
    virtual void Update();
    
    virtual void Draw(Renderer* renderer);
    
    virtual void Clean();
    
    Rect getRect(){ return m_rRect; }
    Renderer::ObjectType getType() { return m_eType; }
  
  private:
    Renderer::ObjectType m_eType;
    Rect m_rRect;
    Rect m_drRect;
    bool m_bChanged;
    const int m_iUniqueID;
    
};

#endif