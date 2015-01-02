#include "GameObjectManager.h"

#include <fstream>
#include <iostream>
#include <string>
#include <utility>

GameObjectManager::GameObjectManager(const std::string& filename)
{
    m_luaScript = new LuaScript(filename);
}

GameObjectManager::~GameObjectManager()
{}


void GameObjectManager::loadGameObjectsFromFile(){
    
    //std::vector<std::string> v;
    //v = LS.getTableKeys("Platform");
    LoadPlatforms();
    LoadEnemys();
    
}

void GameObjectManager::LoadGameObjectSpecifics(Variables& var, const std::string global){

	std::vector<int> v_tmp;
	var.spritesheet = m_luaScript->get<std::string>(global + ".Spritesheet");
	v_tmp = m_luaScript->getIntVector(global + ".Size");
	var.size.x = 800;
	var.size.y = 300;
	var.size.w = v_tmp.at(0);
	var.size.h = v_tmp.at(1);
	v_tmp = m_luaScript->getIntVector(global + ".Collisionbox");
	var.collisionbox.x = v_tmp.at(0);
	var.collisionbox.y = v_tmp.at(1);
	var.collisionbox.w = v_tmp.at(2);
	var.collisionbox.h = v_tmp.at(3);
	var.immune = m_luaScript->get<bool>(global + ".Immune");
	var.health = m_luaScript->get<int>(global + ".Health");
	var.damage = m_luaScript->get<int>(global + ".Damage");
	
    
}

void GameObjectManager::LoadMovingObjectSpecifics(Variables& var){
    ;
}

void GameObjectManager::LoadStaticObjectSpecifics(Variables& var){
    ;
}

Animation* GameObjectManager::LoadAnimation(const std::string global, const std::string animationName){
    
    	std::vector<int> v_tmp;
	
	Variables var;
	
	var.spritesheet = m_luaScript->get<std::string>(global + ".Animations." + animationName + ".Spritesheet");
	v_tmp = m_luaScript->getIntVector(global + ".Animations." + animationName + ".FramePositions");
	
	for(unsigned int i = 0; i < v_tmp.size() ;i += 2){
	    Point t(v_tmp.at(i), v_tmp.at(i+1));
	    var.framepositions.push_back(t);
	}
	
	v_tmp.clear();
	v_tmp = m_luaScript->getIntVector(global + ".Animations." + animationName + ".FrameSize");
	var.framesize.w = v_tmp.at(0);
	var.framesize.h = v_tmp.at(1);
	
	v_tmp.clear();
	v_tmp = m_luaScript->getIntVector(global + ".Animations." + animationName + ".ScreenSize");
	var.screensize.x = v_tmp.at(0);
	var.screensize.y = v_tmp.at(1);
	var.screensize.w = v_tmp.at(2);
	var.screensize.h = v_tmp.at(3);
	
	var.delay = m_luaScript->get<int>(global + ".Animations." + animationName + ".Delay");
	
	var.doonce = m_luaScript->get<bool>(global + ".Animations." + animationName + ".DoOnce");
	
	return new Animation( var.spritesheet, var.framepositions, var.framesize, var.screensize, var.delay, var.doonce );
}

void GameObjectManager::LoadPlatforms(){
    std::vector<std::string> platforms;
    Variables var;
    platforms = m_luaScript->getTableKeys("Platform");

    for (auto it : platforms)
    {
	std::vector<int> v_tmp;
	
	LoadGameObjectSpecifics(var, "Platform." + it);
	
	// Speciall for platfroms:
	var.damageticks = m_luaScript->get<int>("Platform." + it + ".DamageTicks");
	var.friktion = m_luaScript->get<int>("Platform." + it + ".Friktion");
	var.jumpacceleration = m_luaScript->get<int>("Platform." + it + ".JumpAcceleration");
	
	loadedPlatforms.insert( std::make_pair( it, new Platform(var.size, var.collisionbox, GameObject::PLATFORM, var.spritesheet, 0,
							    var.immune, var.health, var.damage, var.damageticks, var.friktion, var.jumpacceleration) ));
	
	
	loadedPlatforms.find(it)->second->AddAnimation( "DEATH" , LoadAnimation("Platform." + it, "DEATH") );
    }	
    
}

void GameObjectManager::LoadEnemys(){
    std::vector<std::string> enemys;
    Variables var;
    enemys = m_luaScript->getTableKeys("Enemy");

    for (auto it : enemys)
    {
	std::vector<int> v_tmp;
	
	LoadGameObjectSpecifics(var, "Enemy." + it);
	
	// Speciall for enemys:
	//
	//
	
	loadedEnemys.insert( std::make_pair( it, new Enemy(var.size, var.collisionbox, GameObject::ENEMY, var.spritesheet, 0,
							    var.immune, var.health, var.damage) ));
	
	
	loadedEnemys.find(it)->second->AddAnimation( "WALK" , LoadAnimation("Enemy." + it, "WALK") );
	loadedEnemys.find(it)->second->AddAnimation( "DEATH" , LoadAnimation("Enemy." + it, "DEATH") );
    }	
    
}



GameObject* GameObjectManager::GetGameObject(const std::string name){
    return loadedPlatforms.find(name)->second->Clone();
}

GameObject* GameObjectManager::GetEnemy(const std::string name){
    return loadedEnemys.find(name)->second->Clone();
}