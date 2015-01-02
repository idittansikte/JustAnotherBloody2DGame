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
	
	void DrawSprite(Renderer* renderer, Rect boxToFill);
	
	
    private:
	
    std::string m_filename;
};

#endif