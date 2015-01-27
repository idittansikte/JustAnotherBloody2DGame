#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include <SDL2/SDL.h>
#include <vector>
#include <map>


#include "GameState.h"
#include "Renderer.h"
#include "Input.h"
#include "Rect.h"
#include "Point.h"
#include "Level.h"

class GameObject;
class Player;

class EditorState : public GameState
{
  public:
    
    enum ButtonType{ NONE, CREATURES, PLATFORMS, ADD, MARK, DELETE, MOVE }; // To know wich one that is selected
    
    ~EditorState();
    
    void Init();
    void Clean();
    void Save();
    
    void Pause();
    void Resume();
    
    void HandleEvents(Game* game);
    
    std::pair<int, GameObject*> GetListPairOnMouse();
    
    void Update(Game* game);
    void UpdateStaticMenu();
    void UpdateSelectedObjectList();
    
    void Draw(Game* game, Renderer* renderer);
    void DrawStaticMenu(Renderer* renderer);
    void DrawSelectedObjectList(Renderer* renderer);
    void DrawMovingObjectArea(Renderer* renderer);
    void DrawCursor(Renderer* renderer);
    
    void AddObject(GameObject*);
    
    void ChangeLayer(int newLayer);
    
    void RemoveLastAdded();
    void RemoveObject(GameObject* object);
    void RemoveSelectedObject();
    void RemoveIterator( std::multimap<int, GameObject*>::iterator it );
    
    int GetButtonSize(int width, int height, int tileCount);
    
    Point GetGridPos(Rect box);
    void UpdateCamera();
    
    static EditorState* Instance()
    {
      return &m_EditorState;
    }
    
  protected:
    
    EditorState();
    
  private:
    static EditorState m_EditorState;
    
    Level m_level;
    
    ButtonType m_selected_tool;
    ButtonType m_selected_list;
    GameObject* m_selected_listobject;
    
    std::multimap<int, GameObject*>::iterator m_it;
    
    int m_selected_layer;
    
    Rect m_toolBox;
    std::vector< std::pair< Rect, ButtonType > > m_toolBoxes;

    Rect m_layerBox;
    
    Rect m_sel_list_box;
    std::vector< std::pair<Rect, ButtonType> > m_sel_list_boxes;
  
    Rect m_listBox;
    std::vector< std::pair<Rect, GameObject*> > m_ListBoxes;
    
    Rect m_currentWindowSize;
    Rect m_backgoundBox;
    Rect m_levelWindow;
    
    std::vector<std::multimap<int, GameObject*>::iterator> m_lastAddedObjects;
    std::pair<int, GameObject*> m_player;
    
    const int m_listColumns{3};
    const int m_listRows{12};
    std::vector<Point> m_objListButtonPos;
    
    Point m_mousePos;
    const int m_gridSize{10};
    
    Rect m_camera_position;
    Point m_camera_movement;
    
};

#endif