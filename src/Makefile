
CCC = g++ -std=c++11

FLAGS = -pedantic -w

SDL_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

OFILES = Renderer.o Game.o PlayState.o PauseState.o MenuState.o GameObject.o Player.o Level.o

all: main.cc $(OFILES)
	$(CCC) $(FLAGS) -o theGame main.cc $(OFILES) $(SDL_FLAGS)

Renderer.o: Renderer.cc Renderer.h Rect.h Constants.h
	$(CCC) $(FLAGS) -c Renderer.cc
	
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
	
Level.o: Level.cc Level.h Rect.h Constants.h
	$(CCC) $(FLAGS) -c Level.cc

clean:
	@ \rm -rf *.o *.gch core theGame *~