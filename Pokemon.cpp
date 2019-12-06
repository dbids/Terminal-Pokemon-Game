using namespace std;
#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <typeinfo>
#include <string>

//User defined headers
#include "Pokemon.h"
#include "GameObject.h"
#include "Point2D.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Rival.h"
#include "BattleArena.h"

Pokemon::Pokemon():GameObject('p')
{
    speed = 5.0;
    std::cout << "Pokemon default constructed" << endl;
	state = STOPPED;

	//Default values from later down in the doc
	is_in_gym = 0;
	is_in_center = 0;
	stamina = 20;
	experience_points = 0;
	pokemon_dollars = 0;
	training_units_to_buy = 0;
	stamina_points_to_buy = 0;
	name = typeid(Pokemon).name();
	current_center = NULL;
	current_gym = NULL;
	delta;

	//New PA4 default values
	health = 20;
	store_health = health;
	physical_damage = 5;
	magical_damage = 4;
	defense = 0;
	is_in_arena = 0;
	target = NULL;
	current_arena = NULL;
}

Pokemon::Pokemon(char in_code):GameObject(in_code)
{
    speed = 5;
    cout << "Pokemon constructed" << endl;
    state = STOPPED;

	//Default values from later down in the doc
	is_in_gym = 0;
	is_in_center = 0;
	stamina = 20;
	experience_points = 0;
	pokemon_dollars = 0;
	training_units_to_buy = 0;
	stamina_points_to_buy = 0;
	current_center = NULL;
	current_gym = NULL;
	delta;
	
	//Define the name as Pokemon (in_code)
	string name(1, in_code);
	name = typeid(Pokemon).name() + name;
	this->name = name;

	//New PA4 default values
	health = 20;
	store_health = health;
	physical_damage = 5;
	magical_damage = 4;
	defense = 0;
	is_in_arena = 0;
	target = NULL;
	current_arena = NULL;
}

Pokemon::Pokemon(string in_name, double in_speed, double hp, double phys_dmg, 
				double magic_dmg, double def, int in_id, char in_code, Point2D in_loc)
:GameObject(in_loc, in_id, in_code)
{
    speed = in_speed;
    name = in_name;
    cout << "Pokemon constructed" << endl;
	state = STOPPED;

	//Default values from later down in the doc
	is_in_gym = 0;
	is_in_center = 0;
	stamina = 20;
	experience_points = 0;
	pokemon_dollars = 0;
	training_units_to_buy = 0;
	stamina_points_to_buy = 0;
	current_center = NULL;
	current_gym = NULL;
	delta;

	//New PA4 default values
	health = hp;
	store_health = health;
	physical_damage = phys_dmg;
	magical_damage = magic_dmg;
	defense = def;
	is_in_arena = 0;
	target = NULL;
	current_arena = NULL;
}

//Default constructor which prints
Pokemon::~Pokemon()
{
	cout << "Pokemon destructed" << endl;
}

//Member function which tells the pokemon to start moving
void Pokemon::StartMoving(Point2D dest)
{	
	//isThere bool used to test if the Pokemon is already there with similar methodology to UpdateLocation()
	bool isThere = (fabs(destination.x - location.x) == fabs(delta.x)) && 
				   (fabs(destination.y - location.y) == fabs(delta.y));
	
    if (isThere)
	{
        cout << display_code << id_num << ": I'm already there. See?" << endl;
	}
    else if (IsExhausted())
	{
        cout << display_code << id_num << ": I am exhausted. I may move but you cannot see me." << endl;
	}
    else
	{
		//If leaving a gym, center, or arena act accordingly
		if (is_in_center) 
		{
            current_center->RemoveOnePokemon(); // handles corner case
            is_in_center = false;
        } 
		else if (is_in_gym) 
		{
            current_gym->RemoveOnePokemon();
            is_in_gym = false;
        }
		else if(is_in_arena)
		{
			current_arena->RemoveOnePokemon();
			is_in_arena = false;
		}
        cout << display_code << id_num << ": On my way." << endl;
		state = MOVING;
		SetupDestination(dest);
	}
}

