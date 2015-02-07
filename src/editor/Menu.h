#ifndef MENU_H
#define MENU_H

#include "../Renderer.h"
#include "../Rect.h"
#include "../Input.h"
#include "../gameobjects/GameObject.h" // Needed for specialization
//#include "../EditorState.h" // Needed for specialization
#include "../Constants.h"
#include <vector>
#include <utility> //Pair
#include <string>

template<class T>
struct Button{
    std::string b_image;
    Rect<int> 	b_box;
    T 		b_object; // The returned object when clicked on
};


template<class T>
class Menu{
public:
	
    Menu( float x, float y, float w, float h ) // Where on screen due to percetage of screen
    {
	m_virtual_position.x = x;
	m_virtual_position.y = y;
	m_virtual_position.w = w;
	m_virtual_position.h = h;
    }
    
    void Insert( T object, std::string image );
    
    void Update( Rect<int> windowSize ); // Dynamically update everything after window resizes
    
    int GetButtonSize(int width, int height, int tileCount);
    
    void Draw( Renderer* renderer );
    
    T GetButtonItemOnMouse();
    T GetDefualt();
    
private:
    Rect<int> m_prev_winSize; // Save previous windowsize to skip unnessessary updates
    Rect<float> m_virtual_position; // Percentage of screen
    Rect<int> m_physic_position; // The actually positions, dependes on screen size. Dont need to be global ???
    
    std::vector< Button<T> > m_buttons; // All buttons inside of menu box...
};

// Template function declarations
template<class T>
inline void Menu<T>::Insert( T object, std::string image ){ //std::vector< std::pair<Rect<int>, T> > buttons
    Button<T> button;
    button.b_image = image;
    button.b_box = Rect<int>();
    button.b_object = object;
    m_buttons.push_back(button);
}

template<class T>
inline void Menu<T>::Draw( Renderer* renderer ){
    for( unsigned int i = 0; i < m_buttons.size(); ++i){
	
	renderer->drawTexture(m_buttons[i].b_box, E_MENU_BUTTONFRAME_FILEPATH, false);
	renderer->drawTexture(m_buttons[i].b_box*0.80, m_buttons[i].b_image, false);
	//if( m_selected_list != NONE ){
	//    if(m_selected_list == it.second)
	//	renderer->drawTexture(it.first, "imgs/editor/marked_frame.png", false);
	//}
    }
}

template<class T>
inline void Menu<T>::Update( Rect<int> windowSize ){ // Dynamically update everything after window resizes
    
    if( m_prev_winSize == windowSize){
	return;
    }
    
    m_physic_position.x = m_virtual_position.x*windowSize.w; // Example: 0,80*1000 = 800
    m_physic_position.y = m_virtual_position.y*windowSize.h;
    m_physic_position.w = m_virtual_position.w*windowSize.w;
    m_physic_position.h = m_virtual_position.h*windowSize.h;
    
    int space = 0.01 * ((m_physic_position.w + m_physic_position.h)/2); // 5% of width and height between each button
    int totalspace = m_buttons.size()*space;
    
    // Calculate how many columns and rows we will need to fill the menu box
    int columns = 4;
    int rows = m_buttons.size()/columns + 1 ;
    
    // Get the maximum possible buttonsize to fill the entire box
    // int buttonsize = GetButtonSize( (m_physic_position.w - totalspace), (m_physic_position.h - totalspace), m_buttons.size() );
    int buttonwidth = (m_physic_position.w/columns - space*5 );
    int buttonheight = buttonwidth;

    // Loop to update and save grid of clickable gameobjects
    for ( unsigned int row = 0; row < rows; ++row ){
	for ( unsigned int column = 0; column < columns; ++column ){
	    int k = (row*columns + column);
	    // Check if we are out of objects in list
	    if( k > m_buttons.size()-1)
		break;
	    // Make box for the current objectbox.
	    Rect<int> confBox;
	    std::cout << k << '\n';
	    m_buttons[k].b_box.x = ( m_physic_position.x + space*column + buttonwidth*column );
	    m_buttons[k].b_box.y = (m_physic_position.y + (space+buttonwidth)*row );
	    m_buttons[k].b_box.w = buttonwidth;
	    m_buttons[k].b_box.h = buttonheight;
	    // To check against mouseclicks we save all the boxes with its gameobject
	    //m_buttons[k].b_box = confBox;
	}
    }
    m_prev_winSize = windowSize;
}

template<class T>
int Menu<T>::GetButtonSize(int width, int height, int tileCount)
{
    // quick bailout for invalid input
    if (width*height < tileCount) { return 0; }

    // come up with an initial guess
    double aspect = (double)height/width;
    double xf = sqrtf(tileCount/aspect);
    double yf = xf*aspect;
    int x = std::max(1.0, floor(xf));
    int y = std::max(1.0, floor(yf));
    int x_size = floor((double)width/x);
    int y_size = floor((double)height/y);
    int tileSize = std::min(x_size, y_size);

    // test our guess:
    x = floor((double)width/tileSize);
    y = floor((double)height/tileSize);
    if (x*y < tileCount) // we guessed too high
    {
        if (((x+1)*y < tileCount) && (x*(y+1) < tileCount))
        {
            // case 2: the upper bound is correct
            //         compute the tileSize that will
            //         result in (x+1)*(y+1) tiles
            x_size = floor((double)width/(x+1));
            y_size = floor((double)height/(y+1));
            tileSize = std::min(x_size, y_size);
        }
        else
        {
            // case 3: solve an equation to determine
            //         the final x and y dimensions
            //         and then compute the tileSize
            //         that results in those dimensions
            int test_x = ceil((double)tileCount/y);
            int test_y = ceil((double)tileCount/x);
            x_size = std::min(floor((double)width/test_x), floor((double)height/y));
            y_size = std::min(floor((double)width/x), floor((double)height/test_y));
            tileSize = std::max(x_size, y_size);
        }
    }

    return tileSize;
} // GetButtonSize() END

template<class T>
inline T Menu<T>::GetButtonItemOnMouse(){
    T found = GetDefualt();

    for(auto it : m_buttons){
	if(Input::getInstance()->is_mouse_inside(it.b_box)){
	    found = it.b_object;
	    break;
	}
    }

    return found;
}

template<class T>
inline T Menu<T>::GetDefualt(){
    return 0;
}

// Specializations
template<>
inline int Menu<int>::GetDefualt(){
    return 0;
}

template<>
inline GameObject* Menu<GameObject*>::GetDefualt(){
    return nullptr;
}


//    // Render box-background with its gameobject
//    for( auto it : m_ListBoxes){
//	renderer->drawTexture(it.first, E_MENU_BUTTONFRAME_FILEPATH, false);
//	renderer->drawTexture(Rect<int>(it.first.x+it.first.w*0.20, it.first.y+it.first.h*0.20, it.first.w*0.60, it.first.h*0.60), it.second->getTexturePath(), false);
//	if(m_selected_listobject != nullptr)
//	    if(it.second == m_selected_listobject)
//		renderer->drawTexture(it.first, "imgs/editor/marked_frame.png", false);
//    }

#endif