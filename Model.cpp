using namespace std;
#include <cstdlib>
#include <iostream>
#include <list>
#include <iterator>
#include <fstream>
#include <string>
#include <vector>

//Include user defined headers
#include "Model.h"
#include "Pokemon.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Point2D.h"
#include "BattleArena.h"
#include "Rival.h"
#include "Input_Handling.h"

// Constructors/Destructors
Model::Model()
{
    time = 0;
    
    //Declare default instances of the pokemon, center, gym, rival, and arena
    Point2D pokemon1_loc(5,1);
    pokemon_ptrs.push_back(new Pokemon("Pikachu", 2, 20, 5, 4, 15, 1, 'P', pokemon1_loc));

    Point2D pokemon2_loc(10,1);
    pokemon_ptrs.push_back(new Pokemon("Bulbasaur", 1, 20, 5, 4, 15, 2, 'P', pokemon2_loc));

    Point2D center1_loc(1,20);
    center_ptrs.push_back(new PokemonCenter(1, 1, 100, center1_loc));

    Point2D center2_loc(10,20);
    center_ptrs.push_back(new PokemonCenter(2, 2, 200, center2_loc));

    Point2D gym1_loc;
    gym_ptrs.push_back(new PokemonGym(10, 1, 2, 3, 1, gym1_loc));
    Point2D gym2_loc(5,5);
    gym_ptrs.push_back(new PokemonGym(20, 5, 7.5, 8, 2, gym2_loc));

    //Create all three rivals in the same arena as per Piazza post @394
    Point2D rival_loc(16,16);
	arena_ptrs.push_back(new BattleArena(3, 3, 4.0, 1, rival_loc));
    rival_ptrs.push_back(new Rival("Gary", 1, 20, 3, 1, 10, 1, rival_loc));//Should probs make easier
    rival_ptrs.push_back(new Rival("May", 2, 20, 1, 3, 15, 2, rival_loc));
    rival_ptrs.push_back(new Rival("Joe", 1, 20, 2, 2, 20, 3, rival_loc));

    //Assign them all to the object_ptrs list
    object_ptrs.assign(pokemon_ptrs.begin(), pokemon_ptrs.end());
    object_ptrs.insert(object_ptrs.end(), center_ptrs.begin(), center_ptrs.end());
    object_ptrs.insert(object_ptrs.end(), gym_ptrs.begin(), gym_ptrs.end());
    object_ptrs.insert(object_ptrs.end(), rival_ptrs.begin(), rival_ptrs.end());
    object_ptrs.insert(object_ptrs.end(), arena_ptrs.begin(), arena_ptrs.end());

    //Initially copy object_ptrs to active_ptrs
    active_ptrs.assign(object_ptrs.begin(), object_ptrs.end());

    cout << "Model default constructed" << endl;
}

Model::~Model()
{
    for (list<GameObject*>::iterator optr = object_ptrs.begin(); optr != object_ptrs.end(); std::advance (optr, 1))
        delete (*optr);
    
    object_ptrs.clear();//Added for insurance
        
    cout << "Model destructed" << endl;
} 

//Member Functions

//Returns a pointer to the pokemon's id or 0(NULL) if not found
Pokemon* Model::GetPokemonPtr(int id)
{
    list<Pokemon*>::iterator pptr = pokemon_ptrs.begin();
    if (id <= pokemon_ptrs.size() && id > 0)
    {
        std::advance(pptr, id-1);
        return *pptr;
    }
    
    //Pseudo else
    return NULL;
}

PokemonCenter* Model::GetPokemonCenterPtr(int id)
{
    list<PokemonCenter*>::iterator cptr = center_ptrs.begin();
    if (id <= center_ptrs.size() && id > 0)
    {
        std::advance(cptr, id-1);
        return *cptr;
    }

    //Pseudo else
    return NULL;
}

PokemonGym* Model::GetPokemonGymPtr(int id)
{
    list<PokemonGym*>::iterator gptr = gym_ptrs.begin();
    if (id <= gym_ptrs.size() && id > 0)
    {
        std::advance(gptr, id-1);
        return *gptr;
    }

    //Pseudo else
    return NULL;
}

//Assuming that this is needed based on precedent
Rival* Model::GetRivalPtr(int id)
{
    list<Rival*>::iterator rptr = rival_ptrs.begin();
    if (id <= rival_ptrs.size() && id > 0)
    {
        std::advance(rptr, id-1);
        return *rptr;
    }
    
    return NULL;
}

