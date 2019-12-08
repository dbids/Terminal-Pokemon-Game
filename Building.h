using namespace std;
#include "Point2D.h"
#include "GameObject.h"

#ifndef BUILDING_H
#define BUILDING_H

//Forward Declaration:
class Model;

class Building: public GameObject
{
public:	
	//Constructors
	Building();
	Building(char, int, Point2D);
	~Building();
	
	//Public Member Functions
	void AddOnePokemon();
	void RemoveOnePokemon();
	void ShowStatus();
	bool ShouldBeVisible();

	//Extra Credit Save/Restore functions
	void save(ofstream& file);
	void restore(ifstream& file, Model& model);

//Private member variables
private:
	unsigned int pokemon_count;
};

#endif
