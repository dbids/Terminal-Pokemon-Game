using namespace std;
#include "Building.h"
#include "Point2D.h"

#ifndef BATTLE_ARENA_H
#define BATTLE_ARENA_H

enum BattleArenaStates{
    RIVALS_AVAILABLE = 0,
    NO_RIVALS_AVAILABLE = 1
};

//Forward Declaration:
class Model;

class BattleArena : public Building
{
public:
    //Constructors / Destructors
    BattleArena();
    BattleArena(unsigned int, unsigned int, double, int, Point2D);

    //Public Member Functions
    unsigned int GetNumRivalsRemaining();
    bool HasEnoughRivals();
    double GetDollarCost();
    unsigned int GetStaminaCost();
    bool IsAbleToFight(double, unsigned int);
    bool Update();
    bool IsBeaten();
    void ShowStatus();
	void AddOneRival();
	void RemoveOneRival();

    //Extra Credit Save/Restore functions
	void save(ofstream& file);
	void restore(ifstream& file, Model& model);
    
private:
    //Private Member Variables
    unsigned int max_num_rivals;
    unsigned int num_rivals_remaining;
    double dollar_cost_per_fight;
    unsigned int stamina_cost_per_fight;
    unsigned int pokemon_count;
};

#endif
