using namespace std;
#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <typeinfo>
#include <string>
#include <fstream> //ofstream

//User defined headers
#include "Pokemon.h"
#include "GameObject.h"
#include "Point2D.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Rival.h"
#include "BattleArena.h"
#include "Model.h"
#include "Attack_Types.h"

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
	physical_damage = 5; //left but not used with extra credit
	magical_damage = 4;//left but not used with extra credit
	defense = 15;
	is_in_arena = 0;
	target = NULL;
	current_arena = NULL;

	//Add attack types
	attack_list[0] = Attack_Types();
	attack_list[1] = Attack_Types();

	//Print it!
	printPokemon();
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
	physical_damage = 5;//left but not used with extra credit
	magical_damage = 4;//left but not used with extra credit
	defense = 15;
	is_in_arena = 0;
	target = NULL;
	current_arena = NULL;

	//Add attack types
	attack_list[0] = Attack_Types();
	attack_list[1] = Attack_Types();

	//Print it!
	printPokemon();
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
	physical_damage = phys_dmg;//left but not used with extra credit
	magical_damage = magic_dmg;//left but not used with extra credit
	defense = def;
	is_in_arena = 0;
	target = NULL;
	current_arena = NULL;

	//Add attack types for pickachu/bulbasaur
	attack_list[0] = Attack_Types(in_name);
	attack_list[1] = Attack_Types(in_name);

	//Print it!
	printPokemon();
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
	else if (state != IN_CENTER && state != RECOVERING_STAMINA)
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

//Returns true if ths Pokemon is not exhausted OR is alive
bool Pokemon::ShouldBeVisible()
{
	if (!(IsExhausted()) || IsAlive())
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
			
			//Level up skills if the pokemon now has more than 7 experience points
			if (experience_points > 7)
			{
				char yes_no;
				cout << "Do you wish to spend 7 experience points to evolve (y/n) ? " << endl;
				cin >> yes_no;
				if (yes_no == 'y')
				{
					attack_list[0].levelUp();
					attack_list[1].levelUp();
				}
			}

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
	return state != FAINTED;
}

//Dishes out the beatings (REVISED)
void Pokemon::TakeHit(double defense, Attack_Types& attack_choice)
{
	//Should choose a damage type based on that move
    int damage_choice = (rand() % 2) ? attack_choice.getPhyDamage() : attack_choice.getMagDamage();

	//Decrements the health based on the choice of move and damage type
	health -= (100.0 - defense) / 100 * damage_choice;

	return;
}

//Old Version of TakeHit from before the addition of the extra credit attack types
/*void Pokemon::TakeHit(double physical_damage, double magical_damage, double defense)
{
	int attack_type = rand() % 2; //Should generate a number between 0 and 1
    int damage_choice = (attack_type) ? magical_damage : physical_damage; //Should choose an attack type based on that rand value
	health -= (100.0 - defense) / 100 * damage_choice;
	return;
}*/

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
	Attack_Types attack_choice;
	double health_before = 0.0;
	while (health > 0 && target->get_health() > 0)
	{
		switcher = !switcher;
		if (switcher)
		{
			//Rival attacks in this loop
			cout << "Rival attacks " << name << endl;
			target->printBattlePokemon();
			printBattlePokemon();

			health_before = health;
			attack_choice = target->attack_list[rand() % 2];
			TakeHit(this->defense, attack_choice);

			cout << "OOF, he hit you with " << attack_choice.getName() << " for " << fabs(health_before - health) << endl;
			cout << "Pokemon Health:" << health << endl;
			attack_choice.printAttack();	
		}
		else
		{
			//You attack rival in this loop
			cout << "You attack " << target->get_name() << endl;
			printBattlePokemon();
			target->printBattlePokemon();

			health_before = target->get_health();
			attack_choice = attack_list[rand() % 2];
			target->TakeHit(target->get_defense(), attack_choice);
			cout << health_before << " " << target->get_health() << endl;
			cout << "Nice!! You hit him with " << attack_choice.getName() << " for " << fabs(health_before - target->get_health()) << endl;
			cout << "Rival Health:" << target->get_health() << endl;
			attack_choice.printAttack();
		}
	}
	//Print the outcome
	if (health <= 0)
	{
		std::cout << R"( 
                                     /$$                              
                                    | $$                              
 /$$   /$$  /$$$$$$  /$$   /$$      | $$  /$$$$$$   /$$$$$$$  /$$$$$$ 
| $$  | $$ /$$__  $$| $$  | $$      | $$ /$$__  $$ /$$_____/ /$$__  $$
| $$  | $$| $$  \ $$| $$  | $$      | $$| $$  \ $$|  $$$$$$ | $$$$$$$$
| $$  | $$| $$  | $$| $$  | $$      | $$| $$  | $$ \____  $$| $$_____/
|  $$$$$$$|  $$$$$$/|  $$$$$$/      | $$|  $$$$$$/ /$$$$$$$/|  $$$$$$$
 \____  $$ \______/  \______/       |__/ \______/ |_______/  \_______/
 /$$  | $$                                                            
|  $$$$$$/                                                            
 \______/)" << '\n';
		return false;
	}
	else
	{
		std::cout << R"( 
                                                   /$$          
                                                  |__/          
 /$$   /$$  /$$$$$$  /$$   /$$       /$$  /$$  /$$ /$$ /$$$$$$$ 
| $$  | $$ /$$__  $$| $$  | $$      | $$ | $$ | $$| $$| $$__  $$
| $$  | $$| $$  \ $$| $$  | $$      | $$ | $$ | $$| $$| $$  \ $$
| $$  | $$| $$  | $$| $$  | $$      | $$ | $$ | $$| $$| $$  | $$
|  $$$$$$$|  $$$$$$/|  $$$$$$/      |  $$$$$/$$$$/| $$| $$  | $$
 \____  $$ \______/  \______/        \_____/\___/ |__/|__/  |__/
 /$$  | $$                                                      
|  $$$$$$/                                                      
 \______/ )" << '\n';
	}
		return true;
}

