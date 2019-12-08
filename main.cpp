using namespace std;
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <ios>  //stream_size    
#include <limits> //numeric_limits
#include <cctype> //isspace
#include <ios> //noskipws

//Include the header files for the different classes
#include "Point2D.h"
#include "Vector2D.h"
#include "GameObject.h"
#include "Building.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Pokemon.h"
#include "Model.h"
#include "GameCommand.h"
#include "View.h"
#include "Rival.h"
#include "BattleArena.h"
#include "Input_Handling.h"


int main()
{
	//Initialize the random seed
	srand(time(NULL));
	
    //Create the inital header to the output
    cout << "EC327: Introduction to Software Engineering" << endl;
    cout << "Fall 2019" << endl;
    cout << "Programming Assignment 4" << endl;
    cout << "Created by Devin Bidstrup" << endl;

    //Output the pokemon logo!
    cout << "                                  ,'\\ " << endl;
    cout << "    _.----.        ____         ,'  _\\   ___    ___     ____" <<  endl;
    cout << "_,-'       `.     |    |  /`.   \\,-'    |   \\  /   |   |    \\  |`." << endl;
    cout << "\\      __    \\    '-.  | /   `.  ___    |    \\/    |   '-.   \\ |  |" << endl;
    cout << " \\.    \\ \\   |  __  |  |/    ,','_  `.  |          | __  |    \\|  |" << endl;
    cout << "   \\    \\/   /,' _`.|      ,' / / / /   |          ,' _`.|     |  |" << endl;
    cout << "    \\     ,-'/  /   \\    ,'   | \\/ / ,`.|         /  /   \\  |     |" << endl;
    cout << "     \\    \\ |   \\_/  |   `-.  \\    `'  /|  |    ||   \\_/  | |\\    |" << endl;
    cout << "      \\    \\ \\      /       `-.`.___,-' |  |\\  /| \\      /  | |   |" << endl;
    cout << "       \\    \\ `.__,'|  |`-._    `|      |__| \\/ |  `.__,'|  | |   |" << endl;
    cout << "        \\_.-'       |__|    `-._ |              '-.|     '-.| |   |" << endl;
    cout << "                                `'                            '-._|" << endl;

    //Declare the initial model, view, and commands
    Model model;
    View view;
	model.ShowStatus();
    model.Display(view);
    
    char command;
    do{
    //User input for testing game command class
    cout << "Enter command: ";
    cin >> command;

    try{
    switch (command)
    {
        case 'm':
        {
            //Get the rest of the move parameters
            int pokemon_id, x_loc, y_loc;
    
            if(!(cin >> pokemon_id))
                throw Invalid_Input("Input Stream: Was expecting an integer"); 
            if(!(cin >> x_loc))
                throw Invalid_Input("Input Stream: Was expecting an integer");
            if(!(cin >> y_loc))
                throw Invalid_Input("Input Stream: Was expecting an integer");

            //Implement the move command
            Point2D location(x_loc, y_loc);
            DoMoveCommand(model, pokemon_id, location);

			model.Display(view);
        }
        break;
        case 'g':
        {
            //Get the rest of the move to gym parameters
            int pokemon_id, gym_id;
            if(!(cin >> pokemon_id))
                throw Invalid_Input("Input Stream: Was expecting an integer"); 
            if(!(cin >> gym_id))
                throw Invalid_Input("Input Stream: Was expecting an integer");

            //Implememt the move to gym command
            DoMoveToGymCommand(model, pokemon_id, gym_id);

			model.Display(view);
        }
        break;
        case 'c':
        {
            //Get the rest of the move to center parameters
            int pokemon_id, center_id;
            if(!(cin >> pokemon_id))
                throw Invalid_Input("Input Stream: Was expecting an integer"); 
            if(!(cin >> center_id))
                throw Invalid_Input("Input Stream: Was expecting an integer");

            //Implememt the move to center command
            DoMoveToCenterCommand(model, pokemon_id, center_id);
			
			model.Display(view);
        }
        break;
        case 's':
        {
            //Get the rest of the stop parameters
            int pokemon_id;
            if(!(cin >> pokemon_id))
                throw Invalid_Input("Input Stream: Was expecting an integer");

            //Implement the stop function
            DoStopCommand(model, pokemon_id);
			
			model.Display(view);
        }
        break;
        case 'r':
        {
            //Get the rest of the recover stamina parameters
            int pokemon_id, stamina_amount;
            if(!(cin >> pokemon_id))
                throw Invalid_Input("Input Stream: Was expecting an integer"); 
            if(!(cin >> stamina_amount))
                throw Invalid_Input("Input Stream: Was expecting an integer");

            //Implement the recover stamina function
            DoRecoverInCenterCommand(model, pokemon_id, stamina_amount);
			
			model.Display(view);        
		}
        break;
        case 't':
        {
            //Get the rest of the train in gym parameters
            int pokemon_id, training_units;
            if(!(cin >> pokemon_id))
                throw Invalid_Input("Input Stream: Was expecting an integer"); 
            if(!(cin >> training_units))
                throw Invalid_Input("Input Stream: Was expecting an integer");

            //Implement the train in gym function
            DoTrainInGymCommand(model, pokemon_id, training_units);
			
			model.Display(view);
        }
        break;
        case 'v':
        {
           DoGoCommand(model, view);
        }
        break;
        case 'x':
        {
            DoRunCommand(model, view);
        }
        break;
        case 'q':
            cout << "terminating program" << endl;
        break;
        case 'b':
        {
            //Get the rest of the battle parameters
            int pokemon_id, rival_id;
            if(!(cin >> pokemon_id))
                throw Invalid_Input("Input Stream: Was expecting an integer"); 
            if(!(cin >> rival_id))
                throw Invalid_Input("Input Stream: Was expecting an integer");

            DoBattleCommand(model, pokemon_id, rival_id);

            model.Display(view); 
        }
        break;
        case 'a':
        {
            //Get the rest of the battle parameters
            int pokemon_id, arena_id;
            if(!(cin >> pokemon_id))
                throw Invalid_Input("Input Stream: Was expecting an integer");   
            if(!(cin >> arena_id))
                throw Invalid_Input("Input Stream: Was expecting an integer");            
            DoMoveToArenaCommand(model, pokemon_id, arena_id);

            model.Display(view); 
        }
        break;
        case 'n':
        {
            //Get the rest of the parameters for the new object
            char type;
            int id_num;
            Point2D location;
            if(!(cin >> type))
                throw Invalid_Input("Input Stream: Was expecting a character"); 
            if(!(cin >> id_num))
                throw Invalid_Input("Input Stream: Was expecting an integer");
            if(!(cin >> location.x))
                throw Invalid_Input("Input Stream: Was expecting a double");
            if(!(cin >> location.y))
                throw Invalid_Input("Input Stream: Was expecting a double");
            
            model.NewCommand(type, id_num, location);
            model.Display(view); 
        }
        break;
        //EXTRA CREDIT SAVE AND READ COMMANDS
        case 'S':
        {
            std::string filename;
            if(cin >> filename) // >> std::noskipws
            {
                for (int i = 0; i < filename.length(); i++)
                    if (i > 99 || isspace(filename.at(i)))
                        throw Invalid_Input("Error: Filename was too long or contained whitespace");
                
                //Pseudo else
                DoSaveCommand(model, filename);
            }
            else
                throw Invalid_Input("Input Stream: Was expecting a string");
        }
        break;
        case 'R':
        {
            std::string filename;
            if(cin >> filename)
            {
                for (int i = 0; i < filename.length(); i++)
                    if (i > 99 || isspace(filename.at(i)))
                        throw Invalid_Input("Error: Filename was too long or contained whitespace");
                
                //Pseudo else
                DoReadCommand(model, filename);

                model.ShowStatus();
                model.Display(view); 
                cout << "Save loaded sucessfully, keep going from where you left off!" << endl;
            }
            else
                throw Invalid_Input("Input Stream: Was expecting a string");
        }
        break;
        default:
        {
            throw Invalid_Input("Error: Please enter a valid command"); 
        }
       
    }
    } //try
    catch(Invalid_Input& except)
    {
        cout << "Invalid input - " << except.msg_ptr << endl;

        // actions to be taken if the input is wrong (io stream error)
        cin.clear(); //clear the error from the ios_base in order to prevent looping
        cin.ignore(numeric_limits<streamsize>::max(),'\n'); //clear the input buffer incase of input stream error
        
    }
    }while (command != 'q');
    
    
    
    
    return 0;
}
