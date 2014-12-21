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
    
    virtual void Init();
    
    virtual void HandleCollision(GameObject* otherObject) = 0;
    
    virtual void Update();
    
    virtual void Draw(Renderer* renderer);
    
    virtual void Clean();
    
    //Objects position functions
    Rect getRect(){ return m_rRect; }
    Point getPoint(){ return Point(m_rRect.x, m_rRect.y); }
    int getPos_x(){ return m_rRect.x; }
    int getPos_y(){ return m_rRect.y; }
    
    int getWidth(){ return m_rRect.w; }
    int getHeight(){ return m_rRect.h; }
    
    Point getCenterPos(){ return Point(m_rRect.x + (m_rRect.w/2), m_rRect.y + (m_rRect.h/2)); }
    
    void updatePos(Point r){ m_rRect.x = r.x; m_rRect.y = r.y; }
    void updatePos_x(int x){ m_rRect.x = x; }
    void updatePos_y(int y){ m_rRect.y = y; }
    
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

    // Collision handling for each object
    //void setContactTop(){ contactTop = true; };
    //void setContactBottom(){ contactBottom = true; };
    //void setContactLeft(){ contactLeft = true; };
    //void setContactRight(){ contactRight = true; };
    
  protected:
    
    GameObject( Rect r, ObjectType oType, std::string texturePath, int uniqueID);
    
  private:
    
    ObjectType m_eObjectType;
    
    const std::string m_sTexturePath;
    
    Rect m_rRect;
    
    bool m_dead;
    
    bool m_bChanged;
    const int m_iUniqueID;

};

#endif