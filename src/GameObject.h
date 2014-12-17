#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>

#include "Rect.h"
#include "Constants.h"
#include "Renderer.h"

class GameObject
{
  public:
    enum ObjectType {PLAYER, PLATFORM, ENEMY};
    
    GameObject( Rect r, ObjectType oType, std::string texturePath, int uniqueID)
      : m_rRect(r), m_eObjectType(oType), m_sTexturePath(texturePath), m_iUniqueID(uniqueID)
    {}
    
    virtual void Init();
    
    virtual void Update();
    
    virtual void Draw(Renderer* renderer);
    
    virtual void Clean();
    
    Rect getRect(){ return m_rRect; }
    std::string getTexturePath() { return m_sTexturePath; }
    ObjectType getObjectType() { return m_eObjectType; }
    int getUniqueID(){ return m_iUniqueID; }
    
    void add_pos_x(int x);
    void add_pos_y(int y);
    
  private:
    ObjectType m_eObjectType;
    const std::string m_sTexturePath;
    Rect m_rRect;
    Rect m_drRect;
    bool m_bChanged;
    const int m_iUniqueID;
    
};

#endif