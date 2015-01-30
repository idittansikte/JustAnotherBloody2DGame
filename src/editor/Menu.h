#ifndef MENU_H
#define MENU_H

#include "../Renderer.h"
#include "../Rect.h"
#include "../Input"
#include "../gameobjects/GameObject.h" // Needed for specialization
#include "../EditorState.h" // Needed for specialization

#include <vector>
#include <utility> //Pair

template<typename T>
class Menu
{
    public:
	
    Menu( float x, float y, float w, float h );
    
    Init( std::vector< std::pair<Rect, T> > buttons );
    
    Update( Rect windowSize ); // Dynamically update everything after window resizes
    
    Draw( Renderer* renderer );
    
    T GetButtonItemOnMouse();
    T GetDefualt();
    
    private:
    Rect m_prev_winSize; // Save previous windowsize to skip unnessessary updates
    const Rect m_virtual_position; // Percentage of screen
    Rect m_physic_position; 
    
    std::vector< std::pair<Rect, T > m_buttons; // All buttons inside of menu box...
};

// Template function declarations
template<typename T>
inline T Menu::GetButtonItemOnMouse<T>(){
    ;
}

template<typename T>
inline T GetDefualt<T>(){
    ;
}

// Specializations
template<>
inline EditorState::ButtonType GetDefualt<EditorState::ButtonType>(){
    ;
}

template<>
inline GameObject* GetDefualt<GameObject*>(){
    ;
}