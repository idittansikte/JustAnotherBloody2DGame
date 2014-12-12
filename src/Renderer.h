#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <map>

#include "Rect.h"
#include "Constants.h"

class Renderer
{
  public:
    enum ObjectType {PLAYER, GRASS_PLATFORM_TOPLEFT, GRASS_PLATFORM_TOPRIGHT, GRASS_PLATFORM_BOTTOMRIGHT, GRASS_PLATFORM_BOTTOMLEFT, ENEMY, BACKGROUND, MENU_BACKGROUND};
    
    Renderer();
    ~Renderer();
    
    void Clean();
    bool Init();
    
    void InitTextures();
    
    void beginScene();
    void endScene();
    
    void drawTexture(Rect rect, ObjectType oType, bool onMap = false , Rect clip = Rect(), bool flip = false);
    
    SDL_Texture* loadTexture(std::string filename);
    SDL_Texture* loadTexture(std::string text, unsigned int color1, unsigned int color2, unsigned int color3);
    
    void updateCamera(Rect screenCenter, int, int);
    Rect getCameraAdjustment();
    
  private:
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    TTF_Font * mFont;
    SDL_Rect camera;
    std::map<ObjectType, SDL_Texture*> m_mObjectTextures;
  
};

#endif;