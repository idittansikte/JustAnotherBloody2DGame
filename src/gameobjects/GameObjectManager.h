#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H

#include <string>
#include <vector>
#include "../Point.h"
#include "../Rect.h"
#include <map>

class Animation;
class LuaScript;
class Enemy;
class Projectile;
class Platform;
class Player;
class GameObject;

struct Variables{
    std::string spritesheet, projectilename, name = "";
    Rect<int> size, collisionbox, framesize, screensize;
    bool immune, doonce, ranger, gravity, targetplayer;
    int health, damage, damageticks, friktion, jumpacceleration, distance;
    int delay, intervall, aggrodistance;
    float speed;
    std::vector<Point> framepositions;
};

class GameObjectManager{
    public:
	GameObjectManager();
	~GameObjectManager();
	
	enum ListType{PLATFORMLIST, PROJECTILELIST, ENEMYLIST};
	
	void LoadGameObjectSpecifics(Variables& var, const std::string global);
	void LoadMovingObjectSpecifics(Variables& var);
	void LoadStaticObjectSpecifics(Variables& var);
	Animation* LoadAnimation(const std::string global, const std::string animationName);
	
	void loadGameObjectsFromFile();
	
	void LoadPlatforms();
	void LoadEnemys();
	void LoadProjectiles();
	void LoadPlayer();
	

	GameObject* GetGameObject(const std::string name);
	GameObject* GetNewEnemy(const std::string name);
	Projectile* GetNewProjectile(const std::string name);
	Player* GetNewPlayer(const std::string name);
	
	//std::map<std::string, Platform*>* getPlatformList(){ return &loadedPlatforms };
	//std::map<std::string, Enemy*>* getEnemyList(){ return &loadedEnemys };
	//Player* GetPlayer(){ return &loadedPlayer; }
	
	std::map<std::string, GameObject*>* GetLoadedList(ListType listtype);
	
	std::vector< std::map<std::string, GameObject*>* > GetAllLoaded();
	
	static GameObjectManager* Instance()
	{
	  return &m_GameObjectManager;
	}

    private:
	static GameObjectManager m_GameObjectManager;
	
	std::map<std::string, GameObject*> loadedPlatforms;
	std::map<std::string, GameObject*> loadedEnemys;
	std::map<std::string, Projectile*> loadedProjectiles;
	
	Player* loadedPlayer;
	LuaScript* m_luaScript;
};

#endif