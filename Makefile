GCC = g++ -std=c++11 -g

OBJS = main.o Point2D.o Vector2D.o GameObject.o Building.o PokemonCenter.o PokemonGym.o Pokemon.o Model.o GameCommand.o View.o Rival.o BattleArena.o Attack_Types.o
HEADS = Point2D.h Vector2D.h GameObject.h Building.h PokemonCenter.h PokemonGym.h Pokemon.h Model.h GameCommand.h View.h Rival.h BattleArena.h Input_Handling.h Attack_Types.h

default: PA4

PA4: $(OBJS)
	$(GCC) -o PA4 $(OBJS)

main.o: main.cpp $(HEADS)
	$(GCC) -c main.cpp -o main.o 
	
Point2D.o: Point2D.h Point2D.cpp Vector2D.h
	$(GCC) -c Point2D.cpp -o Point2D.o

Vector2D.o: Vector2D.cpp Vector2D.h
	$(GCC) -c Vector2D.cpp -o Vector2D.o

GameObject.o: GameObject.cpp GameObject.h Point2D.h Vector2D.h Model.h
	$(GCC) -c GameObject.cpp -o GameObject.o
	
Building.o: Building.cpp Building.h GameObject.h Point2D.h Model.h
	$(GCC) -c Building.cpp -o Building.o

PokemonCenter.o: PokemonCenter.cpp PokemonCenter.h Building.h GameObject.h Point2D.h Model.h
	$(GCC) -c PokemonCenter.cpp -o PokemonCenter.o

PokemonGym.o: PokemonGym.cpp PokemonGym.h Building.h GameObject.h Point2D.h Model.h
	$(GCC) -c PokemonGym.cpp -o PokemonGym.o

Pokemon.o: Pokemon.cpp PokemonGym.h GameObject.h Point2D.h PokemonCenter.h Pokemon.h Model.h
	$(GCC) -c Pokemon.cpp -o Pokemon.o

Model.o: Model.cpp Model.h Pokemon.h PokemonGym.h PokemonCenter.h View.h GameObject.h Point2D.h
	$(GCC) -c Model.cpp -o Model.o	

GameCommand.o: GameCommand.cpp GameCommand.h Model.h Point2D.h View.h 
	$(GCC) -c GameCommand.cpp -o GameCommand.o

View.o: View.cpp View.h Point2D.h GameObject.h
	$(GCC) -c View.cpp -o View.o

Rival.o: Rival.cpp Rival.h GameObject.h Point2D.h Model.h
	$(GCC) -c Rival.cpp -o Rival.o

BattleArena.o: BattleArena.cpp BattleArena.h Building.h Point2D.h GameObject.h Model.h
	$(GCC) -c BattleArena.cpp -o BattleArena.o

Attack_Types.o: Attack_Types.cpp Attack_Types.h
	$(GCC) -c Attack_Types.cpp -o Attack_Types.o	

clean: 
	rm $(OBJS) PA4
