#ifndef BAR_H
#define BAR_H

#include "../../Rect.h"
#include "../../Renderer.h"
class Bar{
    
    public:
	
	void showHealthBar(Renderer* renderer, Rect barRect, int max, int current);
	
    private:
    
};

#endif