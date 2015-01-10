#include "EditorState.h"

#include "InputDefinition.h"

#include "Constants.h"

#include "MenuState.h"
#include "gameobjects/GameObjectManager.h"
#include "gameobjects/GameObject.h"

#include <cmath>
#include <algorithm>
//#include <utility>

#include <iostream>

EditorState EditorState::m_EditorState;

EditorState::EditorState()
{
    m_objListButtonPos = {Point(0,400), Point(40,400), Point(80,400),
			    Point(0,450), Point(40,450), Point(80,450),
			    Point(0,500), Point(40,500), Point(80,500),
			    Point(0,550), Point(40,550), Point(80,550),
			    Point(0,600), Point(40,600), Point(80,600)};
			    
    m_selected_list = CREATURES; // NONE;
}

EditorState::~EditorState()
{}


void EditorState::Init()
{
  printf("EditorState Init Successful\n");
}

void EditorState::Clean()
{
  printf("EditorState Clean Successful\n");
}

void EditorState::Pause()
{
  printf("EditorState Paused\n");
}
void EditorState::Resume()
{
  printf("EditorState Resumed\n");
}

void EditorState::HandleEvents(Game* game)
{
  if( Input::getInstance()->get_quit() )
      game->Quit();
      
  if(Input::getInstance()->is_key_pressed(KEY_ESCAPE))
      game->ChangeState(MenuState::Instance());
      
    if(Input::getInstance()->is_mouse_down(MOUSE_LEFT)){
	//if(Input::getInstance()->is_mouse_inside(Rect rectangle)){
	//    
	//}
    }
}
void EditorState::Update(Game* game)
{
  ;
}

void EditorState::Draw(Game* game, Renderer* renderer)
{
    m_currentWindowSize = renderer->getWindowSize();
    
    m_backgoundBox.w = m_currentWindowSize.w*0.20;
    m_backgoundBox.x = m_currentWindowSize.w-m_backgoundBox.w;
    m_backgoundBox.h = m_currentWindowSize.h;
    
    DrawStaticMenu(renderer);
    DrawCurrentObjectList(renderer);
  //renderer->drawTexture(Rect(0,0,renderer->getWindowSize().w, renderer->getWindowSize().h), BACKGROUND_PAUSEMENU_FILEPATH, false);
  //SDL_Flip(game->getScreen());
}

void EditorState::DrawStaticMenu(Renderer* renderer){
    
    // Clear array for new insertion
    m_toolBoxes.clear();
    
    // Render menu background
    renderer->drawTexture(Rect(m_backgoundBox.x,0,m_backgoundBox.w, m_backgoundBox.h), E_MENU_BACKGROUND_FILEPATH, false);
    
    // Create/update toolBox
    m_toolBox.x = m_backgoundBox.x + m_backgoundBox.w*0.05;
    m_toolBox.y =  m_backgoundBox.h*0.10;
    m_toolBox.w = m_backgoundBox.w*0.90;
    m_toolBox.h = m_backgoundBox.w*0.20; // We set the height to buttons diameter cuz we only got 1 row
    
    
    // Temporary boxsize for the buttons
    Rect button;
    button.y = m_toolBox.y; // button.y is always the same(one row only)
    // We set an max size cuz we dont want buttons to follow windows size for too long...
    if(m_toolBox.h > 80){
	button.w = 80;
	button.h = 80;
    }
    else{
	button.w = m_toolBox.h;
	button.h = m_toolBox.h;
    }
    
    //ADD, MARK, COPY, MOVE
    // Render tool buttons..
    // ADD
    button.x = m_toolBox.x; 
    m_toolBoxes.push_back(button, ADD);
    renderer->drawTexture(button, E_MENU_BUTTONFRAME_FILEPATH, false);
    // MARK
    button.x = m_toolBox.x + m_toolBox.w*0.26; 
    m_toolBoxes.push_back(button, MARK ); 
    renderer->drawTexture(button, E_MENU_BUTTONFRAME_FILEPATH, false);
    // COPY
    button.x = m_toolBox.x + m_toolBox.w*0.52; 
    m_toolBoxes.push_back(button, COPY );
    renderer->drawTexture(button, E_MENU_BUTTONFRAME_FILEPATH, false);
    // MOVE
    button.x = m_toolBox.x + m_toolBox.w*0.77; 
    m_toolBoxes.push_back(button, MOVE ); 
    renderer->drawTexture(button, E_MENU_BUTTONFRAME_FILEPATH, false);
    // END OF TOOLS
    
    // Create/update list selection
    button.x = m_backgoundBox.x + m_backgoundBox.w*0.10;
    button.y = m_backgoundBox.h*0.40;
    button.w = m_backgoundBox.w*0.30;
    button.h = m_backgoundBox.h*0.03;
    
    renderer->drawTexture(button, E_MENU_BUTTONFRAME_FILEPATH, false);
    renderer->drawTexture(button, "imgs/editor/text_creatures.png", false);
    
    button.x = m_backgoundBox.x + m_backgoundBox.w*0.60;
    renderer->drawTexture(button, E_MENU_BUTTONFRAME_FILEPATH, false);
    renderer->drawTexture(button, "imgs/editor/text_platforms.png", false);
    // END OF LIST SELECTION
    
    //E_MENU_BUTTONFRAME_FILEPATH
    //E_MENU_BACKGROUND_FILEPATH
    //E_MENU_MARKEDBUTTON_FILEPATH
}

