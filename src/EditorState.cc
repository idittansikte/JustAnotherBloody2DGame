#include "EditorState.h"

#include "InputDefinition.h"
#include "Constants.h"

#include "Input.h"
#include "MenuState.h"
#include "gameobjects/GameObjectManager.h"
#include "gameobjects/GameObject.h"
#include "gameobjects/Enemy.h"
#include "editor/EditorEvent.h"
#include "editor/Menu.h"

#include <SDL2/SDL.h>
#include <cmath>
#include <algorithm>
#include <fstream>

#include <iostream>


EditorState EditorState::m_EditorState;

EditorState::EditorState()
{
}

EditorState::~EditorState()
{
    m_selected_listobject = nullptr;
}


void EditorState::Init(){
    m_level = new Level("");
    
    m_selected_list = NONE; // NONE;
    m_selected_tool = NONE;
    m_selected_listobject = nullptr;
    m_player.second = nullptr;
    m_selected_layer = 3;
    m_handle_event = new EditorEvent();
    
    m_toolmenu.Insert( (int)ADD, "imgs/editor/add.png" );
    m_toolmenu.Insert( (int)MARK, "imgs/editor/mark.png" );
    m_toolmenu.Insert( (int)DELETE, "imgs/editor/delete.png");
    m_toolmenu.Insert( (int)MOVE, "imgs/editor/move.png");
    
    m_listselectmenu.Insert( CREATURES, "imgs/editor/text_creatures.png");
    m_listselectmenu.Insert( PLATFORMS, "imgs/editor/text_platforms.png");
    
    std::map<std::string, GameObject*>* creatureList = GameObjectManager::Instance()->GetLoadedList(GameObjectManager::PLATFORMLIST);
    std::map<std::string, GameObject*>* platformList = GameObjectManager::Instance()->GetLoadedList(GameObjectManager::ENEMYLIST);
    
    for(auto creature : *creatureList){
	m_creaturemenu.Insert( creature.second, creature.second->getTexturePath() );
    }
    for(auto platform : *platformList){
	m_platformmenu.Insert( platform.second, platform.second->getTexturePath() );
    }
    
    printf("EditorState Init Successful\n");
}
    //
    //renderer->drawTexture(m_layerBox, "imgs/editor/layer.png", false);
    //Rect<int> currentLayer = Rect<int>(m_layerBox.x +5+ (m_selected_layer-1)*(m_layerBox.w*0.20), m_layerBox.y*1.08, m_layerBox.w*0.17, m_layerBox.h*0.60 );
    //renderer->drawTexture(currentLayer, "imgs/editor/layer_marker.png", false);

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
    
    if( Input::getInstance()->is_mouse_down(MOUSE_LEFT) ){  // Handle left mouse key
	if( Input::getInstance()->is_mouse_inside( m_rightmenubox ) ){
	    // Menu selection
	    ButtonType tool = (ButtonType)m_toolmenu.GetButtonItemOnMouse();
	    if( tool != NONE ){
		RemoveSelectedObject();
		m_selected_tool = tool;
	    }
	    
	    ButtonType list = (ButtonType)m_listselectmenu.GetButtonItemOnMouse();
	    if( list != NONE ){
		RemoveSelectedObject();
		m_selected_list = list;
	    }
	    
	    GameObject* tmp_selected = nullptr;
	    if(m_selected_list == CREATURES){
		tmp_selected = m_creaturemenu.GetButtonItemOnMouse();
	    }
	    else if(m_selected_list == PLATFORMS){
		tmp_selected = m_platformmenu.GetButtonItemOnMouse();
	    }
	    if( tmp_selected != nullptr ){
		RemoveSelectedObject();
		m_selected_listobject = AddObject(tmp_selected);
	    }
	}	// End of menu selection
	    if( Input::getInstance()->is_mouse_inside( m_levelWindow ) ){ // Handle events in level window when mouseclick
		switch(m_selected_tool){
		    case ADD:
			m_handle_event->ReleaseObjectFromMouse( m_selected_listobject, m_selected_tool );
		    break;
		    case DELETE:
			RemoveObject( m_handle_event->GetLevelObjectOnMouse( m_level->GetEditorList() ) );
		    break;
		    case MARK:
		    case MOVE:
			if( m_selected_listobject == nullptr ){
			    m_selected_listobject = m_handle_event->GetLevelObjectOnMouse( m_level->GetEditorList() );
			}
		    break;
		    default:
		    break;
		}// End of switch case
	    }	// End level window
    } // END OF LEFT MOUSECLICK
    
    if( Input::getInstance()->is_mouse_inside( m_levelWindow ) ){ // Handle events in level window when mouseclick
	if( Input::getInstance()->is_mouse_pressed(MOUSE_LEFT) ){
	    switch(m_selected_tool){
		case MARK:
		    ;
		break;
		case MOVE:
		    ;
		break;
		default:
		break;
	    }
	}
	else{ // IF LEFT MOUSE NOT PRESSED
	    switch(m_selected_tool){
		case MARK:
		case MOVE:
		    m_handle_event->ReleaseObjectFromMouse( m_selected_listobject );
		break;
		default:
		break;
	    }
	}
    } // END OF INSIDE LEVELWINDOW
} // HandleEvents END

