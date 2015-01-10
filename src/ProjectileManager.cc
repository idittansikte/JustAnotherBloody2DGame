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
    //m_projectiles.erase(std::remove_if(m_projectiles.begin(), m_projectiles.end(), []( std::pair<int, GameObject*> p ) { return p.second->isDead() == true; }), m_projectiles.end());
}

void ProjectileManager::Update(){
    
    //CleanupDead();
    
    for (std::multimap<int, GameObject*>::iterator it = m_projectiles.begin(); it != m_projectiles.end(); ++it){
	
	// Remove dead ones
	if( (*it).second->isDead() )
	    m_projectiles.erase(it);
	    
	// Update projectile...
	(*it).second->Update();
    }
    //std::cout << m_projectiles.size() << std::endl;
}

void ProjectileManager::DrawAll(Renderer* renderer){
    
    for (auto it : m_projectiles)
    {
      it.second->Draw(renderer);
    }
    
}

void ProjectileManager::AddProjectile(Projectile* np){
    m_projectiles.insert( std::make_pair( 4, np ) );
}


std::multimap<int, GameObject*> ProjectileManager::GetProjectiles() const {
    return m_projectiles;
}