#include "gameobjects/GameObject.h"
#include "gameobjects/Projectile.h"

#include <string>
#include <vector>

class ProjectileManager
{
public:
    
    ProjectileManager();
    ~ProjectileManager();
    
    void CleanupDead();
    
    void Update();
    
    void DrawAll(Renderer* renderer);
    
    
    void AddProjectile(std::string file_path, int uniqueTag, GameObject::ObjectType shooter, Rect startRectange, Point targetPos, int speed, int distance, int damage);
    void AddProjectile(std::string file_path, int uniqueTag, GameObject::ObjectType shooter, Rect startRectange, float angle, int speed, int distance, int damage);
    std::multimap<int, GameObject*> GetProjectiles() const;
	
    static ProjectileManager* getInstance(){
	if( !m_ProjectileManager )
	    m_ProjectileManager = new ProjectileManager();
	    
	return m_ProjectileManager;
    }
private:
    std::multimap<int, GameObject*> m_projectiles;
    
    static ProjectileManager* m_ProjectileManager;
};