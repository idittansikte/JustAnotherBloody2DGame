#include "Renderer.h"
#include <iostream>

using namespace std;
Renderer::Renderer()
{
    mRenderer = nullptr;
    mWindow = nullptr;
}

Renderer::~Renderer()
{
  // cleanup SDL
  Clean();
}

void Renderer::Clean()
{
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
	TTF_CloseFont(mFont);
    mWindow = NULL;
    mRenderer = NULL;
	TTF_Quit();
    SDL_Quit();
}

bool Renderer::Init()
{
    bool success = true;

    if(SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() < 0)
    {
	cerr << "ERROR: Kunde inte initiera SDL\n";
        success = false;
    }
    else
    {

	 // create window
        mWindow = SDL_CreateWindow("Not speced" , SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 720, 480, SDL_WINDOW_SHOWN/*|SDL_WINDOW_RESIZABLE*/);
        if(mWindow == NULL)
        {
            cerr << "ERROR: Kunde inte skapa fönster\n";
            success = false;;
        }else
        {
            mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED );
            if(mRenderer == NULL)
            {
                cerr << "ERROR: Kunde inte skapa renderer\n" << SDL_GetError();
				success = false;
            }else
            {
                // initialize renderer color
                SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                
				// initialize SDL_mixer
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) 
				{ 
					cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl; 
					success = false; 
				}
				
				/*mFont = TTF_OpenFont(".." , 40);
				if(mFont == NULL)
				{
					cerr << "ERROR: Kunde inte skapa mFont\n" << TTF_GetError();
					success = false;
				}*/
			
                // initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
    }
    if(success)
      printf("Succeeded to initialize renderer\n");
    else
      printf("Failed to initialize renderer\n");
      return success;
    
}

void Renderer::InitTextures()
{
	m_mObjectTextures.insert( std::pair<ObjectType, SDL_Texture*>( PLAYER, loadTexture(PLAYER_FILEPATH) ) );
	m_mObjectTextures.insert( std::pair<ObjectType, SDL_Texture*>( MENU_BACKGROUND, loadTexture(MENU_BACKGROUND_FILEPATH) ) );
}

void Renderer::beginScene()
{
    SDL_RenderClear(mRenderer);
}

void Renderer::endScene()
{
    SDL_RenderPresent(mRenderer);
    //SDL_Delay(1000/(60+FPScalc.getMilliseconds())); // 60 FPS
	SDL_Delay(1000/60);
}

void Renderer::drawTexture(Rect rect, ObjectType oType, bool onMap ,Rect clip, bool flip)
{
  SDL_Rect offset;
  SDL_Rect Clip;
  SDL_RendererFlip SDLflip;
  if (onMap)
    offset = {rect.x-camera.x, rect.y-camera.y, rect.w, rect.h};
  else
    offset = {rect.x, rect.y, rect.w, rect.h};
    
  if (flip == false)
    SDLflip = SDL_FLIP_NONE;
  else
     SDLflip = SDL_FLIP_HORIZONTAL; 

  if( clip.w != 0 && clip.w != 0 )
  {
    Clip = {clip.x, clip.y, clip.w, clip.h};
	SDL_RenderCopyEx( mRenderer, m_mObjectTextures.find(oType)->second, &Clip, &offset, 0, NULL, SDLflip );
  }
  else
    SDL_RenderCopyEx( mRenderer, m_mObjectTextures.find(oType)->second, NULL, &offset, 0, NULL, SDLflip );
}


SDL_Texture* Renderer::loadTexture(std::string filename)
{
    //The final texture
    SDL_Texture* newTexture = NULL;
    
    SDL_Surface* tmpSurface = IMG_Load(filename.c_str() );
    if(tmpSurface == NULL)
    {
        cerr << "ERROR: Kunde inte öppna fil: " << filename << IMG_GetError() << endl;
    }else
    {
        //Convertera surface till screen format
        newTexture = SDL_CreateTextureFromSurface(mRenderer, tmpSurface);
        if(newTexture == NULL)
        {
            cerr << "ERROR: Misslyckades konvertera fil: " << filename << SDL_GetError() << endl;
        }
        SDL_FreeSurface(tmpSurface);
    }

    return newTexture;
}

SDL_Texture* Renderer::loadTexture(string text, unsigned int color1, unsigned int color2, unsigned int color3)
{
   
	SDL_Texture* newTexture = NULL;
    SDL_Color color = { (unsigned char)color1, (unsigned char)color2, (unsigned char)color3 };
    
    SDL_Surface* tmpSurface = TTF_RenderText_Solid(mFont, text.c_str(), color);
    if(tmpSurface == NULL)
    {
        cerr << "ERROR: Kunde inte ladda text: " << text << endl;
    }else
    {
        //Convertera surface till screen format
        newTexture = SDL_CreateTextureFromSurface(mRenderer, tmpSurface);
        if(newTexture == NULL)
        {
            cerr << "ERROR: Misslyckades konvertera text: " << text << SDL_GetError() << endl;
        }
        SDL_FreeSurface(tmpSurface);
    }

    return newTexture;
}


void Renderer::updateCamera(Rect screenCenter, int LEVEL_WIDTH, int LEVEL_HEIGHT)
{
	//Center the camera over the player
	camera.x = ( screenCenter.x + screenCenter.w / 2 ) - SCREEN_WIDTH / 2;
	camera.y = ( screenCenter.y + screenCenter.h / 2 ) - SCREEN_HEIGHT / 2;
	//std::cout << "camera.x: " << camera.x << " camera.y: " << camera.y << std::endl; 
	//Keep the camera in bounds
	if( camera.x < 0 )
		camera.x = 0;
	if( camera.y < 0 )
		camera.y = 0;
	if( camera.x > LEVEL_WIDTH - camera.w )
		camera.x = LEVEL_WIDTH - camera.w;
	if( camera.y > LEVEL_HEIGHT - camera.h )
		camera.y = LEVEL_HEIGHT - camera.h;
		
}

Rect Renderer::getCameraAdjustment()
{
	return Rect(camera.x, camera.y);
}
