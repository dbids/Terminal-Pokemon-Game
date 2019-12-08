using namespace std;
#include <string>
#include <iostream>
#include <fstream>

#include "GameObject.h"
#include "Point2D.h"
#include "Rival.h"
#include "Model.h"
#include "Attack_Types.h"

//Constructor for Rival
Rival::Rival(string name, double speed, double hp, double phys_dmg, double magic_dmg,
             double def, int id, Point2D in_loc) : GameObject(in_loc, id, 'R')
{
    this->name = name;
    this->speed = speed;
    health = hp;
    physical_damage = phys_dmg;
    magical_damage = magic_dmg;
    defense = def;
    state = ALIVE_RIVAL;

    //Print it
    printPokemon();
}

//Acts much the same as the TakeHit function for pokemon (REVISED)
void Rival::TakeHit(double defense, Attack_Types& attack_choice)
{
	//Should choose a damage type based on the move
    int damage_choice = (rand() % 2) ? attack_choice.getPhyDamage() : attack_choice.getMagDamage();

	//Decrements the health based on the choice of move and damage type
	health -= (100.0 - defense) / 100 * damage_choice;

	return;
}

/* OLD VERSION FOR PA4
void Rival::TakeHit(double physical_damage, double magical_damage, double defense)
{
	int attack_type = rand() % 2; //Should generate a number between 0 and 1
    int damage_choice = (attack_type) ? magical_damage : physical_damage; //Should choose an attack type based on that rand value
	health -= (100.0 - defense) / 100 * damage_choice;
	return;
}*/

//Getter for physical damage
double Rival::get_phys_dmg()
{
    return physical_damage;
}

//Getter for magical damage
double Rival::get_magic_dmg()
{
    return magical_damage;
}

//Getter for defense
double Rival::get_defense()
{
    return defense;
}

//Getter for health
double Rival::get_health()
{
    return health;
}

//Updates the Rival class
bool Rival::Update()
{
    switch (state)
    {
        case ALIVE_RIVAL:
        {
            return false;
        }
        break;
        case FAINTED_RIVAL:
        {
            return false;
        }
        break;
    }
}

//Shows the status of the rival class
void Rival::ShowStatus()
{
    cout <<  "Rival Status: ";
    GameObject::ShowStatus();
    switch (state)
    {
        case ALIVE_RIVAL:
        {
            cout << " Alive with health: " << health << endl; //I added the health in order to know the result of a battle
        }
        break;
        case FAINTED_RIVAL:
        {
            cout << " Fainted" << endl;
        }
        break;
    }
}

//Updates the state of the rival class and returns whether or not it is alive
//Note this is used in Pokemon.cpp instructions, but not in instructions for rival class as of 11/25/2019
bool Rival::IsAlive()
{
    if (health <= 0)
    {
        state = FAINTED_RIVAL;
        return false;
    }   

    state = ALIVE_RIVAL;
    return true;

}

//Getter for name which I added for better couts in pokemon.cpp
string Rival::get_name()
{
    return name;
}

//Need this for ShoudlBeVisible to be a pure virtual function in GameObject
bool Rival::ShouldBeVisible()
{
    if (IsAlive())
    {
        return true;
    }

    return false;
}

//Need this in order to change the current_arena from the model class
void Rival::set_current_arena(BattleArena* current_arena)
{
    this->current_arena = current_arena;
}

//Need this to be able to see current_arena from the model class
BattleArena* Rival::get_current_arena()
{
    return this->current_arena;
}

//Saves the game
void Rival::save(ofstream& file)
{
	if (file.is_open())
	{
		//First call GameObjects save function
		GameObject::save(file);

		//Copy the normal member variables
		file << health << endl;
		file << physical_damage << endl;
		file << magical_damage << endl;
		file << defense << endl;
		file << stamina_cost_per_fight << endl;
		file << name << endl;
		file << speed << endl;

		//Copy the pointers to other Game Objects' id
		if (current_arena)
            file << current_arena->GetId() << endl;
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
void Rival::restore(ifstream& file, Model& model)
{
	string line;
    
    //First call Gameobjects restore
    GameObject::restore(file, model);
    
    //Restore the state properly
    state = (state == '1') ? ALIVE_RIVAL : FAINTED_RIVAL;

    getline(file,line);
    health = stod(line);
    getline(file,line);
    physical_damage = stod(line);
    getline(file,line);
    magical_damage = stod(line);
    getline(file,line);
    defense = stod(line);
    getline(file,line);
    stamina_cost_per_fight = stod(line);
    getline(file,line);
    name = line;
    getline(file,line);
    speed = stod(line);

    //Then do the pointers to variables
	getline(file,line);//current_arena
	if (line != "-1")
		current_arena = model.GetArenaPtr(stoi(line));

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

//prints the Rival Pokemon upon creation
void Rival::printPokemon()
{
    cout << R"(                                        
                         |              |
                         |             ,|
                ,_       |\            F'   ,.-""`.
               /  `-._   |`           // ,-"_,..  |
              |   ___ `. | \ ,"""`-. /.-' ,'    ' |_....._
              |  /   `-.`.  L......|j j_.'      ` |       `._
              | |      _,'| |______|' | '-._     ||  ,.-.    `.
               L|    ,'   | |      | j      `-.  || '    `.    \
___            | \_,'     | |`"----| |         `.||       |\    \
 ""=+...__     `,'   ,.-.   |....._|   _....     Y \      j_),..+=--
     `"-._"._  .   ,' |  `   \    /  ,' |   \     \ j,..-"_..+-"  L
          `-._-+. j   !   \   `--'  .   !    \  ,.-" _..<._  |    |
              |-. |   |    L        |   !     |  .-/'      `.|-.,-|
              |__ '   '    |        '   |    /    /|   `, -. |   j
        _..--'"__  `-.___,'          `.___,.'  __/_|_  /   / '   |
   _.-_..---""_.-\                            .,...__""--./L/_   |
 -'""'     ,""  ,-`-.    .___.,...___,    _,.+"      """"`-+-==++-
          / /  `.   "-.._`v \|    V/  /-'    \._,._.'"-. /    /
          ` `.  )---.     `""\\__  / .'        /    \    Y"._.'
           `"'`"     `-.     /|._""_/         |  ,..   _ |  |
                        `"""' |  "'           `. `-'  (_|,-.'
                               \               |`       .`-
                                `.           . j`._    /
                                 |`.._     _.'|    `""/
                                 |    /""'"   |  .". j
                                .`.__j         \ `.' |
                                j    |          `._.'
                               /     |
                              /,  ,  \
                              \|  |   L
                               `..|_..)" << '\n';
    return;
}
//prints the Rival Pokemon during battle
void Rival::printBattlePokemon()
{
cout << R"(
_____________________________________________________________________
[]=+...__     `,'   ,.-.   |....._|   _....     Y \      j_),..+=-- []
[]   `"-._"._  .   ,' |  `   \    /  ,' |   \     \ j,..-"_..+-"  L []
[]        `-._-+. j   !   \   `--'  .   !    \  ,.-" _..<._  |    | []
[]            |-. |   |    L        |   !     |  .-/'      `.|-.,-| []
[]            |__ '   '    |        '   |    /    /|   `, -. |   j  []
[]      _..--'"__  `-.___,'          `.___,.'  __/_|_  /   / '   |  []
====================================================================== )" << '\n';
return;
}
