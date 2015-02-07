#include "EditorEvent.h"

//#include "../InputDefinition.h"
//#include "../Input.h"

#include "../MenuState.h"

#include <iostream>
#include <map>
#include <iterator>

void EditorEvent::Quit(Game* game){
    if( Input::getInstance()->get_quit() )
	game->Quit();
}

void EditorEvent::QuitEditor(Game* game){
    if(Input::getInstance()->is_key_pressed(KEY_ESCAPE))
	game->ChangeState(MenuState::Instance());
}

void EditorEvent::Scroll(Point &camera_position){
     if( Input::getInstance()->is_mouse_pressed( MOUSE_WHEEL ) ){
	// Calculate the diffrence between last frames mouse pos and this frame
	m_camera_movement.x = m_camera_movement.x - Input::getInstance()->get_mouse_x();
	m_camera_movement.y = m_camera_movement.y - Input::getInstance()->get_mouse_y();
	// Add the diffrence to the next camerapos
	camera_position.x -= m_camera_movement.x;
	camera_position.y -= m_camera_movement.y;

	// Set the current mousepos for the next frame
	ResetCameraMovement();
    }else{ // Set current mousepos if we want to scroll next frame
	ResetCameraMovement();
    }
}

void EditorEvent::ResetCameraMovement(){
    m_camera_movement.x = Input::getInstance()->get_mouse_x();
    m_camera_movement.y = Input::getInstance()->get_mouse_y(); 
}
void EditorEvent::Layer(EditorState* editor){
    // Handle layer keys
    if(Input::getInstance()->is_key_down(KEY_1)){
	editor->ChangeLayer(1);
    }
    else if(Input::getInstance()->is_key_down(KEY_2)){
	editor->ChangeLayer(2);
    }
    else if(Input::getInstance()->is_key_down(KEY_3)){
	editor->ChangeLayer(3);
    }
    else if(Input::getInstance()->is_key_down(KEY_4)){
	editor->ChangeLayer(4);
    }
    else if(Input::getInstance()->is_key_down(KEY_5)){
	editor->ChangeLayer(5);
    }
}

void EditorEvent::RemoveLastAddedObject(EditorState* editor){
    // Remove last added object
    if(Input::getInstance()->ctrl() && Input::getInstance()->is_key_down(KEY_Z) && Input::getInstance()->is_key_pressed(KEY_Z) ){
	editor->RemoveLastAdded();
    }
}

void EditorEvent::ReleaseObjectFromMouse( GameObject* &selected_object, EditorState::ButtonType tool){
    
    if( selected_object == nullptr )
	return;
    
    //if( tool != EditorState::ADD ){
	selected_object = nullptr;
//    }
//    else{
//	if( selected_object->getType() != GameObject::PLAYER ){
//	    GameObject* keeper = selected_object->Clone();
//	    selected_object = nullptr;
//	    selected_object = keeper;
//	}
//	else{
//	    selected_object = nullptr;
//	}
//    }
}

GameObject* EditorEvent::GetLevelObjectOnMouse( std::multimap<int, GameObject*>* level_list ) {
    // I'm using reverse_iterator because if items are stacked on each other I want the top layer object. Therefore I search outside and in...
    GameObject* p = nullptr;
    std::multimap<int, GameObject*>::reverse_iterator rit;
    for(rit = level_list->rbegin() ; rit != level_list->rend() ; ++rit){
	if( Input::getInstance()->is_mouse_inside( rit->second->getRect() ) ){
	    p = rit->second;
	    break;
	}
    }
    return p;
}