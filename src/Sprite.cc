#include "Sprite.h"



Sprite::Sprite(std::string filename )
    : m_filename(filename)
{
}

Sprite::~Sprite(){
    
}

std::string Sprite::getFilename(){
    return m_filename;
}

void Sprite::DrawSprite(Renderer* renderer, Rect boxToFill){
    
    renderer->drawTexture( boxToFill, m_filename, true);
    
}