bool Model::Update()
{
    ++time;
    bool returnVal = false;
    
    //Check to see if all of the gyms have been beaten
    int num_beaten_gyms = 0;
    for (list<PokemonGym*>::iterator gptr = gym_ptrs.begin(); gptr != gym_ptrs.end(); std::advance(gptr,1))
    {
        if ((*gptr)->IsBeaten())
        {
             num_beaten_gyms++;
        }
           
    }
    if (num_beaten_gyms == gym_ptrs.size())
    {
        cout << "GAME OVER: You win! All Pokemon Gyms beaten!" << endl;
        exit(EXIT_SUCCESS);
    }

    //Check to see if all of your pokemon are exhausted
    int num_exhausted_pokemon = 0;
    for (list<Pokemon*>::iterator pptr = pokemon_ptrs.begin(); pptr != pokemon_ptrs.end(); std::advance(pptr,1))
    {
        if ((*pptr)->IsExhausted())
            num_exhausted_pokemon++;
    }
    if (num_exhausted_pokemon == pokemon_ptrs.size())
    {
        cout << "GAME OVER: You lose! All of your Pokemon are tired!" << endl;
        exit(EXIT_FAILURE);
    }
    
    //Check if any GameObjects are not alive and remove them from active_ptrs
    for (list<GameObject*>::iterator aoptr = active_ptrs.begin(); aoptr != active_ptrs.end(); std::advance (aoptr, 1))
    {
		if (!((*aoptr)->IsAlive()))
		{
			cout << "Dead object removed" << endl;
            aoptr = active_ptrs.erase(aoptr);
        }
    }  
    //Update all objects in the Model
    list<GameObject*>::iterator aoptr;
    for (aoptr = active_ptrs.begin(); aoptr != active_ptrs.end(); std::advance(aoptr,1) )
    {
        if (returnVal)
            (*aoptr)->Update();
        else
            returnVal = (*aoptr)->Update();
    }

    return returnVal;
}

//Prints time and then the view class
void Model::Display(View& view)
{
    //Implement the clear, plot, and draw functionallity described at the end of the view class
    view.Clear();

    //Plot each model on the Display
    list<GameObject*>::iterator aoptr;
    for (aoptr = active_ptrs.begin(); aoptr != active_ptrs.end(); std::advance(aoptr,1) )
    {
         view.Plot(*aoptr);
    }

    view.Draw();
}

void Model::ShowStatus()
{
	cout << "Time: " << time << endl;

    //ShowStatus for all objects in the model
    list<GameObject*>::iterator aoptr;
    for (aoptr = active_ptrs.begin(); aoptr != active_ptrs.end(); std::advance(aoptr,1) )
    {
         (*aoptr)->ShowStatus();
    }
}

//Used within the DoMoveToArenaCommand in GameCommand
BattleArena* Model::GetArenaPtr(int id)
{
    list<BattleArena*>::iterator aptr = arena_ptrs.begin();
    if (id <= arena_ptrs.size() && id > 0)
    {
        std::advance(aptr, id-1);
        return *aptr;
    }
    
    //Pseudo else
    return NULL;
}

//Function to add new things described in part 5 of PA4
void Model::NewCommand(char type, int id_num, Point2D location)
{
    //Note: I decided that numbers greater than 9 would be invalid, so that there can only be 9 of a given game object at a time for the sake of the display
    if (location.x <= 20 && location.x >= 0 && location.y <= 20 && location.y >= 0)
    {
        switch(type)
        {
            case 'g':
                if (id_num > gym_ptrs.size() && id_num < 10)
                {
                    gym_ptrs.push_back(new PokemonGym(10, 1, 1, 2, id_num, location));
                    object_ptrs.push_back(gym_ptrs.back());
                    active_ptrs.push_back(gym_ptrs.back());
                }
                    
                else
                    throw Invalid_Input("Please enter valid id_num when creating a new object");
            break;
            case 'c':
                if (id_num > center_ptrs.size() && id_num < 10)
                {
                    center_ptrs.push_back(new PokemonCenter(id_num, 1, 100, location));
                    object_ptrs.push_back(center_ptrs.back());
                    active_ptrs.push_back(center_ptrs.back());
                }
                else
                    throw Invalid_Input("Please enter valid id_num when creating a new object");
            break;
            case 'p':
                if (id_num > pokemon_ptrs.size() && id_num < 10)
                {
                    pokemon_ptrs.push_back(new Pokemon("Charizard", 1, 200, 100, 100, 50, id_num, 'P', location));
                    object_ptrs.push_back(pokemon_ptrs.back());
                    active_ptrs.push_back(pokemon_ptrs.back());
                }
                else
                    throw Invalid_Input("Please enter valid id_num when creating a new object");
            break;
            case 'r':
                if (id_num > pokemon_ptrs.size() && id_num < 10)
                {
                    rival_ptrs.push_back(new Rival("Rivaler", 1, 20, 3, 1, 50, id_num, location));
                    object_ptrs.push_back(rival_ptrs.back());
                    active_ptrs.push_back(rival_ptrs.back());
                }
                else
                    throw Invalid_Input("Please enter valid id_num when creating a new object");

                //Adds the new rival to the arena it is placed in (if placed properly)
                for (list<BattleArena*>::iterator aptr = arena_ptrs.begin(); aptr != arena_ptrs.end(); std::advance(aptr,1))
                {
                    if (rival_ptrs.back()->GetLocation() == (*aptr)->GetLocation())
                    {
                        rival_ptrs.back()->set_current_arena(*aptr);
                        (*aptr)->AddOneRival();
                    }
                }
               
            break;
            default:
                throw Invalid_Input("Please enter valid type when creating a new object");
            break;
        }
    }
    else
    {
        throw Invalid_Input("Please enter a location within the display");
    }
}