//Old Version of StartBattle() from before the addition of the extra credit attack types and printing
/*bool Pokemon::StartBattle()
{
	bool switcher = 0;
	while (health > 0 && target->get_health() > 0)
	{
		switcher = !switcher;
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
			target->TakeHit(target->get_phys_dmg(), target->get_magic_dmg(), target->get_defense());
			cout << "Nice!! You hit him for " << fabs(health_before - target->get_health()) << endl;
		}
	}
}*/

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

//Saves the game
void Pokemon::save(ofstream& file)
{
	if (file.is_open())
	{
		//First call GameObjects save function
		GameObject::save(file);

		//Copy the normal member variables
		file << speed << endl;
		file << is_in_gym << endl;
		file << is_in_center << endl;
		file << stamina << endl;
		file << experience_points << endl;
		file << pokemon_dollars << endl;
		file << training_units_to_buy << endl;
		file << stamina_points_to_buy << endl;
		file << name << endl;
		file << health << endl;
		file << store_health << endl;
		file << physical_damage << endl;
		file << magical_damage << endl;
		file << defense << endl;
		file << is_in_arena << endl;
		file << destination.x << endl; 	//Point2D destination(x,y)
		file << destination.y << endl;
		file << delta.x << endl;		//Vector2D delta(x,y)
		file << delta.y << endl;

		//Copy the pointers to other Game Objects id
		if (current_arena)
			file << current_arena->GetId() << endl;
		else
			file << -1 << endl;
		if (current_center)
			file << current_center->GetId() << endl;
		else
			file << -1 << endl;		
		if (current_gym)
			file << current_gym->GetId() << endl;
		else
			file << -1 << endl;
		if (target )
			file << target->GetId() << endl;
		else
			file << -1 << endl;

		//Additional things for the Attack_Types class
		file << attack_list[0].getName() << endl;
		file << attack_list[0].getPhyDamage() << endl;
		file << attack_list[0].getMagDamage() << endl;
		file << attack_list[1].getName() << endl;
		file << attack_list[1].getPhyDamage() << endl;
		file << attack_list[1].getMagDamage() << endl;
		
	}
	return;
}

