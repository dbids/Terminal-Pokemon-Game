using namespace std;
#include "Pokemon.h"
#include "PokemonGym.h"
#include "PokemonCenter.h"
#include "View.h"
#include "GameObject.h"
#include "Point2D.h"
#include "Rival.h"
#include "BattleArena.h"

#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <list>

class Model
{
public:
	// Constructors/Destructors
  	Model();
  	~Model();

	//Public member functions
  	Pokemon* GetPokemonPtr(int id);
  	PokemonCenter* GetPokemonCenterPtr(int id);
  	PokemonGym* GetPokemonGymPtr(int id);
	Rival* GetRivalPtr(int id);
  	bool Update();
  	void Display(View& view);
  	void ShowStatus();
	BattleArena* GetArenaPtr(int id);

	//Part 5 of PA4
	void NewCommand(char type, int id_num, Point2D location);
 
private:
  	int time;
  	list <GameObject*> object_ptrs;
	list <GameObject*> active_ptrs;
  	list <Pokemon*> pokemon_ptrs;
  	list <PokemonCenter*> center_ptrs;
  	list <PokemonGym*> gym_ptrs;
	list<Rival*> rival_ptrs;
	list <BattleArena*> arena_ptrs;

	//Private Copy Constructor
	Model(const Model&);
};

#endif // MODEL_H
