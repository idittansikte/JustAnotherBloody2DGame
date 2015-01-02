#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>

#include "../Renderer.h"
#include "../Rect.h"
#include "../Constants.h"
#include "../Point.h"
#include "../Animation.h"
#include "gadgets/Bar.h"


class GameObject
{
  public:
    enum ObjectType {PLAYER, PLATFORM, INVI_PLATFORM, ENEMY, PROJECTILE};
    
    virtual void Init();
    
    virtual void HandleCollision(GameObject* otherObject);
    
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
    int getUniqueTag(){ return m_iUniqueID; }
    void changeUniqueTag(int tag){ m_iUniqueID = tag; }
    
    // Check if object should for example, be rendered or updated...
    bool is_in_screen_range(Point screenCenter, Rect screenSize);
    
    // Object life handling
    void setDead();
    void setAlive();
    bool isDead();
    
    void AddAnimation(std::string animationName, Animation* newAnimation);
    Animation* GetAnimation(std::string animationName);
    void CloneAnimations();
    
    int getMaxHealth(){ return m_max_health;}	
    int getCurrentHealth(){ return m_health;}
    
    Bar* m_bar;

  protected:
    GameObject( Rect r, Rect c, ObjectType oType, std::string texturePath, int uniqueID, bool immune, int health, int damage);
    
    virtual GameObject* Clone() = 0;
    
    
    const int m_max_health;
    int m_health;
    bool m_immune;
    const int m_damage;
    
  private:
    
    ObjectType m_eObjectType;
    
    const std::string m_sTexturePath;
    
    Rect m_rRect; // very far sides of sprite
    const Rect m_rcollisionRect; // collision detection rectangle of sprite
    
    bool m_dead;
    
    bool m_bChanged;
    int m_iUniqueID;
    
    std::map<std::string, Animation*> m_animations;

};

#endif