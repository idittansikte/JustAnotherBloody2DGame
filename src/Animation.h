#ifndef ANIMATION_H
#define ANIMATION_H

#include <iostream>
#include <vector>
#include <string>

#include "Renderer.h"
#include "Sprite.h"
#include "Point.h"
#include "Rect.h"
#include "Timer.h"



class Animation : public Sprite {
    
    public:
	Animation(std::string filename, std::vector<Point> framePositions, Rect frameSize, Rect screensize, int delay, bool onlyOnce);
	
	~Animation();
	
	void Reset();
	
	void Update();
	
	void DrawCurrentFrame(Renderer* renderer, Rect boxToFill, bool flipHorisontal = false);
	
	void Next();
	
	void Previous();
	
	Animation* Clone(){ return new Animation(*this); }
	
	bool AnimationFinished();
	
    private:
	Animation() = delete;
	
	std::vector<Point> m_framePositions;
	
	Rect m_frameSize;
	Rect m_screenSize;
	
	std::vector<Point>::iterator m_currentFramePos;
	
	int m_framecounter;
	
	const int m_millisecondsDelay;
	
	Timer m_timer;
	
	const bool m_onlyOnce;
	bool m_runnedOnce;
};

#endif