#include "EditorState.h"

#include "InputDefinition.h"

#include "Constants.h"

#include "MenuState.h"
#include "gameobjects/GameObjectManager.h"
#include "gameobjects/GameObject.h"
#include "gameobjects/Enemy.h"
#include "Input.h"
#include "editor/EditorEvent.h"

#include <SDL2/SDL.h>
#include <cmath>
#include <algorithm>
#include <fstream>

#include <iostream>


EditorState EditorState::m_EditorState;

EditorState::EditorState()
{
    m_objListButtonPos = {Point(0,400), Point(40,400), Point(80,400),
			    Point(0,450), Point(40,450), Point(80,450),
			    Point(0,500), Point(40,500), Point(80,500),
			    Point(0,550), Point(40,550), Point(80,550),
			    Point(0,600), Point(40,600), Point(80,600)};
			    
    m_selected_list = NONE; // NONE;
    m_selected_tool = NONE;
    m_selected_listobject = nullptr;
    m_player.second = nullptr;
    m_selected_layer = 3;
    m_handle_event = new EditorEvent();
}

EditorState::~EditorState()
{
    m_selected_listobject = nullptr;
}


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

void EditorState::HandleEvents(Game* game){
    
    m_handle_event->Quit(game);
	
    m_handle_event->QuitEditor(game);
	
    m_handle_event->Scroll(m_camera_position);
    
    if(Input::getInstance()->ctrl() && Input::getInstance()->is_key_pressed(KEY_S))
	Save();
    
    m_handle_event->Layer(this);
    
    // Remove last added object
    if(Input::getInstance()->ctrl() && Input::getInstance()->is_key_down(KEY_Z) && Input::getInstance()->is_key_pressed(KEY_Z) ){
	RemoveLastAdded();
    }
    
    ButtonType tool = m_handle_event->MenuButtonSelection<ButtonType>( m_backgoundBox, m_toolBox, m_toolBoxes );
    if( tool != NONE ){
	m_selected_tool = tool;
    }
    
    ButtonType list = m_handle_event->MenuButtonSelection<ButtonType>( m_backgoundBox, m_sel_list_box, m_sel_list_boxes );
    if( list != NONE ){
	m_selected_list = list;
    }
    GameObject* tmp_selected = m_handle_event->MenuButtonSelection<GameObject*>( m_backgoundBox, m_listBox, m_ListBoxes );
    if( tmp_selected != nullptr ){
	if(m_selected_listobject != nullptr)
	    RemoveSelectedObject();
	m_selected_listobject = AddObject(tmp_selected);
    }

    if( Input::getInstance()->is_mouse_inside( m_levelWindow ) ){ // Handle events in level(ex. outside of right menu)
	if( Input::getInstance()->is_mouse_down(MOUSE_LEFT) ){  // Handle left mouse key inside right-menu
	    switch(m_selected_tool){
		case ADD:
		    m_handle_event->ReleaseObjectFromMouse( m_selected_listobject, m_selected_tool );
		break;
		case DELETE:
		    RemoveObject( m_handle_event->GetObjectOnMouse( m_selected_layer, m_level.GetEditorList() ) );
		break;
		case MARK:
		case MOVE:
		    if(m_selected_listobject == nullptr)
			m_selected_listobject = m_handle_event->GetObjectOnMouse( m_selected_layer, m_level.GetEditorList() );
		break;
	    }
	}// END OF LEFT MOUSECLICK DOWN
	
	if( Input::getInstance()->is_mouse_pressed(MOUSE_LEFT) ){
	   switch(m_selected_tool){
		case MARK:
		    ;
		break;
	    	case MOVE:
		    ;
		break;
	    }
	}
	else{ // IF LEFT MOUSE NOT PRESSED
	    switch(m_selected_tool){
		case MARK:
		case MOVE:
		    m_handle_event->ReleaseObjectFromMouse( m_selected_listobject );
		break;
	    }
	}
    } // END OF INSIDE LEVELWINDOW

} // HandleEvents END