//Restores the game from the save
void Pokemon::restore(ifstream& file, Model& model)
{
	string line;
	
	//First restore the game object
	GameObject::restore(file, model);
	
	//Restore the state properly
	getline(file,line);
    int state_temp = stoi(line);
	switch (state_temp)
	{
		case 0: state = STOPPED;			break;
		case 1: state = MOVING;				break;
		case 2: state = EXHAUSTED;			break;
		case 3: state = IN_GYM;				break;
		case 4: state = IN_CENTER;			break;
		case 5: state = MOVING_TO_GYM;		break;
		case 6: state = MOVING_TO_CENTER;	break;
		case 7: state = TRAINING_IN_GYM;	break;
		case 8: state = RECOVERING_STAMINA;	break;
		case 9: state = IN_ARENA;			break;
		case 10: state = MOVING_TO_ARENA;	break;
		case 11: state = BATTLE;			break;
		case 12: state = FAINTED; 			break;
	}
	
	//First do the normal variables
	getline(file,line);
	speed = stod(line, NULL);
	getline(file,line);
	is_in_gym = (line == "1") ? true : false;
	getline(file,line);
	is_in_center = (line == "1") ? true : false;
	getline(file,line);
	stamina = stoul(line);
	getline(file,line);
	experience_points = stoul(line);
	getline(file,line);
	pokemon_dollars = stod(line, NULL);
	getline(file,line);
	training_units_to_buy = stoul(line);
	getline(file,line);
	stamina_points_to_buy = stoul(line);
	getline(file,line);
	name = line;
	getline(file,line);
	health = stod(line, NULL);
	getline(file,line);
	store_health = stod(line, NULL);
	getline(file,line);
	physical_damage = stod(line, NULL);
	getline(file,line);
	magical_damage = stod(line, NULL);
	getline(file,line);
	defense = stod(line, NULL);
	getline(file,line);
	is_in_arena = (line=="1") ? true : false;
	getline(file,line);
	destination.x = stod(line);
	getline(file,line);
	destination.y = stod(line);
	getline(file,line);
	delta.x = stod(line);
	getline(file,line);
	delta.y = stod(line);

	//Then do the pointers to variables
	getline(file,line);//current_arena 
	if (line != "-1")
		current_arena = model.GetArenaPtr(stoi(line));
	getline(file,line); //current_center
	if (line != "-1")
		current_center = model.GetPokemonCenterPtr(stoi(line));
	getline(file,line); //current_gym
	if (line != "-1")
		current_gym = model.GetPokemonGymPtr(stoi(line));
	getline(file,line); //target
	if (line != "-1")
		target = model.GetRivalPtr(stoi(line));

	//Additional things for the Attack_Types class
	getline(file,line);
	string temp_name = line;
	getline(file,line);
	double temp_mag_dmg = stod(line);
	getline(file,line);
	double temp_phy_dmg = stod(line);
	attack_list[0] = Attack_Types(temp_name, temp_mag_dmg, temp_phy_dmg);
	getline(file,line);
	temp_name = line;
	getline(file,line);
	temp_mag_dmg = stod(line);
	getline(file,line);
	temp_phy_dmg = stod(line);
	attack_list[1] = Attack_Types(temp_name, temp_mag_dmg, temp_phy_dmg);

	return;
}