//Member function which tells a pokemon to start moving towards a Pokemon Center
void Pokemon::StartMovingToCenter(PokemonCenter* center)
{
//isThere bool used to test if the Pokemon is already there with similar methodology to UpdateLocation()
bool isThere = (fabs(destination.x - location.x) == fabs(delta.x)) && 
			   (fabs(destination.y - location.y) == fabs(delta.y));

     if (isThere)
        cout << display_code << id_num << ": I am already at the Pokemon Center!" << endl;
    else if (IsExhausted())
        cout << display_code << id_num << ": I am exhausted so I can't move to recover stamina..." << endl;
    else
	{
		//If leaving a gym, center, or arena act accordingly
		if (is_in_center) 
		{
            current_center->RemoveOnePokemon(); // handles corner case
            is_in_center = false;
        } 
		else if (is_in_gym) 
		{
            current_gym->RemoveOnePokemon();
            is_in_gym = false;
        }
		else if(is_in_arena)
		{
			current_arena->RemoveOnePokemon();
			is_in_arena = false;
		}
		current_center = center;
		SetupDestination(current_center->GetLocation());
		state = MOVING_TO_CENTER;
		cout << display_code << id_num << ": on my way to center " << center->GetId() << "." << endl;
	}
        
}

//Member function which tells a pokemon to start moving towards a Pokemon Gym
void Pokemon::StartMovingToGym(PokemonGym* gym)
{	
//isThere bool used to test if the Pokemon is already there with similar methodology to UpdateLocation()
bool isThere = (fabs(destination.x - location.x) == fabs(delta.x)) && 
			   (fabs(destination.y - location.y) == fabs(delta.y));

    if (isThere)
        cout << display_code << id_num << ": I am already at the Pokemon Gym!" << endl;
    else if (IsExhausted())
        cout << display_code << id_num << ": I am exhausted so I shouldn't be going to the gym..." << endl;
    else
	{
		//If leaving a gym, center, or arena act accordingly
		if (is_in_center) 
		{
            current_center->RemoveOnePokemon(); // handles corner case
            is_in_center = false;
        } 
		else if (is_in_gym) 
		{
            current_gym->RemoveOnePokemon();
            is_in_gym = false;
        }
		else if(is_in_arena)
		{
			current_arena->RemoveOnePokemon();
			is_in_arena = false;
		}
		current_gym = gym;
		SetupDestination(current_gym->GetLocation());
		state = MOVING_TO_GYM;
		cout << display_code << id_num << ": On my way to the gym " << gym->GetId() << "." << endl;
	}
}

//Member function which tells a pokemon to start training num_training_units
void Pokemon::StartTraining(unsigned int num_training_units)
{
	if (IsExhausted())
	{
		cout << display_code << id_num << ": I am exhausted so no more training for me..." << endl;
		return;
	}
	else if (!(state == IN_GYM || state == TRAINING_IN_GYM))
	{	
		cout << display_code << id_num << ": I can only train in a Pokemon Gym!" << endl;
		return;
	}
	else if (!(current_gym->IsAbleToTrain(num_training_units, pokemon_dollars, stamina)))
	{
		cout << display_code << id_num << ": Not enough stamina and/or money for training." << endl;
	return;
	}	
	else if (current_gym->IsBeaten())
	{
		cout << display_code << id_num << ": Cannot train! This Pokemon Gym is already beaten" << endl;
		return;
	}
	else
	{
		state = TRAINING_IN_GYM;
		
		// Set its training_units_to_buy to the minimum of the requested training units and the remaining training units in the gym
		training_units_to_buy = (current_gym->GetNumTrainingUnitsRemaining() > num_training_units) ? num_training_units : 
		current_gym->GetNumTrainingUnitsRemaining();

		cout << display_code << id_num << ": Started to train at Pokemon Gym " << current_gym->GetId() << " with " << training_units_to_buy
			 << " training units." << endl;
	}
	
	return;
}

//Member function which tells the Pokemon to start recovering at a Pokemon Center
void Pokemon::StartRecoveringStamina(unsigned int num_stamina_points)
{
	if (!(pokemon_dollars >= current_center->GetDollarCost(num_stamina_points)))
		cout << display_code << id_num << ": Not enough money to recover stamina." << endl;
	else if (!(current_center->HasStaminaPoints()))
		cout << display_code << id_num << ": Cannot recover! No stamina points remaining in this Pokemon Center!" << endl;
	else if (state == IN_CENTER || state == RECOVERING_STAMINA)
		cout << display_code << id_num << ": I can only recover stamina at a Pokemon Center!" << endl;
	else
	{
		state = RECOVERING_STAMINA;
		cout << display_code << id_num << ": Started recovering " << stamina << " stamina point(s) at Pokemon Center " << current_center->GetId() <<"." << endl;
		
		// Set its stamina_units_to_buy to the minimum of the requested stamina points and the remaining stamina points in the center	
		stamina_points_to_buy = (current_center->GetNumStaminaPointsRemaining() > stamina)? stamina: current_center->GetNumStaminaPointsRemaining();
	}
}

