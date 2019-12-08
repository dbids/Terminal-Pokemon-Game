using namespace std;
#include "Building.h"
#include "GameObject.h"
#include "Point2D.h"
#include "Model.h"
#include <iostream>
#include <fstream>
#include <string>

//Create the default constructor with all of the default values for the member variables including those inherited from GameObject
Building::Building():GameObject('B')
{	
	pokemon_count = 0;
	cout << "Building default constructed" << endl;
}

//Constructor which takes in the display_code, id_num, and location
Building::Building(char in_code, int in_id, Point2D in_loc):GameObject(in_loc, in_id, in_code)
{
	pokemon_count = 0;
	cout << "Building constructed" << endl;
}

//Building Destructor
Building::~Building() {
    cout << "Building destructed" << endl;
}

//Member function which adds 1 to pokemon_count
void Building::AddOnePokemon()
{
	pokemon_count++;
}

//Member function which subtracts 1 from pokemon_count
void Building::RemoveOnePokemon()
{
	if (pokemon_count > 0)	
		pokemon_count--;
	else
		cout << "Error : Pokemon count cannot be negative" << endl;
}

//Member function which diplays the status of the building including inherited variables
void Building::ShowStatus() 
{
	cout << display_code << id_num << " located at " << location << endl;
	cout << "	";
	if (pokemon_count == 1) //These are the conditions for the singular verb 'is'
		cout << pokemon_count << " pokemon is in this building" << endl;
	else //Zero and anything greater than 1 should use 'are'
		cout << pokemon_count << " pokemon are in this building" << endl;
}

//Member function which always returns true because buildings are always visable
bool Building::ShouldBeVisible()
{
	return true;
}

//Saves the game
void Building::save(ofstream& file)
{
	if (file.is_open())
	{
		//First call GameObjects save function
		GameObject::save(file);

		//Copy the normal member variables
		file << pokemon_count << endl;
	}
	return;
}

//Restores the game from the save
void Building::restore(ifstream& file, Model& model)
{
	GameObject::restore(file, model);
	string line;
	getline(file, line);
	pokemon_count = stoul(line);
	return;
}