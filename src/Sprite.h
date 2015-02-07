#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>
#include <string>

#include "Renderer.h"
#include "Rect.h"
#include "Point.h"

class Sprite{
    public:
	Sprite(std::string filename );
        
	~Sprite();
	
	std::string getFilename();
	
	void DrawSprite(Renderer* renderer, Rect<int> boxToFill);
	
	
    private:
	
        std::string m_filename;
    
      // Size that we want on screen
      //Rect m_screenSize;
};

#endif