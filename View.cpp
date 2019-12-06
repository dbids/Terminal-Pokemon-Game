using namespace std;
#include <iostream>
#include <sstream>
#include <vector>

//Include user defined headers
#include "View.h"
#include "Point2D.h"
#include "GameObject.h"

// Constructors/Destructors
View::View()
{
	size = 11;
    scale = 2.0;
    origin.x = 0;
    origin.y = 0;
}

//Public Member Functions:

//Returns a bool indicating whether or not subscripts were correctly found, as well as the subscripts by reference
bool View::GetSubscripts(int& out_x, int& out_y, Point2D location)
{
    out_x = static_cast<int>((location.x - origin.x) / scale);
    out_y = static_cast<int>((location.y - origin.y) / scale);

    if (out_x >= origin.x && out_x <= size - 1 &&
        out_y >= origin.y && out_y <= size - 1)
        {
            return true;
        }
        
    
    //Pseudo else
    cout << "An object is outside the display" << endl;
    return false;
}

//Sets the grid to the background of dots and spaces
void View::Clear()
{
    for (int j = 0; j < size; j++)
    {
        for (int i = 0; i < size; i++)
        {
            grid[i][j][0] = '.';
            grid[i][j][1] = ' ';
        }
    }
}

//Places the objects on the grid
void View::Plot(GameObject* ptr)
{
    Point2D location = ptr->GetLocation();
    int out_x, out_y;

    //Check to see if the subscripts function passes
    if (GetSubscripts(out_x, out_y, location) && (ptr->ShouldBeVisible()))
    {
        //If there is nothing there then plot the display code and id num
        if (grid[out_y][out_x][0] == '.' && grid[out_y][out_x][1] == ' ')
        {
            char id[2];
            ptr->DrawSelf(id);
            grid[out_y][out_x][0] = id[0];
            grid[out_y][out_x][1] = id[1];
        }
        //If there is something there then plot '*' and ' '
        else
        {
            grid[out_y][out_x][0] = '*';
            grid[out_y][out_x][1] = ' ';
        }
    }
}

//Draws the whole plot and grid
void View::Draw()
{
    //Define an output string stream for each line of the output
    vector<stringstream> line(size + 1);
     
    //Find the axis labels as a vector, this is what I have come up with so that the axis are not hard coded
    vector<int> axisLabels(size/2 + 1);
    int curr_num = 0;
    for (int i = 0; i < (size/2 + 1); i++)
    {
        axisLabels[i] = curr_num;
        curr_num += view_maxsize / (size / 2);
    }
    
    //Print the axis
    line[0] << "  " << axisLabels[0] << "   " << axisLabels[1] << "   " << axisLabels[2] 
            << "  " << axisLabels[3] << "  " << axisLabels[4] << "  " << axisLabels[5];
    line[1] << axisLabels[0] << " ";
    line[2] << "  ";
    line[3] << axisLabels[1] << " ";
    line[4] << "  ";
    line[5] << axisLabels[2] << " ";
    line[6] << "  ";
    line[7] << axisLabels[3];
    line[8] << "  ";
    line[9] << axisLabels[4];
    line[10] << "  ";
    line[11] << axisLabels[5];

    //Add the grid to each stringstream
    for (int l = 1; l < size + 1; l++)
    {
        for (int j = 0; j < size; j++)
        {
                line[l] << grid[l-1][j][0];
                line[l] << grid[l-1][j][1];
        }
    }

    //cout all of the stringstreams
    for (int l = size; l >= 0; l--)
    {
        cout << line[l].str() << endl;
    }
    
    line.clear();
}