void EditorState::Update(Game* game)
{
    
    //std::cout << "| Last added list size: " << m_lastAddedObjects.size() << " | Level list size: " << m_level->GetEditorList()->size() << " | \n";
    UpdateCamera();

    m_toolmenu.Update(m_currentWindowSize);
    m_listselectmenu.Update(m_currentWindowSize);
    m_creaturemenu.Update(m_currentWindowSize);
    m_platformmenu.Update(m_currentWindowSize);
    
    if( m_selected_tool == MARK && m_selected_listobject != nullptr && m_selected_listobject->getType() == GameObject::ENEMY){
	Enemy* enemy = dynamic_cast<Enemy*>(m_selected_listobject);
	Rect<int> A = enemy->getRect();
	Point mousepos( Input::getInstance()->get_mouse_x(), Input::getInstance()->get_mouse_y() );
	if( mousepos.x < A.x + (A.w/2) ){ // LEFT SIDE
	    if(mousepos.x > A.x){
		enemy->SetMaxMovementLeft(0);
	    }
	    else if(mousepos.x < A.x){
		enemy->SetMaxMovementLeft(A.x-mousepos.x);
	    }
	}
	else{
	    if(mousepos.x < A.x + A.w){
		enemy->SetMaxMovementRight(0);
	    }
	    else{
		enemy->SetMaxMovementRight(mousepos.x - (A.x + A.w));
	    }
	}
    }
    else if(m_selected_listobject != nullptr){
	Rect<int> pos = m_selected_listobject->getRect();
	m_selected_listobject->updatePos(GetGridPos(pos));
    }
}

void EditorState::Draw(Game* game, Renderer* renderer)
{
    m_currentWindowSize = renderer->getWindowSize();
    
    m_level->Draw(renderer);
    
    m_rightmenubox.w = m_currentWindowSize.w*0.20;
    m_rightmenubox.x = m_currentWindowSize.w-m_rightmenubox.w;
    m_rightmenubox.h = m_currentWindowSize.h;
    
    m_levelWindow.x = 0;
    m_levelWindow.y = 0;
    m_levelWindow.w = m_currentWindowSize.w - m_rightmenubox.w;
    m_levelWindow.h = m_currentWindowSize.h;
    
    renderer->drawTexture(m_rightmenubox, "imgs/editor/alpha.png", false);
    //Draw all menus
    m_toolmenu.Draw(renderer);

    if(m_selected_tool != NONE){
	if(m_selected_tool == ADD)
	{
	    m_listselectmenu.Draw(renderer);
	    
	    if( m_selected_list == CREATURES ){
		m_creaturemenu.Draw(renderer);
	    }
	    else if( m_selected_list == PLATFORMS ){
		m_platformmenu.Draw(renderer);
	    }   
	}
    }
    DrawMovingObjectArea(renderer);
    DrawCursor(renderer);
} // Draw() END 

