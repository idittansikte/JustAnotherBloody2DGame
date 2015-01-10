#include "Bar.h"

#include "../GameObject.h"

//#include "../../Constants.h"

void Bar::setBarBox(Rect barbox){
    
    m_barBox = barbox;
}

void Bar::showBar(float uptime){
    m_timer.start();
    m_uptime=uptime;
}

void Bar::drawHealthBar(Renderer* renderer, GameObject* lhs){
    
    if(lhs->getImmune())
	return;
    
    
    Rect r = lhs->getRect();
    
    if(m_timer.getSecondsFromStart() < m_uptime){
    
    float greenPercentage = ((float)lhs->getCurrentHealth() / (float)lhs->getMaxHealth()) * m_barBox.w;
    
    renderer->drawTexture( Rect(r.x + m_barBox.x, r.y + m_barBox.y, m_barBox.w, m_barBox.h), HEALTHBAR_RED_FILEPATH, true);
    renderer->drawTexture( Rect(r.x + m_barBox.x, r.y + m_barBox.y, greenPercentage, m_barBox.h), HEALTHBAR_GREEN_FILEPATH, true);

    }
}