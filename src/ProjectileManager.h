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
    
    std::vector<GameObject*> GetProjectiles() const;
	
    static ProjectileManager* getInstance(){
	if( !m_ProjectileManager )
	    m_ProjectileManager = new ProjectileManager();
	    
	return m_ProjectileManager;
    }
private:
    std::vector<GameObject*> m_projectiles;
    
    static ProjectileManager* m_ProjectileManager;
};