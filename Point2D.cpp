using namespace std;
#include "Point2D.h"
#include <ostream>
#include <cmath> //abs(), sqrt(), pow()
#include "Vector2D.h"

Point2D :: Point2D()
{
    x = 0.0;
    y = 0.0;
}

Point2D :: Point2D(double x_in, double y_in)
{
    x = x_in;
    y = y_in;
}

//Create the non-member function GetDistanceBetween which finds the distance between two points
double GetDistanceBetween(Point2D p1, Point2D p2)
{
    double xDiff = 0, yDiff = 0, diff = 0;

    xDiff = abs(p1.x - p2.x);
    yDiff = abs(p1.y - p2.y);
    diff = sqrt(pow(xDiff,2) + pow(yDiff,2));
    return diff;
}

//Overload the << operator for formatted output of (x, y)
ostream& operator<<(ostream& out, const Point2D& p2d)
{
    out << "(" << p2d.x << ", " << p2d.y << ")";
    return out;
}

//Overload the + operator to add the two member variables and return a new Point2D object
Point2D operator+(Point2D p1, Vector2D v1)
{
    Point2D out;
    out.x = p1.x + v1.x;
    out.y = p1.y + v1.y;

    return out;
}

//Overload the - operator to subtract the two member variables and return a new Point2D object
Vector2D operator-(Point2D p1, Point2D p2)
{
    Vector2D out;
    out.x = p1.x - p2.x;
    out.y = p1.y - p2.y;

    return out;
}

//Overload the == operator for later use in Model.cpp to check if the pokemon is in the building (not used in Pokemon.cpp)
bool operator==(Point2D p1, Point2D p2)
{
	if ((p1.x == p2.x) && (p1.y == p2.y))
    {
        return true;
    }
		
	return false;
}
