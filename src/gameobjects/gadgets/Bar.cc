#include "Bar.h"


void Bar::showHealthBar(Renderer* renderer, Rect barRect, int max, int current){
    
    float greenPercentage = ((float)current / (float)max) * barRect.w;
    
    renderer->drawTexture( barRect, HEALTHBAR_RED_FILEPATH, true);
    renderer->drawTexture( Rect(barRect.x, barRect.y, greenPercentage, barRect.h), HEALTHBAR_GREEN_FILEPATH, true);

}