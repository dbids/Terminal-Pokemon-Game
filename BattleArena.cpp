using namespace std;
#include <iostream>
#include <fstream>
#include <string>

//User defined headers
#include "BattleArena.h"
#include "Building.h"
#include "Point2D.h"
#include "GameObject.h"
#include "Model.h"

//Constructors / Destructors
BattleArena::BattleArena():Building('A', 1, Point2D(0,0))
{
    max_num_rivals = 3;
    num_rivals_remaining = max_num_rivals;
    dollar_cost_per_fight = 4.0;
    stamina_cost_per_fight = 3;
    state = RIVALS_AVAILABLE;
    cout << "BattleArena default constructed" << endl;
}

BattleArena::BattleArena(unsigned int max_rivals, unsigned int stamina_cost,
 double dollar_cost, int in_id, Point2D in_loc):Building('A', in_id, in_loc)
{
    max_num_rivals = max_rivals;
    num_rivals_remaining = max_num_rivals;
    dollar_cost_per_fight = dollar_cost;
    stamina_cost_per_fight = stamina_cost;
    state = RIVALS_AVAILABLE;
    cout << "BattleArena constructed" << endl;
}

//Getter for the number of rivals remaining variable
unsigned int BattleArena::GetNumRivalsRemaining()
{
    return num_rivals_remaining;
}

//Returns true if there is at least one rival in the arena
bool BattleArena::HasEnoughRivals()
{
    if (num_rivals_remaining > 0)
    {
        return true;
    }

    return false;
}

//Getter for the dollar cost per fight variable
double BattleArena::GetDollarCost()
{
    return dollar_cost_per_fight;
}

//Getter for the stamina cost per fight variable
unsigned int BattleArena::GetStaminaCost()
{
    return stamina_cost_per_fight;
}

//Returns true if a pokemon is capable of fighting
bool BattleArena::IsAbleToFight(double budget, unsigned int stamina)
{
    if (budget > dollar_cost_per_fight && stamina > stamina_cost_per_fight)
	{
		return true;
	}
		
	return false;
}

//Returns true if there are no rivals remaining
bool BattleArena::IsBeaten()
{
    if (num_rivals_remaining == 0)
    {
        return true;
    }

    return false;
}

//ye old update function
bool BattleArena::Update()
{
    static bool first_time = 0;//Used so that Update only returns true once

    if (HasEnoughRivals() || first_time)
    {
        return false;
    }

    first_time = true;
    state = NO_RIVALS_AVAILABLE;
    cout << "All rivals in the arena have been defeated!!" << endl;
    display_code = 'a';
    return true;
}

//Show Status function
void BattleArena::ShowStatus()
{
    cout << "Battle Arena Status: ";
    Building::ShowStatus();
    cout << "	Max number of rivals: " << num_rivals_remaining << endl;
    cout << "	Stamina cost per fight: " << stamina_cost_per_fight << endl;
    cout << "	Pokemon dollar per fight: " << dollar_cost_per_fight << endl;
    cout << "	" << num_rivals_remaining << " rival(s) are remaining for this arena" << endl;
}

//Adds a rival to the battle arena
void BattleArena::AddOneRival()
{
	num_rivals_remaining++;
}

//Removes a rival from the battle arena
void BattleArena::RemoveOneRival()
{
	num_rivals_remaining--;
}

//Saves the game
void BattleArena::save(ofstream& file)
{
	if (file.is_open())
	{
		//First call Building's save function
		Building::save(file);

		//Copy the normal member variables
		file << max_num_rivals << endl;
		file << num_rivals_remaining << endl;
		file << dollar_cost_per_fight << endl;
        file << stamina_cost_per_fight << endl;
		file << pokemon_count << endl;
	}
	return;
}

//Restores the game from the save
void BattleArena::restore(ifstream& file, Model& model)
{
	string line;

    //First restore the parent class
	Building::restore(file, model);

    //Restore the state properly
    state = (state == '1') ? RIVALS_AVAILABLE : NO_RIVALS_AVAILABLE;

    getline(file,line);
    max_num_rivals = stoul(line);
    getline(file,line);
    num_rivals_remaining = stoul(line);
    getline(file,line);
    dollar_cost_per_fight = stod(line);
    getline(file,line);
    stamina_cost_per_fight = stoul(line);
    getline(file,line);
    pokemon_count = stoul(line);

    return;
}