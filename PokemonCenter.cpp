using namespace std;
#include "PokemonCenter.h"
#include "Point2D.h"
#include "Building.h"
#include "GameObject.h"
#include <iostream>
#include <fstream>
#include "Model.h"

//Define the default constructor for PokemonCenter with inherited values from Building
Point2D default_loc;
PokemonCenter :: PokemonCenter() : Building('C', 1, default_loc)
{
	stamina_capacity = 100;
	num_stamina_points_remaining = stamina_capacity;
	dollar_cost_per_stamina_point = 5;
	state = STAMINA_POINTS_AVAILABLE;
	cout << "PokemonCenter default constructed" << endl;
}

//Define the  constructor for PokemonCenter which takes the arguments in_id and in_loc
PokemonCenter :: PokemonCenter(int in_id, double stamina_cost, unsigned int stamina_cap, Point2D in_loc) : Building('C', in_id, in_loc)
{
	stamina_capacity = stamina_cap;
	num_stamina_points_remaining = stamina_capacity;
	dollar_cost_per_stamina_point = stamina_cost;
	state = STAMINA_POINTS_AVAILABLE;
	cout << "PokemonCenter constructed" << endl;
}

//Default Destructor which prints
PokemonCenter::~PokemonCenter()
{
	cout << "PokemonCenter destructed" << endl;
}

//Member function which returns true if this PokemonCenter contains at least one stamina point.
bool PokemonCenter::HasStaminaPoints()
{
	if (num_stamina_points_remaining > 0)
		return true;

	return false;
}

//Member function which returns the number of stamina points remaining in this Pokemon Center
unsigned int PokemonCenter::GetNumStaminaPointsRemaining()
{
	return num_stamina_points_remaining;
}

//Member function which returns true if this Pokemon can afford to purchase stamina_points with the given budget
bool PokemonCenter::CanAffordStaminaPoints(unsigned int stamina_points, double budget)
{
	if ((budget - GetDollarCost(stamina_points)) >= 0)
	{
		return true;
	}
		
	return false;
}

//Member function which returns the Pokemon dollar cost for the specified number of stamina points
double PokemonCenter::GetDollarCost(unsigned int stamina_points)
{
	return dollar_cost_per_stamina_point * stamina_points;
}

//Member function returns needed stamina points and removes that amount from the pokecenter
unsigned int PokemonCenter::DistributeStamina(unsigned int points_needed)
{
	if (num_stamina_points_remaining >= points_needed)
	{
		num_stamina_points_remaining -= points_needed;
	}
	else
	{
		points_needed = num_stamina_points_remaining; //Using the points_needed as a temp variable
		num_stamina_points_remaining = 0;
	}
	
	return points_needed;
}

//member function which changes display_code, state, prints and returns true if stamina is depleted, otherwise returns false
bool PokemonCenter::Update()
{
	static bool first_time = 0;//Used so that Update only returns true once

	if (num_stamina_points_remaining == 0 && !first_time)
	{
		state = NO_STAMINA_POINTS_AVAILABLE;
		display_code = 'c';
		cout << "PokemonCenter " << id_num << " has ran out of stamina points." << endl;
		first_time = 1; 
		return true;
	}
	return false; 
}

//Member function which displays the status of the PokemonCenter
void PokemonCenter::ShowStatus()
{
	//Calls the Building show status function
	cout << "Pokemon Center Status: ";
	Building::ShowStatus();

	//Prints the pokemon center specific information
	cout << "	Pokemon dollars per stamina point: " << dollar_cost_per_stamina_point << endl;
	cout << "	Has " << num_stamina_points_remaining << " stamina point(s) remaining." << endl;
}	

//Saves the game
void PokemonCenter::save(ofstream& file)
{
	if (file.is_open())
	{
		//First call Building's save function
		Building::save(file);

		//Copy the normal member variables
		file << stamina_capacity << endl;
		file << num_stamina_points_remaining << endl;
		file << dollar_cost_per_stamina_point << endl;
	}
	return;
}

//Restores the game from the save
void PokemonCenter::restore(ifstream& file, Model& model)
{
	//First restore the parent class
	Building::restore(file, model);

    string line;

    getline(file,line);
    stamina_capacity = stoul(line);
    getline(file,line);
    num_stamina_points_remaining = stoul(line);
    getline(file,line);
	dollar_cost_per_stamina_point = stod(line);
	
	return;
}