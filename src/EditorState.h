#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include <vector>
#include <map>

#include "editor/Menu.h"
#include "GameState.h"
#include "Renderer.h"

#include "Rect.h"
#include "Point.h"
#include "Level.h"

class GameObject;
class Player;
class EditorEvent;


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
    //void UpdateStaticMenu();
    //void UpdateSelectedObjectList();
    
    void Draw(Game* game, Renderer* renderer);
    //void DrawStaticMenu(Renderer* renderer);
    //void DrawSelectedObjectList(Renderer* renderer);
    void DrawMovingObjectArea(Renderer* renderer);
    void DrawCursor(Renderer* renderer);
    
    
    GameObject* AddObject(GameObject*);
    void ChangeLayer(int newLayer);
    void RemoveLastAdded();
    void RemoveObject(GameObject* object);
    void RemoveSelectedObject();
    
    Point GetGridPos(Rect<int> box);
    
    void UpdateCamera();
    
    static EditorState* Instance()
    {
      return &m_EditorState;
    }
    
  protected:
    
    EditorState();
    
  private:
    static EditorState m_EditorState;
    
    Level *m_level;
    
    // Selections, to know what "states" that is actve;
    ButtonType m_selected_tool;
    ButtonType m_selected_list;
    GameObject* m_selected_listobject;
    int m_selected_layer;
    
    std::pair<int, GameObject*> m_player;
    
    Rect<int> m_currentWindowSize;
    Rect<int> m_rightmenubox;
    Rect<int> m_levelWindow;
    
    std::vector<GameObject*> m_lastAddedObjects;
    
    
    const int m_gridSize{10};
    
    Point m_camera_position;
    
    EditorEvent* m_handle_event;
    
    Menu<int> m_toolmenu{0.82,0.20,0.18,0.20};
    Menu<int> m_listselectmenu{0.82,0.40,0.18,0.20};
    Menu<GameObject*> m_creaturemenu{0.82,0.60,0.18,0.20};
    Menu<GameObject*> m_platformmenu{0.82,0.60,0.18,0.20};
    
};

#endif