//Tells this Pokemon to stop doing whatever it was doing
void Pokemon::Stop()
{
	state = STOPPED;
	cout << display_code << id_num << ": Stopping.." << endl;
}

//Returns true if stamina is zero
bool Pokemon::IsExhausted()
{
	if (stamina == 0)
	{
		return true;
	}
	
	return false;
}

//Returns true if ths Pokemon is not exhausted
bool Pokemon::ShouldBeVisible()
{
	if (!IsExhausted())
		return true;
	
	return false;
}

//Shows the status of the pokemon
void Pokemon::ShowStatus()
{
	cout << name << " status: ";
	GameObject::ShowStatus();
	switch (state)
	{
		case STOPPED:
			cout << " stopped" << endl;
			break;
		case MOVING:
			cout << " moving at a speed of " << speed << " to " 
			     << destination << " at each step of " << delta << "." << endl;
			break;
		case EXHAUSTED:
			cout << " EXHAUSTED" << endl;
			break;
		case IN_GYM:
			cout << " inside Pokemon Gym " << current_gym->GetId() << endl;
			break;
		case IN_CENTER:
			cout << " inside Pokemon Center " << current_center->GetId() << endl;
			break;
		case MOVING_TO_GYM:
			cout << " heading to Pokemon Gym " << current_gym->GetId() << " at a speed of " 
			     << speed << " at each step of " << delta << endl;
			break;
		case MOVING_TO_CENTER:
			cout << " heading to Pokemon Center " << current_center->GetId() << " at a speed of " 
			     << speed << " at each step of " << delta << endl;
			break;
		case TRAINING_IN_GYM:
			cout << " traning in Pokemon Gym " << current_gym->GetId() << "." << endl;
			break;
		case RECOVERING_STAMINA:
			cout << " recovering stamina in Pokemon Center " << current_center->GetId() << "." << endl;
			break;
		case MOVING_TO_ARENA:
			cout << " heading to Battle Arena " << current_arena->GetId() << " at a speed of " 
			     << speed << " at each step of " << delta << endl;
			break;
		case IN_ARENA:
			cout << " inside Battle Arena " << current_arena -> GetId() << endl;
			break;
		case FAINTED:
			cout << " FAINTED" << endl;
			break;
		case BATTLE:
			cout << " in battle against rival " << target->GetId() << endl;
			break;
	}

	cout << "	Stamina: " << stamina << endl;
	cout << "	Pokemon Dollars: " << pokemon_dollars << endl;
	cout << "	Experience Points: " << experience_points << endl;
}

