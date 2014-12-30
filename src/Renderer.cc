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
	for (std::map<std::string, SDL_Texture*>::iterator it=m_mObjectTextures.begin(); it!=m_mObjectTextures.end(); ++it)
	{
		SDL_DestroyTexture(it->second);
		it->second = nullptr;
	}
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
        mWindow = SDL_CreateWindow("Not speced" , SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 720, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
	
	
	SDL_Surface *surface;     // Declare an SDL_Surface to be filled in with pixel data from an image file
	/*Uint16 pixels[16*16] = {  // ...or with raw pixel data:
	  0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
	  0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
	  0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
	  0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
	  0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
	  0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
	  0x0fff, 0x0aab, 0x0789, 0x0bcc, 0x0eee, 0x09aa, 0x099a, 0x0ddd,
	  0x0fff, 0x0eee, 0x0899, 0x0fff, 0x0fff, 0x1fff, 0x0dde, 0x0dee,
	  0x0fff, 0xabbc, 0xf779, 0x8cdd, 0x3fff, 0x9bbc, 0xaaab, 0x6fff,
	  0x0fff, 0x3fff, 0xbaab, 0x0fff, 0x0fff, 0x6689, 0x6fff, 0x0dee,
	  0xe678, 0xf134, 0x8abb, 0xf235, 0xf678, 0xf013, 0xf568, 0xf001,
	  0xd889, 0x7abc, 0xf001, 0x0fff, 0x0fff, 0x0bcc, 0x9124, 0x5fff,
	  0xf124, 0xf356, 0x3eee, 0x0fff, 0x7bbc, 0xf124, 0x0789, 0x2fff,
	  0xf002, 0xd789, 0xf024, 0x0fff, 0x0fff, 0x0002, 0x0134, 0xd79a,
	  0x1fff, 0xf023, 0xf000, 0xf124, 0xc99a, 0xf024, 0x0567, 0x0fff,
	  0xf002, 0xe678, 0xf013, 0x0fff, 0x0ddd, 0x0fff, 0x0fff, 0xb689,
	  0x8abb, 0x0fff, 0x0fff, 0xf001, 0xf235, 0xf013, 0x0fff, 0xd789,
	  0xf002, 0x9899, 0xf001, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0xe789,
	  0xf023, 0xf000, 0xf001, 0xe456, 0x8bcc, 0xf013, 0xf002, 0xf012,
	  0x1767, 0x5aaa, 0xf013, 0xf001, 0xf000, 0x0fff, 0x7fff, 0xf124,
	  0x0fff, 0x089a, 0x0578, 0x0fff, 0x089a, 0x0013, 0x0245, 0x0eff,
	  0x0223, 0x0dde, 0x0135, 0x0789, 0x0ddd, 0xbbbc, 0xf346, 0x0467,
	  0x0fff, 0x4eee, 0x3ddd, 0x0edd, 0x0dee, 0x0fff, 0x0fff, 0x0dee,
	  0x0def, 0x08ab, 0x0fff, 0x7fff, 0xfabc, 0xf356, 0x0457, 0x0467,
	  0x0fff, 0x0bcd, 0x4bde, 0x9bcc, 0x8dee, 0x8eff, 0x8fff, 0x9fff,
	  0xadee, 0xeccd, 0xf689, 0xc357, 0x2356, 0x0356, 0x0467, 0x0467,
	  0x0fff, 0x0ccd, 0x0bdd, 0x0cdd, 0x0aaa, 0x2234, 0x4135, 0x4346,
	  0x5356, 0x2246, 0x0346, 0x0356, 0x0467, 0x0356, 0x0467, 0x0467,
	  0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
	  0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
	  0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
	  0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff
	};
	surface = SDL_CreateRGBSurfaceFrom(pixels,16,16,16,16*2,0x0f00,0x00f0,0x000f,0xf000); */
      
	surface = IMG_Load( PLAYER_FILEPATH.c_str() );
	// The icon is attached to the window pointer
	SDL_SetWindowIcon(mWindow, surface);

	
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

SDL_Texture* Renderer::getTexture(std::string texturePath)
{
	map<std::string, SDL_Texture*>::iterator it;
	it = m_mObjectTextures.find(texturePath);
	
	if(it != m_mObjectTextures.end())
	{
		return it->second;
	}
	else
	{
		m_mObjectTextures.insert(make_pair(texturePath, loadTexture(texturePath)));
		cout << "Added " << texturePath << " to m_mObjectTextures\n";
		return m_mObjectTextures.find(texturePath)->second;
	}
}

void Renderer::beginScene()
{
	SDL_SetRenderDrawColor(this->mRenderer, 0 ,0 ,0 ,0);
	
    SDL_RenderClear(this->mRenderer);
}

void Renderer::endScene()
{
    SDL_RenderPresent(this->mRenderer);
    //SDL_Delay(1000/(60+FPScalc.getMilliseconds())); // 60 FPS
	SDL_Delay(1000/60);
}

void Renderer::drawTexture(Rect rect, std::string texturePath, bool onMap ,Rect clip, bool flipHorisontal, bool flipVertical, Point centerPoint, double angle)
{
	
  SDL_Rect offset;
  SDL_Rect Clip;
  SDL_Point center = {centerPoint.x, centerPoint.y};
  SDL_RendererFlip SDLflip;
  
  if (onMap)
    offset = {rect.x-camera.x, rect.y-camera.y, rect.w, rect.h};
  else
    offset = {rect.x, rect.y, rect.w, rect.h};
    
    if (flipHorisontal == false && flipVertical == false )
	SDLflip = SDL_FLIP_NONE;
    else if (flipHorisontal == true && flipVertical == false)
	SDLflip = SDL_FLIP_VERTICAL; 
    else if (flipHorisontal == false && flipVertical == true)
	SDLflip = SDL_FLIP_HORIZONTAL;

    if( clip.w != 0 && clip.h != 0 )
    {
	Clip = {clip.x, clip.y, clip.w, clip.h};
	SDL_RenderCopyEx( mRenderer, getTexture(texturePath), &Clip, &offset, angle, &center, SDLflip );
    }
    else{
	SDL_RenderCopyEx( mRenderer, getTexture(texturePath), NULL, &offset, angle, &center, SDLflip );
    }	

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


void Renderer::updateCamera(Rect screenCenter, int levelWidth, int levelHeight)
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
	if( camera.x > levelWidth - camera.w )
		camera.x = levelWidth - camera.w;
	if( camera.y > levelHeight - camera.h )
		camera.y = levelHeight - camera.h;
		
}

Point Renderer::getCameraAdjustment()
{
	return Point(camera.x, camera.y);
}

