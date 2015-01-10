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
    
    
    void AddProjectile(Projectile* np);
    
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