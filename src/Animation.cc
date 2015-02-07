#include "Animation.h"

#include <iostream>

Animation::Animation(std::string filename, std::vector<Point> framePositions, Rect<int> frameSize, Rect<int> screensize, int delay, bool onlyOnce)
	: Sprite(filename), m_framePositions(framePositions), m_frameSize(frameSize), m_screenSize(screensize), m_millisecondsDelay(delay), m_onlyOnce(onlyOnce), m_runnedOnce(false),m_currentFramePos(m_framePositions.begin())
	{
	    m_timer.start();
	    m_framecounter = 0;
	    //Reset(); // Reset iterator
	}
	
Animation::~Animation()
	{}
	
void Animation::Reset(){
    
    //m_currentFramePos = m_framePositions.begin();
    m_framecounter = 0;

}
	
void Animation::Update(){
    if( m_timer.getMillisecondsFromStart() > m_millisecondsDelay ){ // if delay reached
	
	m_timer.reset();
	Next();
    }
}

bool Animation::AnimationFinished(){
    return m_framecounter == m_framePositions.size();
}

void Animation::DrawCurrentFrame( Renderer* renderer, Rect<int> boxToFill, bool flipHorisontal ){
    
    
    
    if( m_framecounter < m_framePositions.size() ){ // This will make sure that animation will only be runned through once if that option is chosen
    
	Rect<int> fill(boxToFill.x + m_screenSize.x, boxToFill.y + m_screenSize.y, m_screenSize.w, m_screenSize.h);
	
	renderer->drawTexture(fill, getFilename(), true , Rect<int>(m_framePositions.at(m_framecounter).x, m_framePositions.at(m_framecounter).y, m_frameSize.w, m_frameSize.h ), flipHorisontal); // x=w & y=h
    }
    
    Update();
}

void Animation::Next(){


    ++m_framecounter;
    
    
    if( AnimationFinished() ){
	if( !m_onlyOnce )
	    Reset();
    }
}
	
void Animation::Previous(){
    
    if( m_currentFramePos != m_framePositions.begin() )
	--m_currentFramePos;
    else
	m_currentFramePos = m_framePositions.end();
}
	
    