#include "GameObjectManager.h"

#include <fstream>
#include <iostream>
#include <string>
#include <utility>


#include "../lua/LuaScript.h"

#include "Enemy.h"
#include "Projectile.h"
#include "Platform.h"
#include "Player.h"
#include "../Animation.h"

GameObjectManager GameObjectManager::m_GameObjectManager;

GameObjectManager::GameObjectManager()
{
    m_luaScript = new LuaScript(LUA_FILEPATH);
    loadGameObjectsFromFile();
}

GameObjectManager::~GameObjectManager()
{
	for(auto it : loadedPlatforms){
	    delete it.second;
	    it.second = nullptr;
	}
	for(auto it : loadedEnemys){
	    delete it.second;
	    it.second = nullptr;
	}
	for(auto it : loadedProjectiles){
	    delete it.second;
	    it.second = nullptr;
	}
	loadedPlayer = nullptr;
}


void GameObjectManager::loadGameObjectsFromFile(){
    
    LoadProjectiles();
    LoadPlayer();
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
	if(var.immune){
	    var.health = 0;
	}else{
	    var.health = m_luaScript->get<int>(global + ".Health");
	}
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
	LoadGameObjectSpecifics(var, "Platform." + it);
	
	// Speciall for platfroms:
	var.damageticks = m_luaScript->get<int>("Platform." + it + ".DamageTicks");
	var.friktion = m_luaScript->get<int>("Platform." + it + ".Friktion");
	var.jumpacceleration = m_luaScript->get<int>("Platform." + it + ".JumpAcceleration");
	var.name = it;
	Platform* newplatform = new Platform(var.size, var.collisionbox, var.spritesheet, 0,
					    var.immune, var.health, var.damage, var.damageticks, var.friktion, var.jumpacceleration);
	newplatform->SetName(var.name);
	loadedPlatforms.insert( std::make_pair( it, newplatform ));
	
	
	
	loadedPlatforms.find(it)->second->AddAnimation( "DEATH" , LoadAnimation("Platform." + it, "DEATH") );
    }	
    
}

void GameObjectManager::LoadEnemys(){
    std::vector<std::string> enemys;
    Variables var;
    enemys = m_luaScript->getTableKeys("Enemy");

    for (auto it : enemys)
    {	
	LoadGameObjectSpecifics(var, "Enemy." + it);
	
	// Speciall for enemys:
	var.ranger = m_luaScript->get<bool>("Enemy." + it + ".Ranger");
	var.projectilename = m_luaScript->get<std::string>("Enemy." + it + ".Projectile");
	var.intervall = m_luaScript->get<int>("Enemy." + it + ".Intervall");
	
	var.targetplayer = m_luaScript->get<bool>("Enemy." + it + ".TargetPlayer");
	var.aggrodistance = m_luaScript->get<int>("Enemy." + it + ".AggroDistance");
	
	var.gravity = m_luaScript->get<bool>("Enemy." + it + ".ApplyGravitation");
	//
	var.name = it;
	Enemy* ne = new Enemy(var.size, var.collisionbox, var.spritesheet, 0, var.immune, var.health, var.damage, var.aggrodistance);
	
	ne->SetName(var.name);
	    
	if(var.ranger)
	    ne->setProjectile(GetNewProjectile(var.projectilename), var.intervall);
	
	loadedEnemys.insert( std::make_pair( it, ne ));
	
	
	loadedEnemys.find(it)->second->AddAnimation( "WALK" , LoadAnimation("Enemy." + it, "WALK") );
	loadedEnemys.find(it)->second->AddAnimation( "DEATH" , LoadAnimation("Enemy." + it, "DEATH") );
    }	
    
}

void GameObjectManager::LoadProjectiles(){

    std::vector<std::string> projectiles;
    Variables var;
    projectiles = m_luaScript->getTableKeys("Projectile");
    
    for (auto it : projectiles)
    {	
	//LoadGameObjectSpecifics(var, "Projectile." + it);
	
	std::string global = "Projectile." + it;
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
	
	// Speciall for enemys:
	var.distance = m_luaScript->get<int>("Projectile." + it + ".Distance");
	var.speed = m_luaScript->get<float>("Projectile." + it + ".Speed");
	
	loadedProjectiles.insert( std::make_pair( it, new Projectile(var.size, var.collisionbox, var.spritesheet, 0, var.distance,
							   var.immune, var.health, var.speed) ));
	
	// Load Animations
	loadedProjectiles.find(it)->second->AddAnimation( "INAIR" , LoadAnimation("Projectile." + it, "INAIR") );
	loadedProjectiles.find(it)->second->AddAnimation( "DEATH" , LoadAnimation("Projectile." + it, "DEATH") );
    }	

}

void GameObjectManager::LoadPlayer(){
    
    std::vector<std::string> players;
    Variables var;
    
    players = m_luaScript->getTableKeys("Player");
    
    for (auto it : players)
    {	
	LoadGameObjectSpecifics(var, "Player." + it);
	
	// Speciall for player:
	var.projectilename = m_luaScript->get<std::string>("Player." + it + ".Projectile");
	
	loadedPlayer = new Player(var.size, var.collisionbox, var.spritesheet, 0, var.immune, var.health, var.damage, GetNewProjectile(var.projectilename)) ;
	loadedPlayer->SetName(it);
	loadedEnemys.insert( std::make_pair( it, loadedPlayer ));
	// Load Animations
	loadedPlayer->AddAnimation( "WALK" , LoadAnimation("Player." + it, "WALK") );
	loadedPlayer->AddAnimation( "DEATH" , LoadAnimation("Player." + it, "DEATH") );
    }
}

GameObject* GameObjectManager::GetGameObject(const std::string name){
    GameObject* founedObject = nullptr;
    std::vector< std::map<std::string, GameObject*>*> v = GetAllLoaded();
    for(auto list : v){
	std::map<std::string, GameObject*>::iterator it = list->find(name);
	if(it != list->end()){
	    founedObject = it->second->Clone();
	    break;
	}
    }
    return founedObject;
}

GameObject* GameObjectManager::GetNewEnemy(const std::string name){
    return loadedEnemys.find(name)->second->Clone();
}

Projectile* GameObjectManager::GetNewProjectile(const std::string name){
    return loadedProjectiles.find(name)->second->Clone();
}

Player* GameObjectManager::GetNewPlayer(const std::string name){
    return loadedPlayer;
}

std::map<std::string, GameObject*>* GameObjectManager::GetLoadedList(ListType listtype){
    if(listtype == PLATFORMLIST){
	return &loadedPlatforms;
    }
    else if(listtype == ENEMYLIST){
	return &loadedEnemys;
    }
    else if(listtype == PROJECTILELIST){
	std::cout << "GetLoadedList::Projectile is not implmented yet" << std::endl;
	return nullptr;//&loadedProjectiles;
    }

    return nullptr;
}

std::vector< std::map<std::string, GameObject*>*> GameObjectManager::GetAllLoaded(){
    std::vector< std::map<std::string, GameObject*>*> v;
    v.push_back(&loadedPlatforms);
    v.push_back(&loadedEnemys);
    return v;
}
