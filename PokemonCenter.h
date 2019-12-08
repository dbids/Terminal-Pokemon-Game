using namespace std;
#include "Point2D.h"
#include "Building.h"

#ifndef POKEMON_CENTER_H
#define POKEMON_CENTER_H

//Forward Declaration:
class Model;

class PokemonCenter: public Building
{
public:
	//Constructors/ Destructors
	PokemonCenter();
	PokemonCenter(int, double, unsigned int, Point2D);
	~PokemonCenter();

	//Public Member Functions
	bool HasStaminaPoints();
	unsigned int GetNumStaminaPointsRemaining();
	bool CanAffordStaminaPoints(unsigned int, double );
	double GetDollarCost(unsigned int);
	unsigned int DistributeStamina(unsigned int);
	bool Update();
	void ShowStatus();

	//Extra Credit Save/Restore functions
	void save(ofstream& file);
	void restore(ifstream& file, Model& model);
	
private:
	//Private Member Variables
	unsigned int stamina_capacity;
	unsigned int num_stamina_points_remaining;
	double dollar_cost_per_stamina_point;
};

//Enumerated States
enum PokemonCenterStates {
	STAMINA_POINTS_AVAILABLE = 0,
	NO_STAMINA_POINTS_AVAILABLE = 1
};

#endif
