using namespace std;
#include <ostream>

#ifndef VECTOR_2D_H
#define VECTOR_2D_H

class Vector2D
{
public:
    //Member Variables
    double x;
    double y;

    //Default Constructor
    Vector2D();

    //Constructor
    Vector2D(double, double);
};

//Overloading the << operator
ostream& operator<<(ostream&, const Vector2D&);

//Overload the * operator for double and Vector2D multiplication
Vector2D operator*(Vector2D, double);

//Overload the / operator for double and Vector2D division
Vector2D operator/(Vector2D, double);
#endif