void EditorState::DrawMovingObjectArea(Renderer* renderer){
    
    std::multimap<int, GameObject*>* List = m_level->GetEditorList();
    std::multimap<int, GameObject*>::iterator it;
    
    for(it = List->begin(); it != List->end(); ++it){
	if( (*it).second->getType() == GameObject::ENEMY ){
	    Enemy* enemy = dynamic_cast<Enemy*>((*it).second);
	    Rect<int> e = enemy->getRect();
	    Rect<int> a;
	    if(enemy->GetMaxMovementLeft() != 0){
		a.x = e.x - enemy->GetMaxMovementLeft() + 30;
		a.y = e.y + 30;
		a.h = e.h - 30;
		a.w = enemy->GetMaxMovementLeft() - 30;
		renderer->drawTexture(a, "imgs/editor/greenarrowtail.png", true);
		a.x -= 30;
		a.w = 30;
		renderer->drawTexture(a, "imgs/editor/greenarrowhead.png", true, Rect<int>(), true);
	    }
	    if(enemy->GetMaxMovementRight() != 0){
		a.x = e.x + e.w;
		a.y = e.y + 30;
		a.h = e.h - 30;
		a.w = enemy->GetMaxMovementRight() - 30;
		renderer->drawTexture(a, "imgs/editor/greenarrowtail.png", true);
		a.x += a.w;
		a.w = 30;
		renderer->drawTexture(a, "imgs/editor/greenarrowhead.png", true);
	    }
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
	Rect<int> A(Input::getInstance()->get_mouse_x()-10+renderer->getCameraAdjustment().x, Input::getInstance()->get_mouse_y()-10+renderer->getCameraAdjustment().y, 20, 20 );
	renderer->drawTexture(A, img, true, Rect<int>(), true);
    }
    else{
	renderer->DisableCursor(false);
    }
}

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
    
    m_level->GetEditorList()->insert( make_pair(m_selected_layer,newobject) );
    m_lastAddedObjects.push_back( newobject );
    
    return m_lastAddedObjects.back();
} // AddObject() END

void EditorState::ChangeLayer(int newLayer){
    
    m_selected_layer = newLayer;
    // If object is selected we change that one too.
    if(m_selected_listobject != nullptr){
	
	if( m_player.second == m_selected_listobject ){
	    m_player.first = m_selected_layer;
	}
	
	for( std::vector<GameObject*>::reverse_iterator rit= m_lastAddedObjects.rbegin(); rit != m_lastAddedObjects.rend(); ++rit ){ // Find selected object in iterator list
	    if(*rit == m_selected_listobject){ // If found
		// Replacement: delete old element in list to a new with correct layer..
		// Copy selected element;
		GameObject* tempObj = m_selected_listobject;
	    // Insert new element with correct layer and replace old iterator in iterator list with iterator to the new place 
		m_selected_listobject = AddObject(m_selected_listobject); // Assign new object to selected object
		// Cleanup pointer and remove object from object list
		RemoveObject(tempObj);
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
    printf("searching...\n");
    for(auto it_last : m_lastAddedObjects){
	if(it_last == object){
	    printf("found...\n");
	    std::swap(it_last, m_lastAddedObjects.back());
	    m_lastAddedObjects.pop_back();
	    for( std::multimap<int, GameObject*>::iterator it_level = (*m_level->GetEditorList()).begin(); it_level != (*m_level->GetEditorList()).end(); ++it_level){
		if( it_level->second == object){
		    delete it_level->second;
		    it_level->second = nullptr;
		    m_level->GetEditorList()->erase(it_level);
		    std::cout << "RemoveObject:: removed.. \n";
		    return;
		}
	    }
	}
    }
}

void EditorState::RemoveLastAdded(){

    if(m_lastAddedObjects.back() == m_selected_listobject){
	if(m_lastAddedObjects.size() >= 2)
	    std::swap(*(m_lastAddedObjects.end()-2), m_lastAddedObjects.back()); // Swap past selected object
	RemoveObject(m_lastAddedObjects.back());
    }
    else if (!m_lastAddedObjects.empty())
	RemoveObject(m_lastAddedObjects.back());
}

Point EditorState::GetGridPos(Rect<int> box){
    //Get mouse position
    Point mousePos(Input::getInstance()->get_mouse_x(), Input::getInstance()->get_mouse_y());
    Point midpos(mousePos.x-box.w/2 + m_camera_position.x - m_currentWindowSize.w/2, mousePos.y-box.h/2+ m_camera_position.y - m_currentWindowSize.h/2);
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
	for( auto it : *m_level->GetEditorList() ){
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
    m_level->SetCamera( Rect<int>(m_camera_position.x, m_camera_position.y,0,0) );
}