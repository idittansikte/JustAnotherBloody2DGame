#include "Menu.h"

//template<class T>
//Menu<T>::Menu( float x, float y, float w, float h )	
//{
//	m_virtual_position.x = x;
//	m_virtual_position.y = y;
//	m_virtual_position.w = w;
//	m_virtual_position.h = h;
//}
    
//template<class T>
//void Menu<T>::Insert( std::string image, T object ){ //std::vector< std::pair<Rect<int>, T> > buttons
//    Button<T> button;
//    button.b_image = image;
//    button.b_box = Rect<int>();
//    button.b_object = object;
//    m_buttons.push_back(button);
//}
//
//template<class T>
//void Menu<T>::Draw( Renderer* renderer ){
//    for( unsigned int i = 0; i < m_buttons.size(); ++i){
//	renderer->drawTexture(m_buttons[i].b_box, E_MENU_BUTTONFRAME_FILEPATH, false);
//	renderer->drawTexture(m_buttons[i].b_box, m_buttons[i].b_image, false);
//	//if( m_selected_list != NONE ){
//	//    if(m_selected_list == it.second)
//	//	renderer->drawTexture(it.first, "imgs/editor/marked_frame.png", false);
//	//}
//    }
//}
//
//template<class T>
//int Menu<T>::GetButtonSize(int width, int height, int tileCount)
//{
//    // quick bailout for invalid input
//    if (width*height < tileCount) { return 0; }
//
//    // come up with an initial guess
//    double aspect = (double)height/width;
//    double xf = sqrtf(tileCount/aspect);
//    double yf = xf*aspect;
//    int x = std::max(1.0, floor(xf));
//    int y = std::max(1.0, floor(yf));
//    int x_size = floor((double)width/x);
//    int y_size = floor((double)height/y);
//    int tileSize = std::min(x_size, y_size);
//
//    // test our guess:
//    x = floor((double)width/tileSize);
//    y = floor((double)height/tileSize);
//    if (x*y < tileCount) // we guessed too high
//    {
//        if (((x+1)*y < tileCount) && (x*(y+1) < tileCount))
//        {
//            // case 2: the upper bound is correct
//            //         compute the tileSize that will
//            //         result in (x+1)*(y+1) tiles
//            x_size = floor((double)width/(x+1));
//            y_size = floor((double)height/(y+1));
//            tileSize = std::min(x_size, y_size);
//        }
//        else
//        {
//            // case 3: solve an equation to determine
//            //         the final x and y dimensions
//            //         and then compute the tileSize
//            //         that results in those dimensions
//            int test_x = ceil((double)tileCount/y);
//            int test_y = ceil((double)tileCount/x);
//            x_size = std::min(floor((double)width/test_x), floor((double)height/y));
//            y_size = std::min(floor((double)width/x), floor((double)height/test_y));
//            tileSize = std::max(x_size, y_size);
//        }
//    }
//
//    return tileSize;
//} // GetButtonSize() END