void EditorState::DrawCurrentObjectList(Renderer* renderer){
    //GameObjectManager::Instance()
    //PLATFORMLIST, PROJECTILELIST, ENEMYLIST
    
    // We have to update m_ListBoxes every time in case of window resize
    // Therefor we clear it every time..
    m_ListBoxes.clear();
    
    // Get all loaded gameobject for selected list
    std::map<std::string, GameObject*>* currentList;
    if(m_selected_list == PLATFORMS){
	currentList = GameObjectManager::Instance()->GetLoadedList(GameObjectManager::PLATFORMLIST);
    }
    else if(m_selected_list == CREATURES){
	currentList = GameObjectManager::Instance()->GetLoadedList(GameObjectManager::ENEMYLIST);
    }
    else{
	return;
    }
    
    // ################################
    int size = currentList->size();
    m_listBox.x = m_backgoundBox.x + m_backgoundBox.w*0.05;
    m_listBox.y =  m_backgoundBox.h*0.45;
    m_listBox.w = m_backgoundBox.w*0.90;
    m_listBox.h = m_backgoundBox.h - m_listBox.x;
    // ################################
    // Get the maximum possible buttonsize to fit all buttons widthin the listBox
    int buttonSize = GetButtonSize(m_listBox.w, m_listBox.x, size);
    
    if(buttonSize > 80) // We dont want the buttons to be too large..
	buttonSize =  80;

    int maxRows = m_listBox.x / buttonSize;
    int maxCols = m_backgoundBox.w / buttonSize;
    
    // This is just to fix some space between boxes
    buttonSize = buttonSize*0.90;
    int rowspace = buttonSize*1.10;
    
    // Setting an iterator on current loaded gameobject.
    std::map<std::string, GameObject*>::iterator it = currentList->begin();
    
    // Loop to render grid of clickable gameobjects
    for ( unsigned int row = 0; row < maxRows; ++row ){
	for ( unsigned int column = 0; column < maxCols; ++column ){
	    
	    // Check if we are out of gameobjects in list
	    int listNum = maxCols*row + column;
	    if( listNum >= size)
		break;
	    // Make box for the current objectbox.
	    Rect confBox;
	    confBox.x = ( m_listBox.x + ( (m_listBox.w/maxCols)*column ) );
	    confBox.y = ( m_listBox.y + rowspace*row );
	    confBox.w = buttonSize;
	    confBox.h = buttonSize;
	    // To check against mouseclicks we save all the boxes with its gameobject
	    m_ListBoxes.push_back( std::make_pair(confBox, it->second));
	    // Render box-background with its gameobject
	    renderer->drawTexture(confBox, E_MENU_BUTTONFRAME_FILEPATH, false);
	    renderer->drawTexture(Rect(confBox.x+buttonSize*0.20, confBox.y+buttonSize*0.20, buttonSize*0.60, buttonSize*0.60), (it++)->second->getTexturePath(), false);
	}
	
    }
}

int EditorState::GetButtonSize(int width, int height, int tileCount)
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
}