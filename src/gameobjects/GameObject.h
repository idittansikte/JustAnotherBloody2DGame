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
    enum ObjectType {NONE, PLAYER, PLATFORM, ENEMY, PROJECTILE};
    
    void Init(Point startpos, int uniquetag);
    
    virtual void Reset();
    
    virtual void HandleCollision(GameObject* otherObject);
    
    virtual void Update();
    
    virtual void Draw(Renderer* renderer);
    
    //Objects position functions
    Rect<int> getRect(){ return m_rRect; }
    Point getPos() { return Point(m_rRect.x, m_rRect.y); }
    Rect<int> getCollisionRect();
    
    Point getCenterPos(){ return Point(m_rRect.x + (m_rRect.w/2), m_rRect.y + (m_rRect.h/2)); }
    
    void updatePos(Point r){ m_rRect.x = r.x - m_rcollisionRect.x; m_rRect.y = r.y - m_rcollisionRect.x; }
    void updatePos_x(int x){ m_rRect.x = x - m_rcollisionRect.x; }
    void updatePos_y(int y){ m_rRect.y = y - m_rcollisionRect.y; }
    
    //Objects texture and types
    std::string getTexturePath() { return m_sTexturePath; }
    virtual ObjectType getType() = 0;
    int getUniqueTag(){ return m_iUniqueID; }
    void changeUniqueTag(int tag){ m_iUniqueID = tag; }
    
    // ObjectName
    std::string GetName(){ return m_objectName; }
    void SetName( std::string name ){ m_objectName = name; }
    
    // Check if object should for example, be rendered or updated...
    bool is_in_screen_range(Point screenCenter, Rect<int> screenSize);
    
    // Object life handling
    void setDead();
    void setAlive();
    bool isDead();
    
    bool getImmune() const { return m_immune; }
    int getDamage() const { return m_damage; }
    
    
    void AddAnimation(std::string animationName, Animation* newAnimation);
    Animation* GetAnimation(std::string animationName);
    void CloneAnimations();
    
    int getMaxHealth() const { return m_max_health;}	
    int getCurrentHealth() const { return m_health;}
    void DrainHealth(int damage);
    
    Bar* m_bar; // Healthbar
    
    virtual GameObject* Clone() = 0;

  protected:
    GameObject( Rect<int> r, Rect<int> c, std::string texturePath, int uniqueID, bool immune, int health, int damage);
    
    
    const int m_max_health;
    int m_health;
    bool m_immune;
    const int m_damage;
    
  private:
    std::string m_objectName;
    const std::string m_sTexturePath;
    
    Rect<int> m_rRect; // very far sides of sprite
    const Rect<int> m_rcollisionRect; // collision detection rectangle of sprite
    
    bool m_dead;
    
    bool m_bChanged;
    int m_iUniqueID;
    
    std::map<std::string, Animation*> m_animations;

};

#endif