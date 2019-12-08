using namespace std;
#include "Point2D.h"
#include "Building.h"

#ifndef POKEMON_GYM_H
#define POKEMON_GYM_H

//Forward Declaration:
class Model;

class PokemonGym : public Building
{
public:
	//Destructors/Constructors
	PokemonGym();
	PokemonGym(unsigned int, unsigned int, double, unsigned int, int, Point2D);
	~PokemonGym();

	//Public Member Functions
	double GetDollarCost(unsigned int unit_qty);
	unsigned int GetStaminaCost(unsigned int unit_qty);
	unsigned int GetNumTrainingUnitsRemaining();
	bool IsAbleToTrain(unsigned int unit_qty, double budget, unsigned int stamina);
	unsigned int TrainPokemon(unsigned int training_units);
	bool Update();
	bool IsBeaten();
	void ShowStatus();

	//Extra Credit Save/Restore functions
	void save(ofstream& file);
	void restore(ifstream& file, Model& model);

private:
	//Private Member Variables
	unsigned int num_training_units_remaining;
	unsigned int max_number_of_training_units;
	unsigned int stamina_cost_per_training_unit;
	double dollar_cost_per_training_unit;
	unsigned int experience_points_per_training_unit;
};

//State Machine Enums
enum PokemonGymStates {
	NOT_BEATEN  = 0,
	BEATEN      = 1
};

#endif
