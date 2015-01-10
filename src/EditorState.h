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

class GameObject;


class EditorState : public GameState
{
  public:
    
    enum ListType{ NONE, CREATURES, PLATFORMS }; // To know wich one that is selected
    enum Tool{ADD, MARK, COPY, MOVE};
    
    ~EditorState();
    
    void Init();
    void Clean();
    
    void Pause();
    void Resume();
    
    void HandleEvents(Game* game);
    void Update(Game* game);
    void Draw(Game* game, Renderer* renderer);
    
    void DrawStaticMenu(Renderer* renderer);
    void DrawCurrentObjectList(Renderer* renderer);
    
    int GetButtonSize(int width, int height, int tileCount);
    
    static EditorState* Instance()
    {
      return &m_EditorState;
    }
  protected:
    
    EditorState();
    
  private:
    static EditorState m_EditorState;
    
    ListType m_selected_list;
    Tool m_selected_tool;
    
    Rect m_toolBox;
    std::vector< std::pair< Rect, Tool > > m_toolBoxes;
    
    Rect m_listBox;
    std::vector< std::pair<Rect, GameObject*> >m_ListBoxes;
    
    Rect m_currentWindowSize;
    Rect m_backgoundBox;
    
    const int m_listColumns{3};
    const int m_listRows{12};
    std::vector<Point> m_objListButtonPos;
};

#endif