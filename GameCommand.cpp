using namespace std;
#include <iostream>
#include <cstdlib> //NULL

//Include created headers
#include "Model.h"
#include "Point2D.h"
#include "View.h"
#include "GameCommand.h"
#include "Input_Handling.h"

//Performs the move command on a given pokemon
void DoMoveCommand(Model& model, int pokemon_id, Point2D p1)
{
    Pokemon* pokemon_of_choice = model.GetPokemonPtr(pokemon_id);
    
    //If the point exists then begin moving and print that you are doing so
    if (pokemon_of_choice)
    {
        cout << "Moving " << pokemon_of_choice->GetName() << " to " << p1 << endl;
        pokemon_of_choice->StartMoving(p1);
    }
    else
    {
        throw Invalid_Input("Error: Please enter a valid command");
    }
        
}

//Performs the move to center command on a given pokemon
void DoMoveToCenterCommand(Model& model, int pokemon_id, int center_id)
{
    Pokemon* pokemon_of_choice = model.GetPokemonPtr(pokemon_id);
    PokemonCenter* center_of_choice = model.GetPokemonCenterPtr(center_id);
    
    //If the pointers exist then begin moving to center and print that you are doing so
    if (pokemon_of_choice && center_of_choice)
    {
        cout << "Moving " << pokemon_of_choice->GetName() << " to center " << center_id << endl;
        pokemon_of_choice->StartMovingToCenter(center_of_choice);
    }
    else
    {
        throw Invalid_Input("Error: Please enter a valid command");
    } 
}

//Performs the move to center command on a given pokemon
void DoMoveToGymCommand(Model& model, int pokemon_id, int gym_id)
{
    Pokemon* pokemon_of_choice = model.GetPokemonPtr(pokemon_id);
    PokemonGym* gym_of_choice = model.GetPokemonGymPtr(gym_id);

    //If the pointers exist then begin moving to gym and print that you are doing so
    if (pokemon_of_choice && gym_of_choice)
    {
        cout << "Moving " << pokemon_of_choice->GetName() << " to gym " << gym_id << endl;
        pokemon_of_choice->StartMovingToGym(gym_of_choice);
    }
    else
    {
        throw Invalid_Input("Error: Please enter a valid command");
    }
}

//Performs the stop command on a given pokemon
void DoStopCommand(Model& model, int pokemon_id)
{
    Pokemon* pokemon_of_choice = model.GetPokemonPtr(pokemon_id);

    //If the pokemon pointer existing then stop it
    if (pokemon_of_choice)
    {
        cout << "Stopping " << pokemon_of_choice->GetName() << endl;
        pokemon_of_choice->Stop();
    }
    else
    {
        throw Invalid_Input("Error: Please enter a valid command");
    }
}

//Performs the train in gym function on a given pokemon if valid
void DoTrainInGymCommand(Model& model, int pokemon_id, unsigned int training_units)
{
    Pokemon* pokemon_of_choice = model.GetPokemonPtr(pokemon_id);

    //If the pokemon pointer existing then get swoll
    if (pokemon_of_choice)
    {
        cout << "Training " << pokemon_of_choice->GetName() << endl;
        pokemon_of_choice->StartTraining(training_units);
    }
    else
    {
        throw Invalid_Input("Error: Please enter a valid command");
    }
}

//Performs the recover in center command on a given pokemon if valid
void DoRecoverInCenterCommand(Model& model, int pokemon_id, unsigned int stamina_points)
{
   Pokemon* pokemon_of_choice = model.GetPokemonPtr(pokemon_id);

    //If the pokemon pointer existing then get swoll
    if (pokemon_of_choice)
    {
        cout << "Recovering " << pokemon_of_choice->GetName() << "'s stamina" << endl;
        pokemon_of_choice->StartRecoveringStamina(stamina_points);
    }
    else
    {
        throw Invalid_Input("Error: Please enter a valid command");
    }
}

//Updates and Displays the model for one tick
void DoGoCommand(Model& model, View& view)
{
	cout << "Advancing one tick" << endl;    
	model.Update();
	model.ShowStatus();
    model.Display(view);
}

//Updates and Displays the model until a major event
void DoRunCommand(Model& model, View& view)
{
    cout << "Advancing to next event" << endl;
    int count = 0;
    while (!model.Update() && count < 4)
    {
        count ++;
    } 
    model.ShowStatus();
    model.Display(view);
}

//Commences the BATTLE!!
void DoBattleCommand(Model& model, int pokemon_id, int rival_id)
{
    Pokemon* pokemon_of_choice = model.GetPokemonPtr(pokemon_id);
    Rival* rival_of_choice = model.GetRivalPtr(rival_id);

    //If the pointers exist then begin battle
    if (pokemon_of_choice && rival_of_choice)
    {
        cout << "Ready your pokemon, the battle begins now!!" << endl;
        if(pokemon_of_choice->ReadyBattle(rival_of_choice))
        {
           pokemon_of_choice->Update(); 
        }
        
    }
    else
    {
        throw Invalid_Input("Error: Please enter a valid command");
    }
}

//Used much like c or g, to move to the Arena building
void DoMoveToArenaCommand(Model& model, int pokemon_id, int arena_id)
{
    Pokemon* pokemon_of_choice = model.GetPokemonPtr(pokemon_id);
    BattleArena* arena_of_choice = model.GetArenaPtr(arena_id);

    //If the pointers exist then begin moving to the arena
    if (arena_of_choice && pokemon_of_choice)
    {
        cout << "Moving " << pokemon_of_choice->GetName() << " to arena " << arena_id << endl;
        pokemon_of_choice->StartMovingToArena(arena_of_choice);
    }
    else
    {
        throw Invalid_Input("Error: Please enter a valid command");
    }
    
}