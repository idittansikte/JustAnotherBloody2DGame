#ifndef EDITOREVENT_H
#define EDITOREVENT_H

#include "../Point.h"
#include "../Rect.h"
#include "../gameobjects/GameObject.h"
#include "../EditorState.h"
//#include "../InputDefinition.h"
#include "../Input.h"

#include <vector>

class Game;

class EditorEvent{
    public:
	~EditorEvent() = default;
	void Quit(Game*);
	
	void QuitEditor(Game*);
	
	void Scroll(Point &camera_position);
	void ResetCameraMovement();
	
	void Layer(EditorState* editor);

	void RemoveLastAddedObject(EditorState* editor);
	
	template<typename T>
	T MenuButtonSelection( const Rect<int> &menuBox, const Rect<int> &outerBox, const std::vector< std::pair<Rect<int>, T> > &buttonBoxes );
	
	template<typename T>
	T GetDefault();
	
	void ReleaseObjectFromMouse( GameObject* &selected_object, EditorState::ButtonType tool = EditorState::NONE);
	
	//GameObject* GetObjectOnMouse(  int &selected_layer, std::multimap<int, GameObject*>* level_list);
	
	GameObject* GetLevelObjectOnMouse( std::multimap<int, GameObject*>* level_list) ;
	
	void LeftMouseClick(EditorState*);
	
	void Ctrl_S(EditorState*);
	
    private:
	Point m_camera_movement;
};


template<typename T>
T EditorEvent::MenuButtonSelection( const Rect<int> &menuBox, const Rect<int> &outerBox, const std::vector< std::pair<Rect<int>, T> > &buttonBoxes){
    T found = GetDefault<T>();
    if(Input::getInstance()->is_mouse_down(MOUSE_LEFT)){
	if(Input::getInstance()->is_mouse_inside(menuBox))
	{	// Handle tool selection
	    if(Input::getInstance()->is_mouse_inside(outerBox) && buttonBoxes.size() != 0 ){
		for(auto it : buttonBoxes){
		    if(Input::getInstance()->is_mouse_inside(it.first)){
			found = it.second;
			break;
		    }
		}
	    }
	}
    } // End of Left mouse click
    return found;
}

// Specializations

template <>
inline GameObject* EditorEvent::GetDefault<GameObject*>(){
    return nullptr;
}

template <>
inline EditorState::ButtonType EditorEvent::GetDefault<EditorState::ButtonType>(){
    return EditorState::NONE;
}

#endif