//Updates the Pokemon based on its state
bool Pokemon::Update()
{
	switch (state)
	{
		case STOPPED:
		{
			return false;
		}
			break;
		case MOVING:
		{			
			 if (is_in_center) 
			{
                current_center->RemoveOnePokemon();
                is_in_center = false;
            } 
			else if (is_in_gym) 
			{
                current_gym->RemoveOnePokemon();
                is_in_gym = false;
            }
			//This detects when the pokemon is first exhausted and if so changes the state
			if (IsExhausted())
			{
				state = EXHAUSTED;
				cout << name << " is out of stamina and can't move" << endl;
				return true;
			}

			bool hasArrived = UpdateLocation();
			if (hasArrived)
			{
				state = STOPPED;
				return true;
			}
			
			stamina--;
			pokemon_dollars += GetRandomAmountOfPokemonDollars();

			return false;
		}
			break;
		case EXHAUSTED:
		{
			return false;
		}
			break;
		case IN_GYM:
		{
			return false;
		}
			break;
		case IN_CENTER:
		{
			return false;
		}
			break;
		case MOVING_TO_GYM:
		{
			if (is_in_center) {
                current_center->RemoveOnePokemon();
                is_in_center = false;
            } else if (is_in_gym) {
                current_gym->RemoveOnePokemon();
                is_in_gym = false;
            }
			//This detects when the pokemon is first exhausted and if so changes the state
			if (IsExhausted())
			{
				state = EXHAUSTED;
				cout << name << " is out of stamina and can't move" << endl;
				return true;
			}

			bool hasArrived = UpdateLocation();
			if (hasArrived)
			{
				is_in_gym = true;
				state = IN_GYM;
				current_gym->AddOnePokemon();
				return true;
			}
			
			stamina--;
			pokemon_dollars += GetRandomAmountOfPokemonDollars();

			return false;
		}
			break;
		case MOVING_TO_CENTER:
		{
			if (is_in_center) {
                current_center->RemoveOnePokemon();
                is_in_center = false;
            } else if (is_in_gym) {
                current_gym->RemoveOnePokemon();
                is_in_gym = false;
            }
			//This detects when the pokemon is first exhausted and if so changes the state
			if (IsExhausted())
			{
				state = EXHAUSTED;
				cout << name << " is out of stamina and can't move" << endl;
				return true;
			}

			bool hasArrived = UpdateLocation();
			if (hasArrived)
			{
				state = IN_CENTER;
				is_in_center = true;
				current_center->AddOnePokemon();
				return true;
			}
			
			stamina--;
			pokemon_dollars += GetRandomAmountOfPokemonDollars();
			
			return false;
		}
			break;
		case TRAINING_IN_GYM:
		{
			stamina -= current_gym->GetStaminaCost(training_units_to_buy);
			pokemon_dollars -= current_gym->GetDollarCost(training_units_to_buy);
			
			unsigned int experience_points_gained = current_gym->TrainPokemon(training_units_to_buy);
			experience_points += experience_points_gained;
			
			//Print the number of training units gained
			cout << "** " << name << " completed " << training_units_to_buy;
			if (training_units_to_buy == 1)
				cout << " training unit!**" << endl;
			else
				cout << " training units!**" << endl;
			
			//Print the number of experience points gained
			cout << "** " << name << " gained " << experience_points_gained;
			if (experience_points_gained == 1)
				cout << " experience point!**" << endl;
			else
				cout << " experience points!**" << endl;
			training_units_to_buy = 0;
			state = IN_GYM;
			return true;
		}
			break;
		case RECOVERING_STAMINA:
		{
			stamina += current_center->DistributeStamina(stamina_points_to_buy);
			pokemon_dollars -= current_center->GetDollarCost(stamina_points_to_buy);

			if (stamina_points_to_buy == 1)
				cout << "** " << name << " recovered " << stamina_points_to_buy << " a stamina point! **" << endl;
			else
				cout << "** " << name << " recovered " << stamina_points_to_buy << " stamina points! **" << endl;
			stamina_points_to_buy = 0;
			state = IN_CENTER;
			return true;
		}
			break;
		case FAINTED:
		{
			return false;
		}
		break;
		case MOVING_TO_ARENA:
		{
			bool hasArrived = UpdateLocation();
			if (hasArrived)
			{
				state = IN_ARENA;
				is_in_arena = true;
				current_arena->AddOnePokemon();
				return true;
			}
			
			stamina--;
			pokemon_dollars += GetRandomAmountOfPokemonDollars();
			
			//This detects when the pokemon is first exhausted and if so changes the state
			if (IsExhausted())
			{
				state = EXHAUSTED;
				cout << name << " is out of stamina and can't move" << endl;
				return true;
			}
			
			return false;
		}
		break;
		case IN_ARENA:
		{
			return false;
		}
		break;
		case BATTLE:
		{
			//Decrease stamina and pokemon dollars based on arena costs NOT YET IMPLEMENTED
			stamina--;
			pokemon_dollars += GetRandomAmountOfPokemonDollars();

			bool win_check = StartBattle();
			if (win_check)
			{
				health = store_health;
				state = IN_ARENA;
				is_in_arena = true;
				target -> IsAlive();
			}
			else
			{
				state = FAINTED;
				target -> IsAlive();
			}
		}
		break;
	}

	return false; // Should never reach here
}

//Updates the location while moving
bool Pokemon::UpdateLocation()
{
	bool withinStep = (fabs(destination.x - location.x) <= fabs(delta.x)) && 
					  (fabs(destination.y - location.y) <= fabs(delta.y));

	if (withinStep)
	{
		location = destination;
		cout << display_code << id_num << ": I'm there!" << endl;
		return true;
	}

	//Return value is within if stamement so all other statments are a pseduo else
	location = location + delta;
	cout << display_code << id_num << ": step..." << endl;
	return false;
}

