using namespace std;
#include "Vector2D.h"
#include <ostream>

Vector2D :: Vector2D()
{
    x = 0.0;
    y = 0.0;
}

Vector2D :: Vector2D(double in_x, double in_y)
{
    x = in_x;
    y = in_y;
}

//Overload the << operator for formatted output of <x, y>
ostream& operator<<(ostream& out, const Vector2D& v1)
{
    out << "<" << v1.x << ", " << v1.y << ">";
    return out;
}

//Overload the * operator for double and Vector2D multiplication
Vector2D operator*(Vector2D v1, double d)
{
	Vector2D returnVector;
	
	returnVector.x = v1.x * d;
	returnVector.y = v1.y * d;
	
	return returnVector;
}

//Overload the / operator for double and Vector2D division
Vector2D operator/(Vector2D v1, double d)
{
	Vector2D returnVector;
	
	//Check for divide by zero
	if (d == 0)
		return v1;
	
	returnVector.x = v1.x / d;
	returnVector.y = v1.y / d;
	return returnVector;
}