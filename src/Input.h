#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

#include "InputDefinition.h"
#include "Rect.h"

class Input
{
  public:
    
    Input();
    ~Input();
    
    static Input* getInstance();
    
    void ResetClicks();
    
    void update(int cameraX = 0, int cameraY = 0);
    
    bool is_key_down(int key);
    bool is_key_up(int key);
    
    bool is_key_pressed(KeyboardKey key);
  
    bool shift();
    bool ctrl();
    bool alt();
    
    bool is_mouse_down(MouseButton button);
    bool is_mouse_up(MouseButton button);
    
    bool is_mouse_pressed(MouseButton button);
    
    int get_mouse_x();
    int get_mouse_y();
    
    bool get_quit();
    
    bool is_mouse_inside(Rect<int> rectangle);

  private:
    
    static Input* instance;
    
    const uint8_t* keyboard;
    
    uint32_t m_mouse;
    
    int m_mouse_x;
    int m_mouse_y;
    
    bool m_key_down[KEYBOARD_SIZE];
    bool m_key_up[KEYBOARD_SIZE];
    bool m_mouse_down[MOUSE_MAX];
    bool m_mouse_up[MOUSE_MAX];
    
    bool m_mouse_pressed[MOUSE_MAX];

    bool m_quit;
};

#endif