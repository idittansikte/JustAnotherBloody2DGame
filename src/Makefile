
CCC = g++ -std=c++11

FLAGS = -pedantic -w

SDL_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

OFILES = Renderer.o Game.o PlayState.o PauseState.o MenuState.o GameObject.o Player.o Platform.o Level.o MovingGameObject.o StaticGameObject.o Collision.o Input.o

all: main.cc $(OFILES)
	$(CCC) $(FLAGS) -o theGame main.cc $(OFILES) $(SDL_FLAGS)

Renderer.o: Renderer.cc Renderer.h Rect.h Constants.h
	$(CCC) $(FLAGS) -c Renderer.cc

Input.o: Input.cc Input.h Rect.h Constants.h InputDefinition.h
	$(CCC) $(FLAGS) -c Input.cc
	
Game.o: Game.cc Game.h Rect.h Constants.h
	$(CCC) $(FLAGS) -c Game.cc
	
PlayState.o: PlayState.cc PlayState.h GameState.h Rect.h Constants.h
	$(CCC) $(FLAGS) -c PlayState.cc
	
PauseState.o: PauseState.cc PauseState.h GameState.h Rect.h Constants.h
	$(CCC) $(FLAGS) -c PauseState.cc
	
MenuState.o: MenuState.cc MenuState.h GameState.h Rect.h Constants.h
	$(CCC) $(FLAGS) -c MenuState.cc
	
GameObject.o: GameObject.cc GameObject.h Rect.h Constants.h
	$(CCC) $(FLAGS) -c GameObject.cc
	
Player.o: Player.cc Player.h Rect.h Constants.h
	$(CCC) $(FLAGS) -c Player.cc
	
Platform.o: Platform.cc Platform.h Rect.h Constants.h
	$(CCC) $(FLAGS) -c Platform.cc
	
Level.o: Level.cc Level.h Rect.h Constants.h
	$(CCC) $(FLAGS) -c Level.cc

MovingGameObject.o: MovingGameObject.cc MovingGameObject.h Rect.h Constants.h
	$(CCC) $(FLAGS) -c MovingGameObject.cc
	
StaticGameObject.o: StaticGameObject.cc StaticGameObject.h Rect.h Constants.h
	$(CCC) $(FLAGS) -c StaticGameObject.cc
	
Collision.o: Collision.cc Collision.h Rect.h Constants.h
	$(CCC) $(FLAGS) -c Collision.cc
	
clean:
	@ \rm -rf *.o *.gch core theGame *~