void EditorState::Update(Game* game)
{
    UpdateCamera();
    UpdateStaticMenu();
    UpdateSelectedObjectList();
    if( m_selected_tool == MARK && m_selected_listobject != nullptr ){
	Enemy* enemy = dynamic_cast<Enemy*>(m_selected_listobject);
	Rect A = enemy->getRect();
	Point mousepos( Input::getInstance()->get_mouse_x(), Input::getInstance()->get_mouse_y() );
	if( mousepos.x < A.x + A.w/2 ){ // LEFT SIDE
	    enemy->SetMaxMovementRight(-mousepos.x);
	}
	else{
	    enemy->SetMaxMovementLeft(-mousepos.x);
	}
    }
    else if(m_selected_listobject != nullptr){
	Rect pos = m_selected_listobject->getRect();
	m_selected_listobject->updatePos(GetGridPos(pos));
    }
}

void EditorState::UpdateStaticMenu(){
    
    // Clear array for new insertion
    m_toolBoxes.clear();
    m_sel_list_boxes.clear();
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
    
    //ADD, MARK, DELETE, MOVE
    // Update tool buttons..
    // ADD
    button.x = m_toolBox.x; 
    m_toolBoxes.push_back( std::make_pair( button, ADD) );
    // MARK
    button.x = m_toolBox.x + m_toolBox.w*0.26; 
    m_toolBoxes.push_back( std::make_pair( button, MARK ) ); 
    // DELETE
    button.x = m_toolBox.x + m_toolBox.w*0.52; 
    m_toolBoxes.push_back( std::make_pair( button, DELETE ) );
    // MOVE
    button.x = m_toolBox.x + m_toolBox.w*0.77; 
    m_toolBoxes.push_back( std::make_pair( button, MOVE ) ); 
    // END OF TOOLS
    
    m_layerBox.x = m_backgoundBox.x + m_backgoundBox.w*0.05;
    m_layerBox.y =  m_backgoundBox.h*0.30;
    m_layerBox.w = m_backgoundBox.w*0.90;
    m_layerBox.h = m_backgoundBox.w*0.20;
    
    
} // UpdateStaticMenu() END

void EditorState::UpdateSelectedObjectList(){
    // We have to update m_ListBoxes every time in case of window resize
    // Therefor we clear it every time..
    m_ListBoxes.clear();
    
    // Create/update list selection box and inner boxes
    //m_selected_list_boxes
    m_sel_list_box.x = m_backgoundBox.x + m_backgoundBox.w*0.10;
    m_sel_list_box.y = m_backgoundBox.h*0.40;
    m_sel_list_box.w = m_backgoundBox.w*0.80;
    m_sel_list_box.h = m_backgoundBox.h*0.03;
    
    // Update list selection buttons
    Rect button;
    button.x = m_sel_list_box.x;
    button.y = m_sel_list_box.y;
    button.w = m_sel_list_box.w*0.35;
    button.h = m_sel_list_box.h;
    m_sel_list_boxes.push_back( std::make_pair( button, CREATURES ) );
    
    button.x = m_backgoundBox.x + m_backgoundBox.w*0.60;
    m_sel_list_boxes.push_back( std::make_pair( button, PLATFORMS ) );
    // END OF LIST SELECTION
    
    if( m_selected_list == NONE )
	return;
    
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
    m_listBox.y = m_backgoundBox.h*0.45;
    m_listBox.w = m_backgoundBox.w*0.90;
    m_listBox.h = m_backgoundBox.h - m_listBox.y;
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
    
    // Loop to update and save grid of clickable gameobjects
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
	    m_ListBoxes.push_back( std::make_pair(confBox, (it++)->second));
	}
    }
} // UpdateSelectedObjectList() END

