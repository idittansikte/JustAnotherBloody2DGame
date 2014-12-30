#include "ProjectileManager.h"
#include <iostream>
#include <algorithm>    // std::iter_swap
#include <utility>
#include <iterator>

ProjectileManager* ProjectileManager::m_ProjectileManager = nullptr;

ProjectileManager::ProjectileManager()
{}

ProjectileManager::~ProjectileManager()
{}


void ProjectileManager::CleanupDead(){
    m_projectiles.erase(std::remove_if(m_projectiles.begin(), m_projectiles.end(), [](GameObject* p) { return p->isDead() == true; }), m_projectiles.end());
}

void ProjectileManager::Update(){
    
    CleanupDead();
    
    for (std::vector<GameObject*>::iterator it = m_projectiles.begin(); it != m_projectiles.end(); ++it){
	// Update projectile...
	(*it)->Update();
    }
    //std::cout << m_projectiles.size() << std::endl;
}

void ProjectileManager::DrawAll(Renderer* renderer){
    
    for (auto it : m_projectiles)
    {
      it->Draw(renderer);
    }
    
}

void ProjectileManager::AddProjectile(std::string file_path, int uniqueTag, GameObject::ObjectType shooter, Rect startRectange, Point targetPos, int distance, int speed, int damage){
    m_projectiles.push_back(new Projectile(startRectange, Rect(0,0,startRectange.w,startRectange.h),
					   GameObject::PROJECTILE, file_path, uniqueTag, shooter, targetPos, distance, speed, damage));
}

std::vector<GameObject*> ProjectileManager::GetProjectiles() const {
    return m_projectiles;
}