#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>

#include "../Renderer.h"
#include "../Rect.h"
#include "../Constants.h"
#include "../Point.h"

class GameObject
{
  public:
    enum ObjectType {PLAYER, PLATFORM, ENEMY};
    
    GameObject( Rect r, ObjectType oType, std::string texturePath, int uniqueID);
    
    virtual void Init();
    
    virtual void HandleCollision(GameObject* otherObject) = 0;
    
    virtual void Update();
    
    virtual void Draw(Renderer* renderer);
    
    virtual void Clean();
    
    Rect getRect(){ return m_rRect; }
    Point getPoint(){ return Point(m_rRect.x, m_rRect.y); }
    void updatePos(Point r){ m_rRect.x = r.x; m_rRect.y = r.y; }
    std::string getTexturePath() { return m_sTexturePath; }
    ObjectType getObjectType() { return m_eObjectType; }
    int getUniqueID(){ return m_iUniqueID; }
    
    void setDead();
    void setAlive();
    bool isDead();

    
  private:
    
    ObjectType m_eObjectType;
    
    const std::string m_sTexturePath;
    
    Rect m_rRect;
    
    bool m_dead;
    
    bool m_bChanged;
    const int m_iUniqueID;
    
    
};

#endif