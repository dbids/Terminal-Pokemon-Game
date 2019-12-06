using namespace std;
#include <string>
#include <iostream>

#include "GameObject.h"
#include "Point2D.h"
#include "Rival.h"

//Constructor for Rival which for our purposes is all we need
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
}

//Acts much the same as the TakeHit function for pokemon
void Rival::TakeHit(int physical_damage, int magical_damage, int defense)
{
	int attack_type = rand() % 1; //Should generate a number between 0 and 1
    int damage_choice = (attack_type) ? magical_damage : physical_damage; //Should choose an attack type based on that rand value
	health -= (100.0 - defense) / 100 * damage_choice;
	return;
}

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
            cout << " Alive" << endl;
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