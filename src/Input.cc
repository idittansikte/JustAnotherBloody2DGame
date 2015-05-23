#include "Input.h"

#include <iostream>

Input* Input::instance = nullptr;

Input::Input():
    keyboard(nullptr),
    m_mouse(0),
    m_mouse_x(0),
    m_mouse_y(0),
    m_quit(0)
{
  ResetClicks();
  for ( int i = 0; i < MOUSE_MAX; ++i )
  {
    this->m_mouse_pressed[i] = false;
  }
  printf("Input instance created successful\n");
}

Input::~Input()
{}

Input* Input::getInstance()
{
  if (!instance)
    instance = new Input();

  return instance;
}

void Input::ResetClicks(){
  int i;
  // for ( i = 0; i < KEYBOARD_SIZE; ++i )
  // {
  //   this->m_key_down[i] = false;
  //   this->m_key_up[i] = false;
  // }
  for ( i = 0; i < MOUSE_MAX; ++i )
  {
    this->m_mouse_down[i] = false;
    this->m_mouse_up[i] = false;
  }
}
void Input::update(int cameraX, int cameraY)
{
  ResetClicks();
  
  SDL_Event event;
  while( SDL_PollEvent(&event) )
  {
    switch(event.type)
    {
      case SDL_QUIT:
        this->m_quit = true;
        break;
      
      case SDL_TEXTINPUT:
        // ??
        break;
      
      case SDL_KEYDOWN:
        {
          this->keyboard = SDL_GetKeyboardState(nullptr);
          
          int index = event.key.keysym.scancode;
          if( this->m_key_up[index] && !this->m_key_down[index]){
	    this->m_key_down[index] = true;
	    this->m_key_up[index] = false;
	  }
	}
        break;
        
      case SDL_KEYUP:
        {
          this->keyboard = SDL_GetKeyboardState(nullptr);
          
          int index = event.key.keysym.scancode;
          
	  if( this->m_key_down[index] && !this->m_key_up[index] ){
	    this->m_key_up[index] = true;
	    this->m_key_down[index] = false;
	  }
	}
        break;
      
      case SDL_MOUSEMOTION:
        {
          this->m_mouse_x = event.motion.x + cameraX;
          this->m_mouse_y = event.motion.y + cameraY;
        }
        break;
      
      case SDL_MOUSEBUTTONDOWN:
        {
          this->m_mouse = SDL_GetMouseState(&(this->m_mouse_x), &(this->m_mouse_y));
          
          if (event.button.button == SDL_BUTTON_LEFT){
            m_mouse_down[MOUSE_LEFT] = true;
            m_mouse_pressed[MOUSE_LEFT] = true;
          }
          else if (event.button.button == SDL_BUTTON_RIGHT){
            m_mouse_down[MOUSE_RIGHT] = true;
            m_mouse_pressed[MOUSE_RIGHT] = true;
          }
          else if( event.button.button == SDL_BUTTON_MIDDLE ){
            m_mouse_pressed[MOUSE_WHEEL] = true;
          }
        }
        break;
      case SDL_MOUSEBUTTONUP:
        {
          if( event.button.button == SDL_BUTTON_LEFT ){
              m_mouse_pressed[MOUSE_LEFT] = false;
          }
          else if( event.button.button == SDL_BUTTON_LEFT ){
              m_mouse_pressed[MOUSE_RIGHT] = false;
          }
          else if(event.button.button == SDL_BUTTON_MIDDLE){
              m_mouse_pressed[MOUSE_WHEEL] = false;
          }
        }
        break;
      case SDL_MOUSEWHEEL:
        {
          //if( event.button.button == SDL_BUTTON_MIDDLE)
          //  m_mouse_pressed[MOUSE_WHEEL] == true;
          // NO USE YET  
        }
        break;
      default:
        break;
    }
  }
}


bool Input::is_key_up(int key)
{
  if( key < 0 || key > KEYBOARD_SIZE )
    return false;
  
  return ( this->m_key_up[key] );
}

bool Input::is_key_down(int key)
{
    if( key < 0 || key > KEYBOARD_SIZE )
    return false;
  
  return ( this->m_key_down[key] );
}

bool Input::is_key_pressed(KeyboardKey key)
{
  if (!(this->keyboard))
    return false;
  
  int sdl_key = static_cast<int>(key);
  
  if (this->keyboard[sdl_key])
    return true;
  
  return false;
}

bool Input::shift()
{
  return ( instance->is_key_pressed(KEY_LEFT_SHIFT) || instance->is_key_pressed(KEY_RIGHT_SHIFT) );
}

bool Input::ctrl()
{
  return ( instance->is_key_pressed(KEY_LEFT_CTRL) || instance->is_key_pressed(KEY_RIGHT_CTRL) );
}

bool Input::alt()
{
  return ( instance->is_key_pressed(KEY_LEFT_ALT) || instance->is_key_pressed(KEY_RIGHT_ALT) );
}

bool Input::is_mouse_down(MouseButton button)
{
  if (button == MOUSE_MAX)
    return false;

  return ( this->m_mouse_down[button] );
}

bool Input::is_mouse_up(MouseButton button)
{
  if (button == MOUSE_MAX)
    return false;

  return ( this->m_mouse_up[button] );
}

bool Input::is_mouse_pressed(MouseButton button)
{
  switch (button)
  {
    case MOUSE_LEFT:
      if (m_mouse_pressed[MOUSE_LEFT]){
       return true;
      }
    break;
    case MOUSE_RIGHT:
      if (m_mouse_pressed[MOUSE_RIGHT]){
       return true;
      }
    break;
    case MOUSE_WHEEL:
      if (m_mouse_pressed[MOUSE_WHEEL]){
       return true;
      }
    break;
  
    default:
    break;
  }
  return false;
}

int Input::get_mouse_x()
{
  return this->m_mouse_x;
}

int Input::get_mouse_y()
{
  return this->m_mouse_y;
}

bool Input::get_quit()
{
  return this->m_quit;
}

bool Input::is_mouse_inside(Rect<int> rectangle)
{
  if ( (this->m_mouse_x >= rectangle.x)
      && (this->m_mouse_x <= rectangle.x + rectangle.w)
      && (this->m_mouse_y >= rectangle.y)
      && (this->m_mouse_y <= rectangle.y + rectangle.h) )
    return true;
  
  return false;
}




