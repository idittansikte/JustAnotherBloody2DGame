#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H

#include <string>
#include <vector>
#include "../Point.h"
#include "../Rect.h"
#include <map>

//#include "../lua/LuaScript.h"
//#include "../Animation.h"

#include "Enemy.h"
#include "Platform.h"
#include "../lua/LuaScript.h"
class Animation;

struct Variables{
    std::string spritesheet = "";
    Rect size, collisionbox, framesize, screensize;
    bool immune, doonce;
    int health, damage, damageticks, friktion, jumpacceleration;
    int delay;
    std::vector<Point> framepositions;
};

class GameObjectManager{
    public:
	GameObjectManager(const std::string& filename);
	~GameObjectManager();
	
	void LoadGameObjectSpecifics(Variables& var, const std::string global);
	void LoadMovingObjectSpecifics(Variables& var);
	void LoadStaticObjectSpecifics(Variables& var);
	Animation* LoadAnimation(const std::string global, const std::string animationName);
	
	void loadGameObjectsFromFile();
	
	void LoadPlatforms();
	void LoadEnemys();
	
	GameObject* GetGameObject(const std::string name);
	GameObject* GetEnemy(const std::string name);
    private:
	std::map<std::string, Platform*> loadedPlatforms;
	std::map<std::string, Enemy*> loadedEnemys;
	LuaScript* m_luaScript;
};

#endif