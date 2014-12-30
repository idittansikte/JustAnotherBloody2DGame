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
    ;
}

void ProjectileManager::Update(){
    
    for (auto it : m_projectiles)
    {
	// Cleanup deads...
	if(it->isDead()){
	    std::swap( it, m_projectiles.back() );
	    m_projectiles.pop_back();
	}
	// Update projectile...
      it->Update();
    }
    
    std::cout << m_projectiles.size() << std::endl;
    
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