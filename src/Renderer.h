#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <map>

#include "Rect.h"
#include "Point.h"
#include "Constants.h"

class Renderer
{
  public:
    
    Renderer();
    ~Renderer();
    
    void Clean();
    bool Init();
    
    SDL_Texture* getTexture(std::string texturePath);
    
    void beginScene();
    void endScene();
    
    void drawTexture(Rect rect, std::string texturePath, bool onMap = false , Rect clip = Rect(),
                     bool flipHorisontal = false, bool flipVertical= false, Point centerPoint = Point(), double angle = 0);
    
    SDL_Texture* loadTexture(std::string filename);
    SDL_Texture* loadTexture(std::string text, unsigned int color1, unsigned int color2, unsigned int color3);
    
    void updateCamera(Rect screenCenter, int, int);
    Point getCameraAdjustment();
    
    Rect getWindowSize();
    
    void DisableCursor(bool disable);
    
  private:
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    TTF_Font * mFont;
    SDL_Rect camera;
    std::map<std::string, SDL_Texture*> m_mObjectTextures;
  
};

#endif