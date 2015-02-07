#ifndef BAR_H
#define BAR_H

#include "../../Rect.h"
#include "../../Timer.h"

class Renderer;
class GameObject;

class Bar{
    public:

	Bar() = default;
	~Bar() = default;
	
	void setBarBox(Rect<int> barbox);
	
	void showBar(float uptime);
	
	void drawHealthBar(Renderer* renderer, GameObject* go);
	
	Bar* Clone(){ return new Bar(*this); }
    private:
	float m_uptime{};
	Timer m_timer;
	Rect<int> m_barBox;
};

#endif