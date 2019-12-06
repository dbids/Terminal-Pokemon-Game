using namespace std;
#include <ostream>
#include "Vector2D.h"

#ifndef POINT_2D_H
#define POINT_2D_H

class Point2D
{
public:
    //Member variables:
    double x;
    double y;

    //Constructors
    Point2D(); 
    Point2D(double, double);

};

//Declaring the GetDistanceBetween function
double GetDistanceBetween(Point2D, Point2D);

//Overloading the << operator
ostream& operator<<(ostream&, const Point2D&);

//Overload the + operator to add the two member variables and return a new Point2D object
Point2D operator+(Point2D, Vector2D);

//Overload the - operator to subtract the two member variables and return a new Point2D object
Vector2D operator-(Point2D, Point2D);

//Overload the == operator for later use in Model.cpp to check if the pokemon is in the building (not used in Pokemon.cpp)
bool operator==(Point2D p1, Point2D p2);

#endif
