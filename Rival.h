using namespace std;
#include <string>

#include "GameObject.h"
#include "Point2D.h"
#include "BattleArena.h"

#ifndef RIVAL_H
#define RIVAL_H

//Setup states specified in Update
enum RivalStates{
    ALIVE_RIVAL = 0,
    FAINTED_RIVAL = 1
};

//Forward Declaration:
class Model;

class Rival : public GameObject
{
public:
    //Constructors / Destructors
    Rival(string, double, double, double, double, double, int, Point2D);
        
    //Public Member Functions
    void TakeHit(int, int, int);
    double get_phys_dmg();
    double get_magic_dmg();
    double get_defense();
    double get_health();
    bool Update();
    void ShowStatus();
    bool IsAlive(); //Suppossed to exist based on instructions for pokemon
    string get_name();
    bool ShouldBeVisible();
    
    //Added for functionality for removing or adding rivals to a given arena
    void set_current_arena(BattleArena*);
    BattleArena* get_current_arena();
    
    //Extra Credit Save/Restore functions
    void save(ofstream& file);
	void restore(ifstream& file, Model& model);
    
protected:
    //Protected Member Variables
    double health;
    double physical_damage;
    double magical_damage;
    double defense;
    double stamina_cost_per_fight;
    bool is_in_arena;
	BattleArena* current_arena;

    //Variables implied by constructor but not stated
    string name;
    double speed;
};

#endif