//Saves the game
void Model::save(ofstream& file)
{
	if (file.is_open())
	{
        //First save the time
        file << time << endl;
        
        //Then save the catagory information
        file << active_ptrs.size() << endl;

        for (list<GameObject*>::iterator aoptr = active_ptrs.begin(); aoptr != active_ptrs.end(); std::advance(aoptr,1) )
        {
            file << (*aoptr)->GetDisplayCode() << (*aoptr)->GetId() << endl;
        }

        //Then call each object to save
        for (list<GameObject*>::iterator aoptr = active_ptrs.begin(); aoptr != active_ptrs.end(); std::advance(aoptr,1) )
        {
            (*aoptr)->save(file);
        }

	}
	return;
}

//Restores the game from the save
void Model::restore(ifstream& file)
{
    //Clear the existing model data
    active_ptrs.clear();
    object_ptrs.clear();
    pokemon_ptrs.clear();
    center_ptrs.clear();
    gym_ptrs.clear();
    arena_ptrs.clear();
    rival_ptrs.clear();

    string line;

    if (file.is_open())
	{
        //Get time and size
        getline(file, line);
        time = stoi(line);
        getline(file, line);
        int num_of_active_objects = stoi(line);
        
        //Get all the category information
        vector <char> display_codes(num_of_active_objects);
        vector <int> id_nums(num_of_active_objects);
        for (int i = 0; i < num_of_active_objects; i++)
        {
            getline(file,line);
            display_codes[i] = line[0];
            id_nums[i] = static_cast<int>(line[1])-'0';
        }

        //Based on the category information create the objects
        for (int i = 0; i < num_of_active_objects; i++)
        {
            switch(display_codes[i])
            {
                case 'P':
                case 'p':
                    pokemon_ptrs.push_back(new Pokemon(display_codes[i]));
                break;
                case 'A':
                case 'a':
                    arena_ptrs.push_back(new BattleArena(0, 0, 0, id_nums[i], Point2D(0,0)));
                break;
                case 'G':
                case 'g':
                    gym_ptrs.push_back(new PokemonGym(0, 0, 0, 0, id_nums[i], Point2D(0,0)));
                    cout << gym_ptrs.back()->GetDisplayCode() << gym_ptrs.back()->GetId() << endl;
                break;
                case 'C':
                case 'c':
                    center_ptrs.push_back(new PokemonCenter(id_nums[i], 0, 0, Point2D(0,0)));
                    cout << center_ptrs.back()->GetDisplayCode() << center_ptrs.back()->GetId() << endl;
                break;
                case 'R':
                case 'r':
                    rival_ptrs.push_back( new Rival("temp", 0, 0, 0, 0, 0, id_nums[i], Point2D(0,0)));
                break;
                default:
                    throw Invalid_Input("Error: reading from file");
            }
        }
        //Based on the category information call the other restore functions (necessary to seperate due to pointers)
        list<Pokemon*>::iterator pptr = pokemon_ptrs.begin(); 
        list<BattleArena*>::iterator aptr = arena_ptrs.begin(); 
        list<PokemonGym*>::iterator gptr = gym_ptrs.begin(); 
        list<PokemonCenter*>::iterator cptr = center_ptrs.begin();
        list<Rival*>::iterator rptr = rival_ptrs.begin();
        for (int i = 0; i < num_of_active_objects; i++)
        {
            
            switch(display_codes[i])
            {
                case 'P':
                case 'p':
                    (*pptr)->restore(file, *this);
                    std::advance(pptr,1);
                break;
                case 'A':
                case 'a':
                    (*aptr)->restore(file, *this);
                    std::advance(aptr,1);
                break;
                case 'G':
                case 'g':
                    (*gptr)->restore(file, *this);
                    std::advance(gptr,1);
                break;
                case 'C':
                case 'c':
                    (*cptr)->restore(file, *this);
                    std::advance(cptr,1);
                break;
                case 'R':
                case 'r':
                    (*rptr)->restore(file, *this);
                    std::advance(rptr,1);
                break;
                default:
                    throw Invalid_Input("Error: reading from file");
            }
        }

        //Assign them all to the object_ptrs list
        object_ptrs.assign(pokemon_ptrs.begin(), pokemon_ptrs.end());
        object_ptrs.insert(object_ptrs.end(), center_ptrs.begin(), center_ptrs.end());
        object_ptrs.insert(object_ptrs.end(), gym_ptrs.begin(), gym_ptrs.end());
        object_ptrs.insert(object_ptrs.end(), rival_ptrs.begin(), rival_ptrs.end());
        object_ptrs.insert(object_ptrs.end(), arena_ptrs.begin(), arena_ptrs.end());

        //Initially copy object_ptrs to active_ptrs
        active_ptrs.assign(object_ptrs.begin(), object_ptrs.end());
    } 
	return;
}