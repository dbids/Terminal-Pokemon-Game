using namespace std;
#include <iostream>
#include "Point2D.h"
#include "Vector2D.h"
#include "GameObject.h"
#include "Model.h"
#include <fstream>
#include <string>

//First constructor which just takes an input code
GameObject::GameObject(char in_code)
{
	display_code = in_code;
	id_num = 1;
	state = 0;
	cout << "GameObject constructed" << endl;
}

//Second constructor which takes a Point2D, int, and char.  
//Note that this specifies location where the previous constructor does not
GameObject::GameObject(Point2D in_loc, int in_id, char in_code)
{
	display_code = in_code;
	id_num = in_id;
	location = in_loc;
	state = 0;
	cout << "GameObject constructed" << endl;
}

//Default destructor for Game Object that just prints
GameObject::~GameObject()
{
	cout << "GameObject destructed" << endl;
}

//Defines the member function GetLocation() which returns the current location
Point2D GameObject::GetLocation()
{
	return location;
}

//Defines the member function GetId which returns the current id_num;
int GameObject::GetId()
{
	return id_num;
}

//Defines the member function GetState which returns the current state
char GameObject::GetState()
{
	return state;
}

//Defines the member function ShowStatus() which outputs the objects current information
void GameObject::ShowStatus()
{
	cout << display_code << id_num << " at " << location;

	return;
}

//Additional getter I use in the GameCommand class for the DoStopCommand function
char GameObject::GetDisplayCode()
{
	return display_code;
}

//Draw self function tells the view class the display_code and id_num
void GameObject::DrawSelf(char* ptr)
{
	*ptr = display_code;
	*(ptr + 1) = id_num + 48; //add 48 for ascii encoding

	return;
}

//Define IsAlive() as true unless overwritten
bool GameObject::IsAlive()
{
	return true;
}

//Saves the game object members
void GameObject::save(ofstream& file)
{
	file << "......" << endl; //deliniate different game objects
	file << location.x << endl;
	file << location.y << endl;
	file << id_num << endl;;
	file << display_code << endl;
	file << static_cast<int>(state) << endl;
}

//Restores the game from the save
void GameObject::restore(ifstream& file, Model& model)
{
	string line;
	getline(file,line);
	getline(file,line);
	location.x = stod(line);
	getline(file,line);
	location.y = stod(line);
	getline(file,line);
	id_num = stoi(line);
	getline(file,line);
	display_code = line[0];
	getline(file,line);
	state = line[0];
}