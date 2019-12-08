using namespace std;
#include <string>

#include "GameObject.h"
#include "Point2D.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Rival.h"
#include "BattleArena.h"
#include "Attack_Types.h"

#ifndef POKEMON_H
#define POKEMON_H

//Enumerated States
enum PokemonStates {
    STOPPED             = 0,
    MOVING              = 1,
    EXHAUSTED           = 2,
    IN_GYM              = 3,
    IN_CENTER           = 4,
    MOVING_TO_GYM       = 5,
    MOVING_TO_CENTER    = 6,
    TRAINING_IN_GYM     = 7,
    RECOVERING_STAMINA  = 8,
    IN_ARENA            = 9,
    MOVING_TO_ARENA     = 10,
    BATTLE              = 11,
    FAINTED             = 12
};

//Forward Declaration:
class Model;

class Pokemon : public GameObject
{
public:
    //Constructors/Destructors
    Pokemon();
    Pokemon(char);
    Pokemon(string, double, double, double, double, double, int, char, Point2D);
    ~Pokemon();

    //Public Member Functions
    void StartMoving(Point2D);
    void StartMovingToCenter(PokemonCenter*);
    void StartMovingToGym(PokemonGym*);
    void StartTraining(unsigned int);
    void StartRecoveringStamina(unsigned int);
    void Stop();
    bool IsExhausted();
    bool ShouldBeVisible();
    void ShowStatus();
    bool Update();

    //Things I added for program functionallity
    string GetName();

    //New PA4 public members
    bool IsAlive();
    void TakeHit(double defense, Attack_Types& attack_choice); //changed for extra credit
    bool ReadyBattle(Rival* in_target); //Purposely changed to bool to check if successful in game command
    bool StartBattle();
    void StartMovingToArena(BattleArena*);

    //Extra Credit Save/Restore functions
    void save(ofstream& file);
	void restore(ifstream& file, Model& model);

    //Extra Credit ASCII print function
    void printBattlePokemon();
    void printPokemon();

protected:
    //Protected Member Functions
    bool UpdateLocation();
    void SetupDestination(Point2D);

    //PA4 protected member additions
    double health;
    double store_health;
    double physical_damage;
    double magical_damage;
    double defense;
    Rival* target;
    bool is_in_arena;
    BattleArena* current_arena;

private:
    //Private Member Variables
    double speed;
    bool is_in_gym;
    bool is_in_center;
    unsigned int stamina;
    unsigned int experience_points;
    double pokemon_dollars;
    unsigned int training_units_to_buy;
    unsigned int stamina_points_to_buy;
    string name;
    PokemonCenter* current_center;
    PokemonGym* current_gym;
    Point2D destination;
    Vector2D delta;

    //Extra Credit Attack List
    Attack_Types attack_list[2];
};

//Non Member Function
double GetRandomAmountOfPokemonDollars();

#endif
