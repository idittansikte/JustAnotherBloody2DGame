#ifndef MOVINGGAMEOBJECT_H
#define MOVINGGAMEOBJECT_H

#include <string>

#include "GameObject.h"
#include "../Rect.h"
#include "../Constants.h"

class Renderer;

enum Direction{LEFT, RIGHT};

class MovingGameObject : public GameObject
{
public:

	void Init(Point startpos, int uniquetag);
	virtual void Reset();

	bool collidedFromLeft(GameObject* otherObject);
	bool collidedFromRight(GameObject* otherObject);
	bool collidedFromTop(GameObject* otherObject);
	bool collidedFromBottom(GameObject* otherObject);
	virtual void HandleCollision(GameObject* otherObject);

	void PhysicHandler();
	void turnOn_falling();
	void turnOff_falling();

	void CleanupFrame();
	void Update();

	void Draw(Renderer* renderer);

	virtual ObjectType getType() = 0;

	void apply_velocity_x(float x);
	void apply_velocity_y(float y);

protected:
	MovingGameObject( Rect<int> r, Rect<int> c, std::string texturePath, int uniqueID, bool immune, int health, int damage)
	: GameObject(r, c, texturePath, uniqueID, immune, health, damage), vx(0), vy(0), ax(1.0), ay(0.5)
	{}

	virtual GameObject* Clone() = 0;

	//For collision detection
	bool contactTop{false};
	bool contactBottom{false};
	bool contactLeft{false};
	bool contactRight{false};
	float m_current_fallspeed;

	float vx;
	float vy;
	float ax; // acceleration X
	float ay; // acceleration Y
	const float vy_max{15};
	const float ax_normal{0.5};
	
	Direction m_current_direction{RIGHT};
	
	float m_ground_friktion{};
	int m_ground_jumpacceleration{};
	
	void SetDirection(Direction dir);
	void ChangeDirection();
	Direction GetDirection();
	
	Point GetStartPos(){ return m_start_position; }
	
private:
	
	Point m_start_position;
	Point m_previous_position; //
  	Point m_velocity;

  	bool m_falling;
  
  

};

#endif