void EditorState::Draw(Game* game, Renderer* renderer)
{
    m_currentWindowSize = renderer->getWindowSize();
    
    m_backgoundBox.w = m_currentWindowSize.w*0.20;
    m_backgoundBox.x = m_currentWindowSize.w-m_backgoundBox.w;
    m_backgoundBox.h = m_currentWindowSize.h;
    
    m_levelWindow.x = 0;
    m_levelWindow.y = 0;
    m_levelWindow.w = m_currentWindowSize.w - m_backgoundBox.w;
    m_levelWindow.h = m_currentWindowSize.h;
    
    m_level.Draw(renderer);
    
    DrawStaticMenu(renderer);
    if(m_selected_tool != NONE){
	if(m_selected_tool == ADD)
	{
	    DrawSelectedObjectList(renderer);
	    
	}
    }
    
    DrawMovingObjectArea(renderer);
    DrawCursor(renderer);
} // Draw() END 

void EditorState::DrawStaticMenu(Renderer* renderer){
    
    // Render menu background
    renderer->drawTexture(Rect(m_backgoundBox.x,0,m_backgoundBox.w, m_backgoundBox.h), E_MENU_BACKGROUND_FILEPATH, false);
    
    //Render tool menu
    std::string img;
    for( auto it : m_toolBoxes ){
	if(it.second == ADD){
	    img = "imgs/editor/add.png";
	}
	else if(it.second == MARK){
	    img = "imgs/editor/mark.png";
	}
	else if(it.second == DELETE){
	    img = "imgs/editor/delete.png";
	}
	else if(it.second == MOVE){
	    img = "imgs/editor/move.png";
	}
	else{
	    std::cout << "No such tool exist!" << std::endl;
	    break;
	}
	renderer->drawTexture(it.first, E_MENU_BUTTONFRAME_FILEPATH, false);
	renderer->drawTexture(Rect(it.first.x+it.first.w*0.20, it.first.y+it.first.w*0.25, it.first.w*0.60, it.first.h*0.50), img, false);
	    if( m_selected_tool != NONE ){
		if(m_selected_tool == it.second)
		    renderer->drawTexture(it.first, "imgs/editor/marked_frame.png", false);
	    }
    }
    
    renderer->drawTexture(m_layerBox, "imgs/editor/layer.png", false);
    Rect currentLayer = Rect(m_layerBox.x +5+ (m_selected_layer-1)*(m_layerBox.w*0.20), m_layerBox.y*1.08, m_layerBox.w*0.17, m_layerBox.h*0.60 );
    renderer->drawTexture(currentLayer, "imgs/editor/layer_marker.png", false);
	
} // DrawStaticMenu() END


void EditorState::DrawSelectedObjectList(Renderer* renderer){
    //GameObjectManager::Instance()
    //PLATFORMLIST, PROJECTILELIST, ENEMYLIST
    std::string img;
    for( auto it : m_sel_list_boxes){
	if(it.second == CREATURES){
	    img = "imgs/editor/text_creatures.png";
	}
	else if(it.second == PLATFORMS){
	    img = "imgs/editor/text_platforms.png";
	}
	else{
	    std::cout << "No such list exist!" << std::endl;
	    break;
	}
	renderer->drawTexture(it.first, E_MENU_BUTTONFRAME_FILEPATH, false);
	renderer->drawTexture(it.first, img, false);
	if( m_selected_list != NONE ){
	    if(m_selected_list == it.second)
		renderer->drawTexture(it.first, "imgs/editor/marked_frame.png", false);
	}
    }

    // Render box-background with its gameobject
    for( auto it : m_ListBoxes){
	renderer->drawTexture(it.first, E_MENU_BUTTONFRAME_FILEPATH, false);
	renderer->drawTexture(Rect(it.first.x+it.first.w*0.20, it.first.y+it.first.h*0.20, it.first.w*0.60, it.first.h*0.60), it.second->getTexturePath(), false);
	if(m_selected_listobject != nullptr)
	    if(it.second == m_selected_listobject)
		renderer->drawTexture(it.first, "imgs/editor/marked_frame.png", false);
    }
    
} // DrawSelectedObjectList() END