//prints the Pokemon upon creation
void Pokemon::printPokemon()
{
	if (name == "Bulbasaur")
	{
		std::cout << R"(                                           
                        _,.------....___,.' ',.-.
                     ,-'          _,.--"        |
                   ,'         _.-'              .
                  /   ,     ,'                   `
                 .   /     /                     ``.
                 |  |     .                       \.\
       ____      |___._.  |       __               \ `.
     .'    `---""       ``"-.--"'`  \               .  \
    .  ,            __               `              |   .
    `,'         ,-"'  .               \             |    L
   ,'          '    _.'                -._          /    |
  ,`-.    ,".   `--'                      >.      ,'     |
 . .'\'   `-'       __    ,  ,-.         /  `.__.-      ,'
 ||:, .           ,'  ;  /  / \ `        `.    .      .'/
 j|:D  \          `--'  ' ,'_  . .         `.__, \   , /
/ L:_  |                 .  "' :_;                `.'.'
.    ""'                  """""'                    V
 `.                                 .    `.   _,..  `
   `,_   .    .                _,-'/    .. `,'   __  `
    ) \`._        ___....----"'  ,'   .'  \ |   '  \  .
   /   `. "`-.--"'         _,' ,'     `---' |    `./  |
  .   _  `""'--.._____..--"   ,             '         |
  | ." `. `-.                /-.           /          ,
  | `._.'    `,_            ;  /         ,'          .
 .'          /| `-.        . ,'         ,           ,
 '-.__ __ _,','    '`-..___;-...__   ,.'\ ____.___.'
 `"^--'..'   '-`-^-'"--    `-^-'`.''"""""`.,^.`.--' )" << '\n';
	}
	else if (name == "Pikachu")
	{
	std::cout << R"( 
:::,
 '::::'._
   '.    '.                        __.,,.
     '.    '.                _..-'''':::"
       \     \,.--""""--.,-''      _:'
   /\   \  .               .    .-'
  /  \   \                   ':'
 /    \  :                     :
/      \:                       :
\       :                       :
 \      :      ,--,         ,-,  :
  \    :      |(_):|       |():| :
   \   :     __'--'   __    '-'_  :
    \  :    /  \      \/      / \ :
     \  :  (    )             \_/ :
  .-'' . :  \__/   '--''--'      :
  \  . .-:'.                   .:
   \' :| :  '-.__      ___...-' :
    \::|:        ''''''          '.
  .,:::':  :                       '.
   \::\:   :                         '._
    \::    :     /             '-._     '.
     \:    :    /              .   :-._ :-'
      :    :   /               :   :  ''
      :   .'   )'.             :   :
       :  :  .'   '.          :   :
        : '..'      :      _.' _.:
         '._        :..---'\'''  _)
            '':---''_)      '-'-'
               '-'-'  )" << '\n';
	}
	else 
	{
std::cout << R"(
                 ."-,.__
                 `.     `.  ,
              .--'  .._,'"-' `.
             .    .'         `'
             `.   /          ,'
               `  '--.   ,-"'
                `"`   |  \
                   -. \, |
                    `--Y.'      ___.
                         \     L._, \
               _.,        `.   <  <\                _
             ,' '           `, `.   | \            ( `
          ../, `.            `  |    .\`.           \ \_
         ,' ,..  .           _.,'    ||\l            )  '".
        , ,'   \           ,'.-.`-._,'  |           .  _._`.
      ,' /      \ \        `' ' `--/   | \          / /   ..\
    .'  /        \ .         |\__ - _ ,'` `        / /     `.`.
    |  '          ..         `-...-"  |  `-'      / /        . `.
    | /           |L__           |    |          / /          `. `.
   , /            .   .          |    |         / /             ` `
  / /          ,. ,`._ `-_       |    |  _   ,-' /               ` \
 / .           \"`_/. `-_ \_,.  ,'    +-' `-'  _,        ..,-.    \`.
.  '         .-f    ,'   `    '.       \__.---'     _   .'   '     \ \
' /          `.'    l     .' /          \..      ,_|/   `.  ,'`     L`
|'      _.-""` `.    \ _,'  `            \ `.___`.'"`-.  , |   |    | \
||    ,'      `. `.   '       _,...._        `  |    `/ '  |   '     .|
||  ,'          `. ;.,.---' ,'       `.   `.. `-'  .-' /_ .'    ;_   ||
|| '              V      / /           `   | `   ,'   ,' '.    !  `. ||
||/            _,-------7 '              . |  `-'    l         /    `||
. |          ,' .-   ,' ||               | .-.        `.      .'     ||
 `'        ,'    `".'    |               |    `.        '. -.'       `'
          /      ,'      |               |,'    \-.._,.'/'
          .     /        .               .       \    .''
        .`.    |         `.             /         :_,'.'
          \ `...\   _     ,'-.        .'         /_.-'
           `-.__ `,  `'   .  _.>----''.  _  __  /
                .'        /"'          |  "'   '_
               /_|.-'\ ,".             '.'`__'-( \
                 / ,"'"\,'               `/  `-.|" 
                 )" << '\n';
	}

	return;
}
//prints the Pokemon during battle
void Pokemon::printBattlePokemon()
{
	if (name == "Bulbasaur")
	{
	std::cout << R"(
______________________________________________________________________
[]   '         /   /  ..   `.  `./ | ;`.'   ,"" ,.  `.   \      |   []
[]    `.     ,'  ,'   | |\  |      "       |  ,'\ |   \   `    ,L   []
[]    /|`.  /   '     | `-| '                /`-' |    L   `._/  \  []
[]   / | .`|   |  .   `._.'                 `.__,'   .  |    |  (`  []
[]  '-""-'_|   `. `.__,.____     .   _,        ____ ,-  j    ".-'"' []
[]         \     `-.  \/.   `"-.._   _,.---'""\/  "_,.'     /-'     []
======================================================================
	)" << '\n';
	}
	else if (name == "Pikachu")
	{
	std::cout << R"(
______________________________________________________________________
[] \ \\ \   `-+_       '-   __           ,--. ./             / // / []
[]\ \ \\ \      `-.._     .:  ).        (`--"| \            / // / /[]
[]\\ \ \\ \          7    | `" |         `...'  \          / // / //[]
[] \\ \ \\ \         |     `--'     '+"        ,". ,""-   / // / // []
[]\ \\ \ \\ \   _.   |   _...        .____     | |/    ' / // / // /[]
[] \ \\ \ \\ \ \' `-.\  .    `.  '--"   /      `./     j/ // / // / []
======================================================================
	)" << '\n';
	}
	else
	{
	std::cout << R"(
______________________________________________________________________
[]         ,' '      `, `.   | \       ( `            `.    `.  ,   []
[]      ../, `.       `  |    .\`.      \ \_       .--'  ._,'"-' `. []
[]     ,' ,..  .      _.,'    ||\l       )  '".   .    .'        `' []
[]    , ,'   \      ,'.-.`-._,'  |      .  _._`.  `.   /         ,' []
[]  ,' /      \ \   `' ' `--/   | \     / /   ..\   `  '--.  ,-"'   []
[].'  /        \ .    |\__ - _ ,'` `   / /     `.`.  `"`   | \      []
======================================================================
	)" << '\n';
	}
	return;
}