//Sets up the object to start moving to dest
void Pokemon::SetupDestination(Point2D dest)
{
	destination = dest;
	
	//Find delta
	double distance = GetDistanceBetween(destination,location);
	if (distance != 0)
	{
		delta = (destination - location) * (speed/GetDistanceBetween(destination,location));
	}
	else
	{
		Vector2D zero;
		delta = zero;
	}
}

//Returns a random number between 0.0 and 2.0 inclusive
double GetRandomAmountOfPokemonDollars()
{
	//Actually get the random number
	double randVal = static_cast<double>(rand()) / RAND_MAX;
	return randVal * 2;
}

//Getter for the name of the pokemon used in the GameCommand class
string Pokemon::GetName()
{
	return name;
}

//Returns true of the state is not FAINTED
bool Pokemon::IsAlive()
{
	if (state != FAINTED)
	{
		return true;
	}

	return false;
}

//Dishes out the beatings
void Pokemon::TakeHit(double physical_damage, double magical_damage, double defense)
{
	int attack_type = rand() % 1; //Should generate a number between 0 and 1
    int damage_choice = (attack_type) ? magical_damage : physical_damage; //Should choose an attack type based on that rand value
	health -= (100.0 - defense) / 100 * damage_choice;
	return;
}

//Sets up the Battle, I made this bool in order to improve game command functionallity
bool Pokemon::ReadyBattle(Rival* in_target)
{
	if (state == IN_ARENA && current_arena->IsAbleToFight(pokemon_dollars, stamina)
		&& !(current_arena -> IsBeaten()) && in_target->IsAlive()) 
	{
		target = in_target;
		state = BATTLE;
		return true;
	}
	else if (!current_arena->IsAbleToFight(pokemon_dollars, stamina))
	{
		cout << "Not enough money or stamina to fight" << endl;
		state = IN_ARENA;
		return false;
	}
	else if (!state == IN_ARENA)
	{
		cout << "Cannot battle outside an arena!" << endl;
		return false;
	}
	else if (current_arena -> IsBeaten())
	{
		cout << "Can't fight the arena is beaten!" << endl;
		state = IN_ARENA;
		return false;
	}
	else if (!in_target->IsAlive())
	{
		cout << "Rival " << in_target->GetId() << " is already defeated" << endl;
		state = IN_ARENA;
		return false;
	}

	return false; //Shouldnt make it here
}

//Orchestrates the battle and calls the TakeHit function
bool Pokemon::StartBattle()
{
	bool switcher = 0;
	while (health > 0 && target->get_health() > 0)
	{
		bool switcher = ~switcher;
		if (switcher)
		{
			//Rival attacks in this loop
			cout << "Rival attacks " << name << endl;
			double health_before = health;
			TakeHit(this->physical_damage, this->magical_damage, this->defense);
			cout << "OOF, he hit you for " << fabs(health_before - health) << endl;	
		}
		else
		{
			//You attack rival in this loop
			cout << "You attack " << target->get_name() << endl;
			double health_before = target->get_health();
			TakeHit(target->get_phys_dmg(), target->get_magic_dmg(), target->get_defense());
			cout << "Nice!! You hit him for " << fabs(health_before - target->get_health()) << endl;
		}
	}
}

//Helps the move to arena function
void Pokemon::StartMovingToArena(BattleArena* arena)
{
	//isThere bool used to test if the Pokemon is already there with similar methodology to UpdateLocation()
	bool isThere = (fabs(destination.x - location.x) == fabs(delta.x)) && 
			   (fabs(destination.y - location.y) == fabs(delta.y));

    if (isThere)
        cout << display_code << id_num << ": I am already at the Pokemon Arena!" << endl;
    else if (IsExhausted())
        cout << display_code << id_num << ": I am exhausted so I shouldn't be going to the arena..." << endl;
    else
	{
		//If leaving a gym, center, or arena act accordingly
		if (is_in_center) 
		{
            current_center->RemoveOnePokemon(); // handles corner case
            is_in_center = false;
        } 
		else if (is_in_gym) 
		{
            current_gym->RemoveOnePokemon();
            is_in_gym = false;
        }
		else if(is_in_arena)
		{
			current_arena->RemoveOnePokemon();
			is_in_arena = false;
		}
		current_arena = arena;
		SetupDestination(current_arena->GetLocation());
		state = MOVING_TO_ARENA;
		cout << display_code << id_num << ": On my way to the arena " << current_arena->GetId() << "." << endl;
	}
}