void EditorState::DrawMovingObjectArea(Renderer* renderer){
    
    std::multimap<int, GameObject*>* List = m_level.GetEditorList();
    std::multimap<int, GameObject*>::iterator it;
    
    for(it = List->begin(); it != List->end(); ++it){
	if( (*it).second->getType() == GameObject::ENEMY ){
	    Enemy* enemy = dynamic_cast<Enemy*>((*it).second);
	    Rect e = enemy->getRect();
	    Rect a;
	    a.x = e.x - enemy->GetMaxMovementLeft();
	    a.y = e.y + 30;
	    a.h = e.h - 30;
	    a.w = enemy->GetMaxMovementLeft();
	    renderer->drawTexture(a, "imgs/editor/greenarrow.png", true, Rect(), true);
	    a.x = e.x + e.w;
	    a.y = e.y + 30;
	    a.h = e.h - 30;
	    a.w = enemy->GetMaxMovementRight();
	    renderer->drawTexture(a, "imgs/editor/greenarrow.png", true);
	}
    }
}

void EditorState::DrawCursor(Renderer* renderer){
    if(m_selected_tool != NONE){
	renderer->DisableCursor(true);
	std::string img;
	if(m_selected_tool == ADD){
	    img = "imgs/editor/add.png";
	}
	else if(m_selected_tool == MARK){
	    img = "imgs/editor/mark.png";
	}
	else if(m_selected_tool == DELETE){
	    img = "imgs/editor/delete.png";
	}
	else {//(m_selected_tool == MOVE){
	    img = "imgs/editor/move.png";
	}
	Rect A(Input::getInstance()->get_mouse_x()-10+renderer->getCameraAdjustment().x, Input::getInstance()->get_mouse_y()-10+renderer->getCameraAdjustment().y, 20, 20 );
	renderer->drawTexture(A, img, true, Rect(), true);
    }
    else{
	renderer->DisableCursor(false);
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
} // GetButtonSize() END

GameObject* EditorState::AddObject(GameObject* object){
//    if(m_selected_listobject != nullptr)
//	RemoveSelectedObject();
    
    GameObject* newobject =  object->Clone();
    
    if( object->getType() == GameObject::PLAYER ){
	if ( m_player.second != nullptr ){
	    RemoveObject(m_player.second);
	    std::cout << "Removing old player..\n";
	}
	m_player.first = m_selected_layer;
	m_player.second = newobject;
    }
    
    m_lastAddedObjects.push_back( m_level.GetEditorList()->emplace(m_selected_layer,newobject) );
    return m_lastAddedObjects.back()->second;
} // AddObject() END

void EditorState::ChangeLayer(int newLayer){
    
    m_selected_layer = newLayer;
    // If object is selected we change that one too.
    if(m_selected_listobject != nullptr){
	if( m_player.second == m_selected_listobject ){
	    m_player.first == m_selected_layer;
	}
	for(auto it : m_lastAddedObjects){ // Find selected object in iterator list
	    if(it->second == m_selected_listobject){ // If found
		// Replacement: delete old element in list to a new with correct layer..
		// Copy selected element;
		GameObject* tempObj = m_selected_listobject->Clone();
		// Cleanup pointer and remove object from object list
		delete m_selected_listobject; 
		m_selected_listobject = nullptr;
		m_level.GetEditorList()->erase(it); // Delete it from object list
		// Insert new element with correct layer and replace old iterator in iterator list with iterator to the new place 
		it = m_level.GetEditorList()->emplace(newLayer, tempObj); // Insert copy with new layer
		m_selected_listobject = tempObj; // Assign new object to selected object
		break; //Nothing more to do here
	    }
	}
    }
} // ChangeLayer() END

void EditorState::RemoveSelectedObject(){
    if(m_selected_listobject != nullptr){
	RemoveObject(m_selected_listobject);
	m_selected_listobject = nullptr;
    }
}

void EditorState::RemoveObject(GameObject* object){
    if(object == nullptr)
	return;

    if( m_player.second == object ){
	m_player.second = nullptr;
    }
    
    for(auto it : m_lastAddedObjects){
	if(it->second == object){
	    delete object;
	    object = nullptr;
	    std::cout << "RemoveObject:: removing.. \n";
	    RemoveIterator(it);
	}
    }
}

void EditorState::RemoveIterator( std::multimap<int, GameObject*>::iterator it ){
    if( !m_lastAddedObjects.empty() ){
	m_level.GetEditorList()->erase(it);
	
	if(it != m_lastAddedObjects.back())
	    std::swap(it, m_lastAddedObjects.back());
	    
	m_lastAddedObjects.pop_back();
    }
}

void EditorState::RemoveLastAdded(){

    if(m_selected_listobject != nullptr && m_lastAddedObjects.size() >= 2){
	if(m_lastAddedObjects.back()->second == m_selected_listobject){ // If we have a selected object and it is the last one added(at the back of list.)...
	    std::swap(*(m_lastAddedObjects.end()-2), m_lastAddedObjects.back()); // Then we swap the two obj. at the back
	    RemoveIterator( m_lastAddedObjects.back() );
	}
	else { // If we have a selected object but it isn't the last one added 
	    RemoveIterator( m_lastAddedObjects.back() );
	}
    }
    else if ( m_selected_listobject == nullptr ){
	RemoveIterator( m_lastAddedObjects.back() );
    }
}

void MarkObject(Point mousepos){

}



Point EditorState::GetGridPos(Rect box){
    //Get mouse position
    Point m_mousePos(Input::getInstance()->get_mouse_x(), Input::getInstance()->get_mouse_y());
    Point midpos(m_mousePos.x-box.w/2 + m_camera_position.x - m_currentWindowSize.w/2, m_mousePos.y-box.h/2+ m_camera_position.y - m_currentWindowSize.h/2);
    Point gridPos;
    
    gridPos.x = (midpos.x/*+(camAdjustment.x-m_currentWindowSize.w/2))*/ / (m_currentWindowSize.w/(m_currentWindowSize.w/m_gridSize)))*(m_currentWindowSize.w/(m_currentWindowSize.w/m_gridSize));
    gridPos.y = (midpos.y/*+(camAdjustment.y-m_currentWindowSize.h/2))*/ / (m_currentWindowSize.h/(m_currentWindowSize.h/m_gridSize)))*(m_currentWindowSize.h/(m_currentWindowSize.h/m_gridSize));
    //std::cout << gridPos.x << " " << gridPos.y << std::endl;
    return gridPos;
}

void EditorState::Save(){
    std::string filename = "Level.dat";
    std::ofstream output;
    output.open( filename, ios::out | ios::binary );
    if( output ){
	RemoveSelectedObject();
	if ( m_player.second == nullptr ){
	    std::cerr << "You must add a player before you can save!\n";
	    return;
	}else{
	    output << m_player.first << " " << m_player.second->GetName() << " " << m_player.second->getPos().x << " " << m_player.second->getPos().y << '\n';
	}
	for( auto it : *m_level.GetEditorList() ){
	    if( it.second != m_player.second ){
		output << it.first << " ";
		output << it.second->GetName() << " ";
		output << it.second->getPos().x << " " << it.second->getPos().y << '\n';
	    }
	}
	std::cout << "You have successfully saved your new level!\n";
	output.close();
    }
    else{
	std::cerr << filename << " could not be opened.\n";
    }
}

void EditorState::UpdateCamera(){
    // Make to make sure camera is inside level
    if(m_camera_position.x - m_currentWindowSize.w/2 < 0)
	m_camera_position.x = m_currentWindowSize.w/2;
	
    if(m_camera_position.y - m_currentWindowSize.h/2 < 0)
	m_camera_position.y = m_currentWindowSize.h/2;
    
    // Update Camera
    m_level.SetCamera( Rect(m_camera_position.x, m_camera_position.y,0,0) );
}