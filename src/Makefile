
CCC = g++ -std=c++11
FLAGS = -pedantic -w
SDL_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

OFILES = Game.o Renderer.o PlayState.o PauseState.o MenuState.o Input.o Collision.o Level.o GameObject.o MovingGameObject.o StaticGameObject.o Player.o Platform.o Enemy.o

all: main.cc $(OFILES)
	# Linking...
	@ $(CCC) $(FLAGS) -o theGame main.cc $(OFILES) $(SDL_FLAGS)
	# Build successful!

Renderer.o: Renderer.cc Renderer.h Rect.h Constants.h
	# Compiling $<...
	@ $(CCC) $(FLAGS) -c Renderer.cc $<

Input.o: Input.cc Input.h Rect.h Constants.h InputDefinition.h
	# Compiling $<...
	@ $(CCC) $(FLAGS) -c Input.cc $<
	
Game.o: Game.cc Game.h Rect.h Constants.h
	# Compiling $<...
	@ $(CCC) $(FLAGS) -c Game.cc $<
	
PlayState.o: PlayState.cc PlayState.h GameState.h Rect.h Constants.h
	# Compiling $<...
	@ $(CCC) $(FLAGS) -c PlayState.cc $<
	
PauseState.o: PauseState.cc PauseState.h GameState.h Rect.h Constants.h
	# Compiling $<...
	@ $(CCC) $(FLAGS) -c PauseState.cc $<
	
MenuState.o: MenuState.cc MenuState.h GameState.h Rect.h Constants.h
	# Compiling $<...
	@ $(CCC) $(FLAGS) -c MenuState.cc $<
      
Level.o: Level.cc Level.h Rect.h Constants.h
	# Compiling $<...
	@ $(CCC) $(FLAGS) -c Level.cc $<
	
Collision.o: Collision.cc Collision.h Rect.h Constants.h
	# Compiling $<...
	@ $(CCC) $(FLAGS) -c Collision.cc $<
	
GameObject.o: gameobjects/GameObject.cc gameobjects/GameObject.h Rect.h Constants.h
	# Compiling $<...
	@ $(CCC) $(FLAGS) -c gameobjects/GameObject.cc $<

MovingGameObject.o: gameobjects/MovingGameObject.cc gameobjects/MovingGameObject.h Rect.h Constants.h
	# Compiling $<...
	@ $(CCC) $(FLAGS) -c gameobjects/MovingGameObject.cc $<
	
StaticGameObject.o: gameobjects/StaticGameObject.cc gameobjects/StaticGameObject.h Rect.h Constants.h
	# Compiling $<...
	@ $(CCC) $(FLAGS) -c gameobjects/StaticGameObject.cc $<
	
Player.o: gameobjects/Player.cc gameobjects/Player.h Rect.h Constants.h
	# Compiling $<...
	@ $(CCC) $(FLAGS) -c gameobjects/Player.cc $<
	
Enemy.o: gameobjects/Enemy.cc gameobjects/Enemy.h Rect.h Constants.h
	# Compiling $<...
	@ $(CCC) $(FLAGS) -c gameobjects/Enemy.cc $<
	
Platform.o: gameobjects/Platform.cc gameobjects/Platform.h Rect.h Constants.h
	# Compiling $<...
	@ $(CCC) $(FLAGS) -c gameobjects/Platform.cc $<
	
clean:
	# Cleaning...
	@ \rm -rf *.o *.gch core theGame *~
	# Cleaning successful!