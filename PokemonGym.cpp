using namespace std;
#include "Point2D.h"
#include "Building.h"
#include "PokemonGym.h"
#include "Model.h"
#include <iostream>
#include <fstream>

//Defualt Constructor
Point2D default_location;
PokemonGym::PokemonGym():Building('G', 1, default_location)
{
	state = NOT_BEATEN;
	max_number_of_training_units = 10;
	num_training_units_remaining = max_number_of_training_units;
	stamina_cost_per_training_unit = 1;
	dollar_cost_per_training_unit = 1.0;
	experience_points_per_training_unit = 2;
	cout << "PokemonGym default constructed" << endl;
}

//Constructor
PokemonGym::PokemonGym(unsigned int max_training_units, unsigned int stamina_cost, double dollar_cost, 
					   unsigned int exp_points_per_training_unit, int in_id, Point2D in_loc):Building('G', in_id, in_loc)
{
	state = NOT_BEATEN;	
	max_number_of_training_units = max_training_units;
	stamina_cost_per_training_unit = stamina_cost;
	experience_points_per_training_unit = exp_points_per_training_unit;
	dollar_cost_per_training_unit = dollar_cost;
	num_training_units_remaining = max_training_units;
	cout << "PokemonGym constructed" << endl;
}

//Destructor that prints
PokemonGym::~PokemonGym()
{
	cout << "PokemonGym destructed" << endl;
}

//Public Member Functions:

//Returns the cost of purchasing unit_qty training units
double PokemonGym::GetDollarCost(unsigned int unit_qty)
{
	return dollar_cost_per_training_unit * unit_qty;
}

//Returns the amount of stamina required for unit_qty training_units	
unsigned int PokemonGym::GetStaminaCost(unsigned int unit_qty)
{
	return stamina_cost_per_training_unit * unit_qty;
}

//Returns the number of training units remaining in this Pokemon Gym
unsigned int PokemonGym::GetNumTrainingUnitsRemaining()
{
	return num_training_units_remaining;
}

//Returns true if a Pokemon with a given budget and stamina can request to train unit_qty training units
bool PokemonGym::IsAbleToTrain(unsigned int unit_qty, double budget, unsigned int stamina)
{
	if ( stamina >= PokemonGym::GetStaminaCost(unit_qty) && budget >= PokemonGym::GetDollarCost(unit_qty))
		return true;
		
	return false;
}

//Returns experience points based on whether or not you can train
unsigned int PokemonGym::TrainPokemon(unsigned int training_units)
{
	if (num_training_units_remaining >= training_units)
	{
		num_training_units_remaining -= training_units;
	}
	else
	{
		training_units = num_training_units_remaining;
		num_training_units_remaining = 0;
	}

	return experience_points_per_training_unit * training_units;
}

//Tell you whether the PokemonGym has been beaten, return true if beaten
bool PokemonGym::IsBeaten()
{
	if (num_training_units_remaining <= 0)
		return true;
	
	return false;
}

//Updates the status of the PokemonGym and whether or not it has been beaten
bool PokemonGym::Update()
{
	static bool first_time = 0;//Used so that Update only returns true once
	
	if (PokemonGym::IsBeaten() )
	{
		state = BEATEN;
		display_code - 'g';
		cout << display_code << id_num << " has been beaten." << endl;
		first_time = 1; 
		return true;
	}
	
	return false;
}

void PokemonGym::ShowStatus()
{
	//Call building show status function
	cout << "Pokemon Gym Status: ";
	Building::ShowStatus();

	//print out remaining variables
	cout << "	Max number of training units: " << max_number_of_training_units << endl;
	cout << "	Stamina cost per training unit: " << stamina_cost_per_training_unit << endl;
	cout << "	Pokemon dollar per training unit: " << dollar_cost_per_training_unit << endl;
	cout << "	Experience points per training unit: " << experience_points_per_training_unit << endl;
	if (num_training_units_remaining == 1)
		cout << "	" << num_training_units_remaining << " training unit are remaining for this gym" << endl;
	else
		cout << "	" << num_training_units_remaining << " training units are remaining for this gym" << endl;

}
	
//Saves the game
void PokemonGym::save(ofstream& file)
{
	if (file.is_open())
	{
		//First call Building's save function
		Building::save(file);

		//Copy the normal member variables
		file << num_training_units_remaining << endl;
		file << max_number_of_training_units << endl;
		file << stamina_cost_per_training_unit << endl;
		file << dollar_cost_per_training_unit << endl;
		file << experience_points_per_training_unit << endl;
	}
	return;
}

//Restores the game from the save
void PokemonGym::restore(ifstream& file, Model& model)
{
	return;
}