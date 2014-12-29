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
    enum ObjectType {PLAYER, PLATFORM, INVI_PLATFORM, ENEMY};
    
    virtual void Init();
    
    virtual void HandleCollision(GameObject* otherObject) = 0;
    
    virtual void Update();
    
    virtual void Draw(Renderer* renderer);
    
    virtual void Clean();
    
    //Objects position functions
    Rect getRect(){ return m_rRect; }
    Rect getCollisionRect();
    
    Point getCenterPos(){ return Point(m_rRect.x + (m_rRect.w/2), m_rRect.y + (m_rRect.h/2)); }
    
    void updatePos(Point r){ m_rRect.x = r.x - m_rcollisionRect.x; m_rRect.y = r.y - m_rcollisionRect.x; }
    void updatePos_x(int x){ m_rRect.x = x - m_rcollisionRect.x; }
    void updatePos_y(int y){ m_rRect.y = y - m_rcollisionRect.y; }
    
    //Objects texture and types
    std::string getTexturePath() { return m_sTexturePath; }
    ObjectType getObjectType() { return m_eObjectType; }
    int getUniqueID(){ return m_iUniqueID; }
    
    // Check if object should for example, be rendered or updated...
    bool is_in_screen_range(Point screenCenter);
    
    // Object life handling
    void setDead();
    void setAlive();
    bool isDead();
    
  protected:
    
    GameObject( Rect r, Rect c, ObjectType oType, std::string texturePath, int uniqueID);
    
  private:
    
    ObjectType m_eObjectType;
    
    const std::string m_sTexturePath;
    
    Rect m_rRect; // very far sides of sprite
    const Rect m_rcollisionRect; // collision detection rectangle of sprite
    
    bool m_dead;
    
    bool m_bChanged;
    const int m_iUniqueID;

};

#endif